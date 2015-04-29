#include <msp430x22x4.h>
#include <stdint.h>
#include "motor_base.h"

#define MAP_SPEED(x, a, b) ((((x) + 100 )*100/(200)) * (b - a)) / 100 + a

#define MAP_SPEED_MOTOR1(x) MAP_SPEED(x, 1, 127)
#define MAP_SPEED_MOTOR2(x) MAP_SPEED(x, 128, 255)

uint8_t MotorInit(void)
{
    P3SEL = 0x30;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;
    UCA0CTL1 &= ~UCSWRST;
    return 0;
}

void MotorStop(void)
{
    /* Wait for the transmit buffer to be ready */
    while (!(IFG2 & UCA0TXIFG));

    /* Transmit data */
    UCA0TXBUF = 0;
}

void MotorSet(int8_t speed,  enum MOTOR motor)
{
#if FLIPPED_BASE
    speed = -speed;
#endif

    switch (motor)
    {
        case MOTOR_1:
        {

            uint8_t motorSpeed = MAP_SPEED_MOTOR1(speed);

            while (!(IFG2 & UCA0TXIFG));

            UCA0TXBUF = motorSpeed;
            break;
        }

        case MOTOR_2:
        {
            uint8_t motorSpeed = MAP_SPEED_MOTOR2(speed);

            while (!(IFG2 & UCA0TXIFG));

            UCA0TXBUF = motorSpeed;
            break;
        }
    }
}
