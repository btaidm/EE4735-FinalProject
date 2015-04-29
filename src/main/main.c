#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"
#include "helper.h"
#include "motor_base.h"
#include <string.h>


#define TOTAL_CALBRATION_STEPS 10
#define MATLAB_STUFF 0
#define CYCLES_TO_CM 64
#define USE_RAW 0

#define ABS(x) (((x) < 0) ? -(x) : (x))

#if MATLAB_STUFF == 1
#include "uart.h"
uart_config_t config = { .baud = 9600 };
#endif

static const uint32_t CALIBRATING_DISTANCE = 1 * CYCLES_TO_CM * 30; //cycles

static const uint32_t FOLLOWING_DISTANCE = 1 * CYCLES_TO_CM * 30; //cycles
static const uint32_t DISTANCE_TOL = CYCLES_TO_CM * 10;
static const uint32_t PINGER_OFFSET_TOL_LOWER = CYCLES_TO_CM * 60;
static const uint32_t PINGER_OFFSET_TOL_UPPER = CYCLES_TO_CM * 80;
static const uint32_t PINGER_LIMIT = CYCLES_TO_CM * 400;
static const uint8_t SPEED_SLOPE = 2;
static const uint8_t SPEED_START_OFFSET = 9;
static const uint8_t SPEED_LIMIT = 90;

static const uint8_t TURN_SPEED_SLOPE = 4;
static const uint8_t TURN_SPEED_LOWER = 5;
static const uint8_t TURN_SPEED_UPPER = 45;

static uint8_t calibrationCount = TOTAL_CALBRATION_STEPS;
static int32_t leftOffset = 0;
static int32_t rightOffset = 0;
static uint8_t drive_state = 0;

#define HIST_SIZE 3

uint32_t leftHist[HIST_SIZE] = {0};
uint32_t rightHist[HIST_SIZE] = {0};

uint8_t histCount = 0;

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

pinger_t* usePinger = &leftPinger;

static inline uint32_t GetMedian(uint32_t* hist, uint8_t count)
{
    uint32_t max = hist[0];
    uint32_t med = 0;

    for (uint8_t i = 0; i < HIST_SIZE; i++)
    {
        if (hist[i] > max)
        {
            med = max;
            max = hist[i];
            continue;
        }

        if (hist[i] > med)
        {
            med = hist[i];
        }
    }

    return med;
}

static inline void PutValue(uint32_t* hist, uint8_t count, uint32_t value)
{
    hist[(count) % HIST_SIZE] = value;
}


__INTERRUPT(TIMERA0_VECTOR) void TimerA0ISR(void)
{
    static uint8_t edge1 = 0;
    static uint16_t reTime1 = 0;

    uint16_t currStamp = TACCR0;

    TACCTL0 ^= CM1 | CM0;

    switch (edge1)
    {
        case 0:
        {
            reTime1 = currStamp;
            edge1 = 1;
            break;
        }

        case 1:
        {
            edge1 = 0;
            uint32_t totalTime = 0;

            if (currStamp < reTime1)
            {
                totalTime = currStamp;
                currStamp = 0xFFFF;
            }

            totalTime += (currStamp - reTime1);
            leftPinger.echoTime = totalTime;

            usePinger = &rightPinger;

            // TB0CTL |= (TBCLR);
            //TB0CTL |= TBIE;
            TB0CCTL0 |= CCIE;

            //StartPinger(&rightPinger);
            break;
        }
    }
}

__INTERRUPT(TIMERA1_VECTOR) void TimerA1ISR(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case TAIV_TACCR1:
        {
            static uint8_t edge2 = 0;
            static uint16_t reTime_2 = 0;

            uint16_t currStamp = TACCR1;

            TACCTL1 &= ~CCIFG;
            TACCTL1 ^= CM1 | CM0;

            // P1OUT ^= 0x01;                            // Set pin P1.0 to output

            switch (edge2)
            {
                case 0:
                {
                    reTime_2 = currStamp;
                    edge2 = 1;
                    break;
                }

                case 1:
                {
                    edge2 = 0;
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
            StartPinger(&leftPinger);
            break;
        }

        default:
            break;
    }
}

__INTERRUPT(TIMERB0_VECTOR) void TimerB0ISR(void)
{
    //static volatile uint8_t pinger = 1;
    //TBCTL &= ~(TBIE | TBIFG);
    //TB0CTL &= ~TBIE;
    TB0CCTL0 &= ~CCIE;
    StartPinger(usePinger);
}

inline void SetupTimer(void)
{
    TACTL   = TASSEL_2 | ID_0 | MC_2;
    TACCTL0 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    TACCTL1 = CM_1 | CCIS_1 | CAP | SCS | CCIE;
    TB0CTL =  TBSSEL_2 | ID_1 | MC_1;
    // //TBCCTL0 = CCIE;
    TB0CCR0 =  35750;


    //TACCTL2 = CM0 | CCIS_1 | CAP | SCS | CCIE;
}

inline void SetupTimer(void)
{
    BCSCTL1 = CALBC1_1MHZ;                // DCO = 1 MHz
    //BCSCTL2 |= DIVS_3;
    DCOCTL  = CALDCO_1MHZ;                // DCO = 1 MHz
}

static inline void Calibrate(void)
{
    int32_t newLeftOffset = CALIBRATING_DISTANCE - leftPinger.echoTime;
    int32_t newRightOffset = CALIBRATING_DISTANCE - rightPinger.echoTime;
    leftOffset += newLeftOffset;
    rightOffset += newRightOffset;

    if (calibrationCount == 0)
    {
        leftOffset /= TOTAL_CALBRATION_STEPS;
        rightOffset /= TOTAL_CALBRATION_STEPS;
    }
}

static inline void Drive(void)
{
    uint32_t newLeftEcho = leftPinger.echoTime + leftOffset;
    uint32_t newRightEcho = rightPinger.echoTime + rightOffset;
    PutValue(leftHist, histCount, newLeftEcho);
    PutValue(rightHist, histCount, newRightEcho);

    if (histCount == 254)
        histCount = 0;
    else
        histCount++;

    newLeftEcho = GetMedian(leftHist, histCount);
    newRightEcho = GetMedian(rightHist, histCount);

    uint32_t currentDistance = (newLeftEcho + newRightEcho) / 2;

#if MATLAB_STUFF == 1
    UartPutsUint32(newLeftEcho);
    UartPutsUint32(newRightEcho);
    UartPutsUint32(currentDistance);

#else
    int32_t distanceToTarget = currentDistance - FOLLOWING_DISTANCE;

#if USE_RAW == 0
    int32_t leftRightDiff = newLeftEcho - newRightEcho;
#else
    int32_t leftRightDiff = leftPinger.echoTime - rightPinger.echoTime
#endif

    if (leftPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin(TURN_SPEED_LOWER + TURN_SPEED_UPPER);
    }
    else if (rightPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin(-(TURN_SPEED_LOWER + TURN_SPEED_UPPER));
    }
    else if (ABS(distanceToTarget) <= DISTANCE_TOL)
    {
        int8_t speed = 0;

        if ( ABS(leftRightDiff) > PINGER_OFFSET_TOL_LOWER)
        {
            if (ABS(leftRightDiff) > PINGER_OFFSET_TOL_UPPER)
            {
                speed = Sign32(leftRightDiff) * TURN_SPEED_UPPER;
            }
            else
            {
                speed = Sign32(leftRightDiff) * (((ABS(leftRightDiff) - PINGER_OFFSET_TOL_LOWER) / (CYCLES_TO_CM)) + TURN_SPEED_LOWER);
            }

            MotorSpin(speed);
        }
        else
        {
            MotorStop();
        }
    }
    else
    {
        int8_t speed = distanceToTarget / (SPEED_SLOPE * CYCLES_TO_CM);

        if (distanceToTarget < 0)
            speed += -SPEED_START_OFFSET;
        else
            speed += SPEED_START_OFFSET;

        int8_t speed1 = speed;
        int8_t speed2 = speed;

        // if (currentDistance > CROSS_POINT)
        //     leftRightDiff = -leftRightDiff;

        if ( ABS(leftRightDiff) > PINGER_OFFSET_TOL_LOWER)
        {
            if (ABS(leftRightDiff) > PINGER_OFFSET_TOL_UPPER)
            {
                speed1 += (leftRightDiff < 0) ? -TURN_SPEED_UPPER :  TURN_SPEED_UPPER;
                speed2 -= (leftRightDiff < 0) ? -TURN_SPEED_UPPER :  TURN_SPEED_UPPER;
            }
            else
            {
                speed1 += (leftRightDiff / CYCLES_TO_CM);
                speed2 -= (leftRightDiff / CYCLES_TO_CM);
            }
        }

        if (speed1 >= SPEED_LIMIT) speed1 = SPEED_LIMIT;

        if (speed1 <= -SPEED_LIMIT) speed1 = -SPEED_LIMIT;

        if (speed2 >= SPEED_LIMIT) speed2 = SPEED_LIMIT;

        if (speed2 <= -SPEED_LIMIT) speed2 = -SPEED_LIMIT;

        MotorSet(speed1, MOTOR_1);
        MotorSet(speed2, MOTOR_2);
        //MotorSetBoth(speed);
    }

#endif

}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    P2SEL = 0;
    SetupTimer();
    SetupPinger(&leftPinger);
    SetupPinger(&rightPinger);

    SetupTimer();

#if MATLAB_STUFF == 1
    UartInit(&config);
#else
    MotorInit();
#endif

#if MATLAB_STUFF == 1
    UartPuts("STARTCOL");
#endif
    P1DIR |= 0x03;                            // Set pin P1.0 to output
    P1OUT &= ~0x03;
    P1OUT |= 0x01;

    //P2SEL2 = 0;
    //MotorFullSpeed(FORWARD);


    while ( 1)
    {
        // Get the Pinger Distances
        //StartPinger(leftPinger);
        // StartPinger(rightPinger);
        //Go to low Power Mode
        usePinger = &leftPinger;
        //TB0CTL |= (TBCLR);
        //TB0CTL |= TBIE;
        TB0CCTL0 |= CCIE;
        //TACTL   |= TAIE;
        __enable_interrupt();
        __low_power_mode_1();
        __disable_interrupt();


        // Calibrate or Drive
        if (calibrationCount != 0)
        {
            calibrationCount--;
            Calibrate();
        }
        else
        {
            //MotorFullSpeed(FORWARD);
            Drive();

        }
    }
}