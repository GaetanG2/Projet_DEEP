/*
 * servo.h
 *
 *  Created on: 26 sept. 2023
 *      Author: Personnel
 */
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
void SERVO_init(void);
void SERVO_set_position(uint16_t position);
void SERVO_process_test(void);
