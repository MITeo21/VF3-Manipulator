// === INCLUDE === //

#include "tasks.h"
#include "config.h"

#include "freertos/task.h"

// === GLOBAL VARIABLES === //

// === SETUP === //

void setup() {

  Serial.begin(115200);
  Serial.println("Hello World!");

  // === initialize SEMAPHORES AND MUTEXES === //

  // === CREATE TASKS === //
#if DEBUG_TASK_ENABLE
  xTaskCreate(
    debugTask,           // Function name
    "DEBUG",             // Text name
    2500,                // Stack size (bytes)
    NULL,                // Parameter for task
    DEBUG_TASK_PRIORITY, // Priority
    &debugTaskHandle     // Pointer
  );
#endif

  Serial.println("End setup()");
  // DO NOT call vTaskStartScheduler();
}

// --- LOOP --- //

void loop() {
  // leave empty but do not remove delay
  vTaskDelay(pdMS_TO_TICKS(1000));
}