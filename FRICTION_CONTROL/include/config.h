#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// === TASKS === //
#define HARDWARE_TIMER_PRESCALER 80

// DEBUG Task
#define DEBUG_TASK_ENABLE false
#define DEBUG_TASK_FREQUENCY 10
#define DEBUG_TASK_PRIORITY 1

// SERIAL task
#define SERIAL_TASK_ENABLE true
#define SERIAL_TASK_FREQUENCY 10
#define SERIAL_TASK_PRIORITY 2

#define BAUD_RATE 115200

#endif