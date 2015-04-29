#include <msp430x22x4.h>
#include <stdint.h>
#include "motor_base.h"

// Maps Number from [-100,100] to [a,b]
#define MAP_SPEED(x, a, b) ((((x) + 100 )*100/(200)) * (b - a)) / 100 + a

// Maps Speed to Motor 1 values
#define MAP_SPEED_MOTOR1(x) MAP_SPEED(x, 1, 127)

// Maps Speed to Motor 2 values
#define MAP_SPEED_MOTOR2(x) MAP_SPEED(x, 128, 255)

uint8_t MotorInit(void)
{
    P3SEL = 0x30;           // Set P3.4 and P3.5 to Tx/Rx
    UCA0CTL1 |= UCSSEL_2;   // Use SMCLK
    UCA0BR0 = 104;          // Buad Rate to 9600
    UCA0BR1 = 0;            // Buad Rate to 9600
    UCA0MCTL = UCBRS0;      // Map 1MHz -> 9600
    UCA0CTL1 &= ~UCSWRST;   // State UART State Machine
    return 0;
}

void MotorStop(void)
{
    // Wait for the transmit buffer to be ready
    while (!(IFG2 & UCA0TXIFG));
    // Transmit data
    UCA0TXBUF = 0;
}

void MotorSet(int8_t speed,  enum MOTOR motor)
{
#if FLIPPED_BASE
    speed = -speed; // Flip Speed if needed
#endif
    
    
    switch (motor)  // Select Motor to drive
    {
        case MOTOR_1:
        {
            // Map Speed to 1 - 127
            uint8_t motorSpeed = MAP_SPEED_MOTOR1(speed);

            while (!(IFG2 & UCA0TXIFG));
            UCA0TXBUF = motorSpeed; // Send speed
            break;
        }

        case MOTOR_2:
        {
            // Map Speed to 128 - 255
            uint8_t motorSpeed = MAP_SPEED_MOTOR2(speed);

            while (!(IFG2 & UCA0TXIFG));
            UCA0TXBUF = motorSpeed; // Send Speed
            break;
        }
    }
}
