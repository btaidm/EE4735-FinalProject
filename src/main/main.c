#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"
#include "helper.h"
#include "motor_base.h"
#include <string.h>

//static char temp[10] = {0};

#define TOTAL_CALBRATION_STEPS 10
#define DRIVE_METHOD 3
#define MATLAB_STUFF 1
#define CYCLES_TO_CM 64

#if MATLAB_STUFF == 1
#include "uart.h"
uart_config_t config = { .baud = 9600 };
#endif

static const uint32_t FOLLOWING_DISTANCE = 2 * CYCLES_TO_CM * 30; //cycles
static const uint32_t CALIBRATING_DISTANCE = CYCLES_TO_CM * 30; //cycles
static const uint32_t DISTANCE_TOL = CYCLES_TO_CM * 10;
static const uint32_t PINGER_OFFSET_TOL = CYCLES_TO_CM * 20;
static const uint8_t SPEED_SLOPE = 2;
static const uint8_t SPEED_START_OFFSET = 9;
static const uint8_t SPEED_LIMIT = 90;
static const uint8_t TURN_SPEED = 45;

static uint8_t calibrationCount = TOTAL_CALBRATION_STEPS;
static int32_t leftOffset = 0;
static int32_t rightOffset = 0;
static uint8_t drive_state = 0;



#define MAX_TICKS 10000        // Blink length (loop passes)

pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0}, \
                        .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 2}, \
                        .echoTime = 0, \
                        .ledpin = 1
                      };

pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1}, \
                         .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 3}, \
                         .echoTime = 0, \
                         .ledpin = 0
                       };

pinger_t* use_pinger = &leftPinger;



__INTERRUPT(TIMERA0_VECTOR) void timara0_isr(void)
{
    static uint8_t edge_1 = 0;
    static uint16_t reTime_1 = 0;

    uint16_t currStamp = TACCR0;

    TACCTL0 ^= CM1 | CM0;

    switch (edge_1)
    {
        case 0:
        {
            reTime_1 = currStamp;
            edge_1 = 1;
            break;
        }

        case 1:
        {
            edge_1 = 0;
            uint32_t totalTime = 0;

            if (currStamp < reTime_1)
            {
                totalTime = currStamp;
                currStamp = 0xFFFF;
            }

            totalTime += (currStamp - reTime_1);
            leftPinger.echoTime = totalTime;

            use_pinger = &rightPinger;

            // TB0CTL |= (TBCLR);
            //TB0CTL |= TBIE;
            TB0CCTL0 |= CCIE;

            //start_pinger(&rightPinger);
            break;
        }
    }
}

__INTERRUPT(TIMERA1_VECTOR) void timera1_isr(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case TAIV_TACCR1:
        {
            static uint8_t edge_2 = 0;
            static uint16_t reTime_2 = 0;

            uint16_t currStamp = TACCR1;

            TACCTL1 &= ~CCIFG;
            TACCTL1 ^= CM1 | CM0;

            // P1OUT ^= 0x01;                            // Set pin P1.0 to output

            switch (edge_2)
            {
                case 0:
                {
                    reTime_2 = currStamp;
                    edge_2 = 1;
                    break;
                }

                case 1:
                {
                    edge_2 = 0;
                    uint32_t totalTime = 0;

                    if (currStamp < reTime_2)
                    {
                        totalTime = currStamp;
                        currStamp = 0xFFFF;
                    }

                    totalTime += (currStamp - reTime_2);
                    rightPinger.echoTime = totalTime;
                    __low_power_mode_off_on_exit();
                    break;
                }
            }

            break;
        }

        case TAIV_TACCR2:
        {
            break;
        }

        case TAIV_TAIFG:
        {
            TACTL &= ~(TAIE | TAIFG);
            start_pinger(&leftPinger);
            break;
        }

        default:
            break;
    }
}

__INTERRUPT(TIMERB0_VECTOR) void timerb0_isr(void)
{
    //static volatile uint8_t pinger = 1;
    //TBCTL &= ~(TBIE | TBIFG);
    //TB0CTL &= ~TBIE;
    TB0CCTL0 &= ~CCIE;
    start_pinger(use_pinger);
}

inline void setup_timer(void)
{
    TACTL   = TASSEL_2 | ID_0 | MC_2;
    TACCTL0 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    TACCTL1 = CM_1 | CCIS_1 | CAP | SCS | CCIE;
    TB0CTL =  TBSSEL_2 | ID_1 | MC_1;
    // //TBCCTL0 = CCIE;
    TB0CCR0 =  35750;


    //TACCTL2 = CM0 | CCIS_1 | CAP | SCS | CCIE;
}

inline void setup_clock(void)
{
    BCSCTL1 = CALBC1_1MHZ;                // DCO = 1 MHz
    //BCSCTL2 |= DIVS_3;
    DCOCTL  = CALDCO_1MHZ;                // DCO = 1 MHz
}

static inline void calibrate(void)
{
    int32_t newLeftOffset = (int32_t)CALIBRATING_DISTANCE - (int32_t)leftPinger.echoTime;
    int32_t newRightOffset = (int32_t)CALIBRATING_DISTANCE - (int32_t)rightPinger.echoTime;
    leftOffset += newLeftOffset;
    rightOffset += newRightOffset;

    if (calibrationCount == 0)
    {
        leftOffset /= TOTAL_CALBRATION_STEPS;
        rightOffset /= TOTAL_CALBRATION_STEPS;
    }
}

static inline void drive(void)
{
    uint32_t newLeftEcho = leftPinger.echoTime + leftOffset;
    uint32_t newRightEcho = rightPinger.echoTime + rightOffset;
    uint32_t currentDistance = (newLeftEcho + newRightEcho) / 2;

#if MATLAB_STUFF == 1
    uart_putsUint32(newLeftEcho);
    uart_putsUint32(newRightEcho);
    uart_putsUint32(currentDistance);

#elif DRIVE_METHOD == 1

    if ((FOLLOWING_DISTANCE - DISTANCE_TOL) <= currentDistance && currentDistance <= (FOLLOWING_DISTANCE + DISTANCE_TOL) && drive_state != 0)
    {
        motor_stop();
        drive_state = 0;
    }
    else if (currentDistance < (FOLLOWING_DISTANCE - DISTANCE_TOL))
    {
        motor_half_speed(REVERSE);
        drive_state = 2;
    }
    else if (currentDistance > (FOLLOWING_DISTANCE + DISTANCE_TOL))
    {
        motor_half_speed(FORWARD);
        drive_state = 1;
    }

#elif DRIVE_METHOD == 2

    int32_t distanceToTarget = currentDistance - FOLLOWING_DISTANCE;

    if (-DISTANCE_TOL <= distanceToTarget && distanceToTarget <= DISTANCE_TOL)
    {
        motor_stop();
    }
    else
    {
        int8_t speed = distanceToTarget / (SPEED_SLOPE * CYCLES_TO_CM);

        if (distanceToTarget < 0)
            speed += -SPEED_START_OFFSET;
        else
            speed += SPEED_START_OFFSET;

        if (speed >= SPEED_LIMIT) speed = SPEED_LIMIT;

        if (speed <= -SPEED_LIMIT) speed = -SPEED_LIMIT;

        motor_set_both(speed);
    }

#elif DRIVE_METHOD == 3
    int32_t distanceToTarget = currentDistance - FOLLOWING_DISTANCE;
    int32_t leftRightOffset = newLeftEcho - newRightEcho;

    // if (-DISTANCE_TOL <= distanceToTarget && distanceToTarget <= DISTANCE_TOL)
    // {
    if (-PINGER_OFFSET_TOL <= leftRightOffset && leftRightOffset <= PINGER_OFFSET_TOL)
    {
        motor_stop();
    }
    else
    {
        if (leftRightOffset < 0)
            motor_spin(-TURN_SPEED);
        else
            motor_spin(TURN_SPEED);
    }

    // }
    // else
    // {
    //     int8_t speed = distanceToTarget / (SPEED_SLOPE * CYCLES_TO_CM);

    //     if (distanceToTarget < 0)
    //         speed += -SPEED_START_OFFSET;
    //     else
    //         speed += SPEED_START_OFFSET;


    //     int8_t speed1 = speed;
    //     int8_t speed2 = speed;

    //     if (-PINGER_OFFSET_TOL <= leftRightOffset && leftRightOffset <= PINGER_OFFSET_TOL)
    //     {
    //         speed1 += (leftRightOffset < 0) ? -TURN_SPEED : TURN_SPEED;
    //         speed2 -= (leftRightOffset < 0) ? -TURN_SPEED : TURN_SPEED;
    //     }

    //     if (speed1 >= SPEED_LIMIT) speed1 = SPEED_LIMIT;

    //     if (speed1 <= -SPEED_LIMIT) speed1 = -SPEED_LIMIT;

    //     if (speed2 >= SPEED_LIMIT) speed2 = SPEED_LIMIT;

    //     if (speed2 <= -SPEED_LIMIT) speed2 = -SPEED_LIMIT;

    //     motor_set(speed1, MOTOR_1);
    //     motor_set(speed2, MOTOR_2);
    //     //motor_set_both(speed);
    // }

#endif

}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    P2SEL = 0;
    setup_timer();
    setup_pinger(&leftPinger);
    setup_pinger(&rightPinger);

    setup_clock();

#if MATLAB_STUFF == 1
    uart_init(&config);
#else
    motor_init();
#endif

#if MATLAB_STUFF == 1
    uart_puts("STARTCOL");
#endif
    P1DIR |= 0x03;                            // Set pin P1.0 to output
    P1OUT &= ~0x03;
    P1OUT |= 0x01;

    //P2SEL2 = 0;
    //motor_full_speed(FORWARD);


    while ( 1)
    {
        // Get the Pinger Distances
        //start_pinger(leftPinger);
        // start_pinger(rightPinger);
        //Go to low Power Mode
        use_pinger = &leftPinger;
        //TB0CTL |= (TBCLR);
        //TB0CTL |= TBIE;
        TB0CCTL0 |= CCIE;
        //TACTL   |= TAIE;
        __enable_interrupt();
        __low_power_mode_1();
        __disable_interrupt();


        // Calibrate or drive
        if (calibrationCount != 0)
        {
            calibrationCount--;
            calibrate();
        }
        else
        {
            //motor_full_speed(FORWARD);
            drive();

        }
    }
}