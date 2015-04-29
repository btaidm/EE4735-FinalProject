#include <msp430x22x4.h>
#include <string.h>
#include <stdint.h>
#include "helper.h"
#include "motor_base.h"
#include "pinger.h"


// Total Number of Calibration steps for pingers
#define TOTAL_CALBRATION_STEPS 10

// Used for Communication with MATLAB for collecting data
#define MATLAB_STUFF 0

// Number of cycles to cm, this roughly around 64 cycles to 1 cm
#define CYCLES_TO_CM 64

// Use Raw Echo Times in turn calculations
#define USE_RAW 0

// Get the absolute value of signed number
#define ABS(x) (((x) < 0) ? -(x) : (x))

#if MATLAB_STUFF == 1
// Need UART for Communication
#include "uart.h"
#endif

// Distance to Calibrate to
static const uint32_t CALIBRATING_DISTANCE = 1 * CYCLES_TO_CM * 30; //cycles
// Distance to Follow at
static const uint32_t FOLLOWING_DISTANCE = 1 * CYCLES_TO_CM * 30; //cycles
// Tolerance of Distance to Target, This is +-
static const uint32_t DISTANCE_TOL = CYCLES_TO_CM * 10; //cycles


// How fast to change speed based on distance to target distance
static const uint8_t SPEED_SLOPE_FOR = 2; // ^-1 %/cm
static const uint8_t SPEED_SLOPE_REV = 4; // ^-1 %/cm
// Starting Speed
static const uint8_t SPEED_START_OFFSET_FOR = 9; // %
static const uint8_t SPEED_START_OFFSET_REV = 19; // %
// Max Speed Allowed
static const uint8_t SPEED_LIMIT = 90; // %


// Lower Tolerance of Pinger Difference for Turning
static const uint32_t PINGER_OFFSET_TOL_LOWER = CYCLES_TO_CM * 20; //cycles
// Upper Tolerance of Pinger Difference for Turning
static const uint32_t PINGER_OFFSET_TOL_UPPER = CYCLES_TO_CM * 60; //cycles
// Max Distance of Pingers Allowed
static const uint32_t PINGER_LIMIT = CYCLES_TO_CM * 400; // cycles
// Slope at which Turn Speed Changes
static const uint8_t TURN_SPEED_SLOPE = 4; // ^-1 %/cm
// Lower Turn Speed Limit
static const uint8_t TURN_SPEED_LOWER = 5; // %
// Upper Turn Speed Limits
static const uint8_t TURN_SPEED_UPPER = 45; // %

// Starting Calibration Count
static uint8_t calibrationCount = TOTAL_CALBRATION_STEPS;
// How much to change left echo by, calibrated
static int32_t leftOffset = 0;
// How much to change right echo by, calibrated
static int32_t rightOffset = 0;

// Keep last 3 values and perform median filter
#define HIST_SIZE 3
// History of Left Echoes
uint32_t leftHist[HIST_SIZE] = {0};
// History of Right Echoes
uint32_t rightHist[HIST_SIZE] = {0};
// Number of Echoes Collected, Allowed to roll over
uint8_t histCount = 0;

// Left Pinger GPIO Information
pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0}, \
                        .echo = { .dir = &P2DIR, .sel = &P2SEL, .pin = 2}, \
                        .echoTime = 0, \
                        .ledpin = 1
                      };

// Right Pinger GPIO Information
pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1}, \
                         .echo = { .dir = &P2DIR, .sel = &P2SEL, .pin = 3}, \
                         .echoTime = 0, \
                         .ledpin = 0
                       };

// Current Pinger in use
pinger_t* usePinger = &leftPinger;

/// ----------------------------------------------------------
/// Func: Gets the median of a history of echo times
/// Args: hist = echo history
/// Retn: Median of echo history
/// ----------------------------------------------------------
static inline uint32_t GetMedian(uint32_t* hist)
{
    // Init max to first value
    uint32_t max = hist[0];
    // Init med to 0
    uint32_t med = 0;

    for (uint8_t i = 0; i < HIST_SIZE; i++)
    {
        // Check to see if value is greater than max
        if (hist[i] > max)
        {
            med = max; // med is old max
            max = hist[i]; // hist[i] is new max
        }
        else if (hist[i] > med) // else if hist[i] > med
        {
            med = hist[i]; // it is the new median
        }
    }
    return med;
}

/// ---------------------------------------------------------------------
/// Func: Puts Echo in History Array
/// 
static inline void PutValue(uint32_t* hist, uint8_t count, uint32_t value)
{
    // Index is hist is count & HIST_SIZE to allow for rolling history
    hist[(count) % HIST_SIZE] = value;
}

/// ---------------------------------------
/// Func: Contains the ISR for calculating 
///       echo time of left pinger
/// ---------------------------------------
__INTERRUPT(TIMERA0_VECTOR) void TimerA0ISR(void)
{
    // Edge of echo pulse
    static uint8_t edge1 = 0;
    // Rising edge time
    static uint16_t reTime1 = 0;

    // Get current timestamp
    uint16_t currStamp = TACCR0;
    
    // Flip Capture Edge
    TACCTL0 ^= CM1 | CM0;

    switch (edge1)
    {
        case 0:
        {
            // rising edge is current time
            reTime1 = currStamp;
            // look for falling edge
            edge1 = 1;
            break;
        }

        case 1:
        {
            // look for rising edge
            edge1 = 0;
            // init totalTime
            uint32_t totalTime = 0;

            // Check for roll over
            if (currStamp < reTime1)
            {
                totalTime = currStamp;
                currStamp = 0xFFFF;
            }
            
            // Add the difference 
            totalTime += (currStamp - reTime1);
            
            // That is now our echo time
            leftPinger.echoTime = totalTime;

            // Use the Right Pinger
            usePinger = &rightPinger;

            // Enable timer to use right pinger
            TB0CCTL0 |= CCIE;
            break;
        }
    }
}

/// ---------------------------------------
/// Func: Contains the ISR for calculating 
///       echo time of right pinger
/// ---------------------------------------
__INTERRUPT(TIMERA1_VECTOR) void TimerA1ISR(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case TAIV_TACCR1:
        {
            TACCTL1 &= ~CCIFG; // Clear Interrupt Flag
            // Edge of echo pulse
            static uint8_t edge2 = 0;
            // Rising edge time
            static uint16_t reTime2 = 0;

            // Get current timestamp
            uint16_t currStamp = TACCR1;

            // Flip Capture Edge
            TACCTL1 ^= CM1 | CM0;

            switch (edge2)
            {
                case 0:
                {
                    // rising edge is current time
                    reTime2 = currStamp;
                    // look for falling edge
                    edge2 = 1;
                    break;
                }

                case 1:
                {
                    // look for rising edge
                    edge2 = 0;
                    // init totalTime
                    uint32_t totalTime = 0;

                    // Check for roll over
                    if (currStamp < reTime2)
                    {
                        totalTime = currStamp;
                        currStamp = 0xFFFF;
                    }

                    // Add the difference 
                    totalTime += (currStamp - reTime2);
                    // That is now our echo time
                    rightPinger.echoTime = totalTime;
                    
                    // Now that we have 2 new echos, process them and drive
                    __low_power_mode_off_on_exit();
                    break;
                }
            }

            break;
        }

        case TAIV_TACCR2:
        case TAIV_TAIFG:
        default:
            break;
    }
}

/// --------------------------------------------
/// Func: Timer for starting pinger to allow for
///       proper settling time
/// --------------------------------------------
__INTERRUPT(TIMERB0_VECTOR) void TimerB0ISR(void)
{
    TB0CCTL0 &= ~CCIE; // Disable the timer until needed
    StartPinger(usePinger); // start the next pinger
}

inline void SetupTimer(void)
{
    // Sel. SMCLK | div by 1 | Continuous Mode 
    TACTL   = TASSEL_2 | ID_0 | MC_2;
    
    // Ris Edge | inp = CCI1B | 
    // Capture | Sync Cap | Enab IRQ
    TACCTL0 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    TACCTL1 = CM_1 | CCIS_1 | CAP | SCS | CCIE;
    // Sel. SMCLK | div by 2 | UP Mode
    TB0CTL =  TBSSEL_2 | ID_1 | MC_1;
    TB0CCR0 =  35750; //= ~65mS
}

inline void SetupClock(void)
{
    BCSCTL1 = CALBC1_1MHZ; // DCO = 1 MHz
    DCOCTL  = CALDCO_1MHZ; // DCO = 1 MHz
}

/// ----------------------------------------
/// Func: Calibrate the sensors
/// ----------------------------------------
static inline void Calibrate(void)
{
    // Get the offset for left and right
    int32_t newLeftOffset = CALIBRATING_DISTANCE - leftPinger.echoTime;
    int32_t newRightOffset = CALIBRATING_DISTANCE - rightPinger.echoTime;
    
    // Add them to current offset
    leftOffset += newLeftOffset;
    rightOffset += newRightOffset;

    // If all the values have been added, average them to get best offset
    if (calibrationCount == 0)
    {
        leftOffset /= TOTAL_CALBRATION_STEPS;
        rightOffset /= TOTAL_CALBRATION_STEPS;
    }
}

/// --------------------------------------
/// Func: Send command to robot base based
///       on a set of rules and tolerances
/// --------------------------------------
static inline void Drive(void)
{
    // First set echoes to calibrated echoes
    uint32_t newLeftEcho = leftPinger.echoTime + leftOffset;
    uint32_t newRightEcho = rightPinger.echoTime + rightOffset;
    
    // Add them to the history
    PutValue(leftHist, histCount, newLeftEcho);
    PutValue(rightHist, histCount, newRightEcho);

    // Reset on 254 because 3 is not a nice number to roll over with
    if (histCount == 254)
        histCount = 0;
    else
        histCount++;

    // Get median values to work with
    newLeftEcho = GetMedian(leftHist);
    newRightEcho = GetMedian(rightHist);

    // Average them to get the center distance
    uint32_t currentDistance = (newLeftEcho + newRightEcho) / 2;

#if MATLAB_STUFF == 1
    // Send to MATLAB
    UartPutsUint32(newLeftEcho);
    UartPutsUint32(newRightEcho);
    UartPutsUint32(currentDistance);

#else
    // Calculate distance to the target
    int32_t distanceToTarget = currentDistance - FOLLOWING_DISTANCE;

#if USE_RAW == 0
    // Use Calibrated echoes for turns
    int32_t leftRightDiff = newLeftEcho - newRightEcho;
#else
    // Use raw echoes for turns
    int32_t leftRightDiff = leftPinger.echoTime - rightPinger.echoTime;
#endif

    // If Left Pinger is out of limit spin left at high speed
    if (leftPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin(-(TURN_SPEED_UPPER));
    }
    // If Right Pinger is out of limit spin Right at high speed
    else if (rightPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin((TURN_SPEED_UPPER));
    }
    // If distance to target is in a safe range
    else if (ABS(distanceToTarget) <= DISTANCE_TOL)
    {
        int8_t speed = 0;
        // Check to see if target is outside of safe turn region
        if ( ABS(leftRightDiff) >= PINGER_OFFSET_TOL_LOWER)
        {
            // If outside of Upper Limit
            if (ABS(leftRightDiff) >= PINGER_OFFSET_TOL_UPPER)
            {
                // Turn at max speed in correct direction
                speed = Sign32(leftRightDiff) * TURN_SPEED_UPPER;
            }
            else
            {
                // Turn at calculated speed in correct direction
                // Speed is calculated based on a point slope based on a given
                // slope, min speed, and lower tolerance
                speed = Sign32(leftRightDiff)
                      * (((ABS(leftRightDiff) - PINGER_OFFSET_TOL_LOWER)
                      / (TURN_SPEED_SLOPE * CYCLES_TO_CM)) + TURN_SPEED_LOWER);
            }
            
            // Spin
            MotorSpin(speed);
        }
        else
        {
            // Stop and wait
            MotorStop();
        }
    }
    else
    {
        // Calculate Base speed on distance to target and a slope
        int16_t speed = 0;

        if (distanceToTarget > 0)
        {
            speed = distanceToTarget / (SPEED_SLOPE_FOR * CYCLES_TO_CM);
        }
        else
        {
            speed = (distanceToTarget * SPEED_SLOPE_REV) / (CYCLES_TO_CM);
        }
        
        // if target is too close
        if (distanceToTarget < 0)
            // back up
            speed += -SPEED_START_OFFSET_REV;
        else
            // move forward
            speed += SPEED_START_OFFSET_FOR;

        // Limit Speed to prevent overflows
        if (speed >= SPEED_LIMIT) speed = SPEED_LIMIT;

        if (speed <= -SPEED_LIMIT) speed = -SPEED_LIMIT;
        
        // Branch speed into the separate motors
        int8_t speed1 = speed;
        int8_t speed2 = speed;

        // Calculate turn speed addition
        // Check to see if target is outside of safe turn region
        if ( ABS(leftRightDiff) > PINGER_OFFSET_TOL_LOWER)
        {
            if (ABS(leftRightDiff) > PINGER_OFFSET_TOL_UPPER)
            {
                // Add turn of max speed in correct direction
                speed1 += Sign32(leftRightDiff) * TURN_SPEED_UPPER;
                speed2 -= Sign32(leftRightDiff) * TURN_SPEED_UPPER;
            }
            else
            {
                // Turn at calculated speed in correct direction
                // Speed is calculated based on a point slope based on a given
                // slope, min speed, and lower tolerance
                speed1 += Sign32(leftRightDiff) * (((ABS(leftRightDiff) - PINGER_OFFSET_TOL_LOWER) / (TURN_SPEED_SLOPE * CYCLES_TO_CM)) + TURN_SPEED_LOWER);
                speed2 -= Sign32(leftRightDiff) * (((ABS(leftRightDiff) - PINGER_OFFSET_TOL_LOWER) / (TURN_SPEED_SLOPE * CYCLES_TO_CM)) + TURN_SPEED_LOWER);
            }
        }

        // Fi
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
    SetupClock();
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