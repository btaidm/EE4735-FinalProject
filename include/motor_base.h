#ifndef MOTOR_BASE_H
#define MOTOR_BASE_H

#include <stdint.h>

/// Set to 1 or 0 depending on which is front of base
/// Flips the speed sign while keeping other code the
/// same.
#define FLIPPED_BASE 1

enum DIRECTION
{
    FORWARD = 1, // Set Motor to forward motion
    REVERSE = -1 // Set Motor to reverse motion
};

enum MOTOR
{
    MOTOR_1, // Set motor 1
    MOTOR_2  // Set motor 2
};


/// ------------------------------------
/// Func: Init UART for Sabertooth Usage
/// Retn: Should Always be zero unless
///       compiler breaks
/// ------------------------------------
uint8_t MotorInit(void);

/// ------------------------------------
/// Func: Set Motors to Full Stop in 1 
///       command
/// ------------------------------------
void MotorStop(void);

/// ----------------------------------------
/// Func: Set Motor to specified speed
/// Args: speed = speed of motor -100 to 100
///       motor = motor to set
/// ----------------------------------------
void MotorSet(int8_t speed, enum MOTOR motor);

/// -----------------------------------------
/// Func: Sets both motors to specified speed
/// Args: speed = speed of motors -100 to 100
/// -----------------------------------------
inline void MotorSetBoth(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(speed, MOTOR_2);
}

/// -----------------------------------------
/// Func: Set Motors to run at full speed in
///       given direction
/// Args: dir = direction of travel
/// -----------------------------------------
inline void MotorFullSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 100);
}

/// -----------------------------------------
/// Func: Set Motors to run at half speed in
///       given direction
/// Args: dir = direction of travel
/// -----------------------------------------
inline void MotorHalfSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 50);
}

/// -----------------------------------------
/// Func: Set Motors to spin in place at
///       given speed
/// Args: speed = speed of motors -100 to 100
/// -----------------------------------------
inline void MotorSpin(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(-speed, MOTOR_2);
}

#endif