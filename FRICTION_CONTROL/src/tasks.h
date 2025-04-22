#ifndef TASKS_H
#define TASKS_H

// === INCLUDE === //

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include "config.h"

// === EXTERNALS === //

// Task Handles
extern TaskHandle_t debugTaskHandle;
extern TaskHandle_t serialTaskHandle;

// Tasks
void debugTask(void *pvParameters);
void serialTask(void *pvParameters);

// Shared Types
enum MessageType {
    PING,
    EXTEND,
    RETRACT,
    ERROR,
};

enum SerialErrorCode {
    NOT_SERIAL_MSG,
    NO_KEY_VAL_PAIR,
    UNKNOWN_EXECUTION,
    UNKNOWN_KEY,
};

struct Message {
    MessageType type;
    union {
        bool pingValue;     // PING
        int servoValue;     // EXTEND, RETRACT
        int errorCode;      // ERROR
    };
};

#endif