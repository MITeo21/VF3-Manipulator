#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// === TASKS === //
#define HARDWARE_TIMER_PRESCALER 80

// DEBUG Task
#define DEBUG_TASK_ENABLE false
#define DEBUG_TASK_FREQUENCY 1
#define DEBUG_TASK_PRIORITY 1

// SERIAL task
#define SERIAL_TASK_ENABLE true
#define SERIAL_TASK_FREQUENCY 50
#define SERIAL_TASK_PRIORITY 2

#define BAUD_RATE 115200

// SERVO task
#define SERVO_TASK_ENABLE true
#define SERVO_TASK_FREQUENCY 55
#define SERVO_TASK_PRIORITY 3

#define N_FINGERS 3
#define EXTENDED_POS_DEG 80
#define RETRACTED_POS_DEG 0

#define SERVO_0_PIN 27
#define SERVO_1_PIN 26
#define SERVO_2_PIN 25

#endif