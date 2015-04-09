#ifndef MOTOR_BASE_H
#define MOTOR_BASE_H

#include <stdint.h>

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


uint8_t motor_init(void);

void motor_stop(void);

void motor_set(int8_t speed, enum MOTOR motor);

inline void motor_set_both(int8_t speed)
{
    motor_set(speed, MOTOR_1);
    motor_set(speed, MOTOR_2);
}

inline void motor_full_speed(enum DIRECTION dir)
{
    motor_set_both(dir * 100);
}

inline void motor_half_speed(enum DIRECTION dir)
{
    motor_set_both(dir * 50);
}

inline void motor_spin(int8_t speed)
{
    motor_set(speed, MOTOR_1);
    motor_set(-speed, MOTOR_2);
}



#endif