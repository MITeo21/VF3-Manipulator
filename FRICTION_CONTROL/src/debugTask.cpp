// === INCLUDE === //

#include "tasks.h"
#include "config.h"

// === GLOBAL VARIABLES === //

// Task handles
TaskHandle_t debugTaskHandle = nullptr;

// === EXTERNALS === //



// === TASK === //

void debugTask(void *pvParameters) {
    (void)pvParameters;

    /* Make the task execute at a specified frequency */
    const TickType_t xFrequency = configTICK_RATE_HZ / DEBUG_TASK_FREQUENCY;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Serial.println("Set up debugTask");

    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        Serial.println("This is the debug task");
    }
}