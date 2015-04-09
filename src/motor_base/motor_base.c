#include <msp430x22x4.h>
#include <stdint.h>
#include "motor_base.h"

#define MAP_SPEED(x, a, b) ((x) + 100 )

#define MAP_SPEED_MOTOR1(x)
#define MAP_SPEED_MOTOR2(x)

uint8_t motor_init(void);

void motor_stop(void);

void motor_set(int8_t speed,  enum MOTOR motor);