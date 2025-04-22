// === INCLUDE === //

#include "tasks.h"
#include "config.h"

// === GLOBAL VARIABLES === //

// Task handles
TaskHandle_t servoTaskHandle = nullptr;

// === EXTERNALS === //

int servoPos[N_FINGERS] = {RETRACTED_POS_DEG, RETRACTED_POS_DEG, RETRACTED_POS_DEG};
int desiredPos[N_FINGERS] = {};

// Command to change finger friction via servo motor; will retract finger pads if isExtension is false; servoID is zero-indexed
void servoCommand(int servoID, bool isExtension){
    desiredPos[servoID] = (isExtension) ?  EXTENDED_POS_DEG : RETRACTED_POS_DEG;
}

// === TASK === //

void servoTask(void *pvParameters) {
    (void)pvParameters;

    /* Make the task execute at a specified frequency */
    const TickType_t xFrequency = configTICK_RATE_HZ / SERVO_TASK_FREQUENCY;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    std::copy(std::begin(servoPos), std::end(servoPos), desiredPos);

    Serial.println("Set up servoTask");

    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        for (int i = 0; i < N_FINGERS; i++){
            if (servoPos[i] < desiredPos[i]){
                servoPos[i] += 4;
            }
            else if (servoPos[i] > desiredPos[i]){
                servoPos[i] -= 4;
            }
            else {
                ; // Servo is in correct position, do nothing
            }
            // logging
            // Serial.print(">Servo_" + String(i) + "_pos:");
            // Serial.println(servoPos[i]);
            // Serial.print(">Servo_" + String(i) + "_desired:");
            // Serial.println(desiredPos[i]);
        }
    }
}