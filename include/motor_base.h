#ifndef MOTOR_BASE_H
#define MOTOR_BASE_H

#include <stdint.h>

#define FLIPPED_BASE 1

enum DIRECTION
{
    FORWARD = 1,
    REVERSE = -1
};

enum MOTOR
{
    MOTOR_1,
    MOTOR_2
};


uint8_t MotorInit(void);

void MotorStop(void);

void MotorSet(int8_t speed, enum MOTOR motor);

inline void MotorSetBoth(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(speed, MOTOR_2);
}

inline void MotorFullSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 100);
}

inline void MotorHalfSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 50);
}

inline void MotorSpin(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(-speed, MOTOR_2);
}



#endif