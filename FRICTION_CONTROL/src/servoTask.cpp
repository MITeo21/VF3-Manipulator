// === INCLUDE === //

#include "tasks.h"
#include "config.h"

#include <ESP32Servo.h>

// === GLOBAL VARIABLES === //

// Task handles
TaskHandle_t servoTaskHandle = nullptr;

Servo servo0, servo1, servo2;
Servo servoList[N_FINGERS] = {servo0, servo1, servo2};
int servoPinList[N_FINGERS] = {SERVO_0_PIN, SERVO_1_PIN, SERVO_2_PIN};
// Published values for SG90 servos; adjust if needed
int minUs = 500;
int maxUs = 4000;
ESP32PWM pwm;

int servoPos[N_FINGERS] = {RETRACTED_POS_DEG, RETRACTED_POS_DEG, RETRACTED_POS_DEG};
int desiredPos[N_FINGERS] = {};

// === EXTERNALS === //

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

    for (int i = 0; i < N_FINGERS; i++){
        ESP32PWM::allocateTimer(i);
        servoList[i].setPeriodHertz(50);
        servoList[i].attach(servoPinList[i], minUs, maxUs);
        desiredPos[i] = servoPos[i];
    }

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

            servoList[i].write(servoPos[i]);
        }
    }
}