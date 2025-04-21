#ifndef TASKS_H
#define TASKS_H

// === INCLUDE === //

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include "config.h"

// === EXTERNALS === //

// Task Handles
extern TaskHandle_t debugTaskHandle;

// Tasks
void debugTask(void *pvParameters);

#endif