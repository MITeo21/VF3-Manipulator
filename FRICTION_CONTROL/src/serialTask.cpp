// === INCLUDE === //

#include "tasks.h"
#include "config.h"

#include <queue>

// === GLOBAL VARIABLES === //

// Task handles
TaskHandle_t serialTaskHandle = nullptr;

std::queue<Message> incomingMessages;

// === EXTERNALS === //

// === FUNCTIONS === //

// Takes a single message like "<EXTEND:2>" and outputs the correct message 
Message parseMessage(String input){
    Message output;
    String key;
    String value;
    if (input.startsWith("<") && input.endsWith(">")) {
        input = input.substring(1, input.length() - 1);
    } else {
        output.type = MessageType::ERROR;
        output.errorCode = SerialErrorCode::NOT_SERIAL_MSG;
        return output;  
    }

    int colonIndex = input.indexOf(':');
    
    if (colonIndex!=-1){
        key = input.substring(0,colonIndex);
        value = input.substring(colonIndex+1);
        value.toLowerCase();
        key.toUpperCase();
    } else {
        output.type = MessageType::ERROR;
        output.errorCode = SerialErrorCode::NO_KEY_VAL_PAIR;
        return output;  
    }

    // Sort message types and add to processing queue
    if (key == "PING"){
        output.type = MessageType::PING;
        output.pingValue = value.toInt();
    }
    else if (key == "EXTEND"){
        output.type = MessageType::EXTEND;
        output.servoValue = value.toInt();
    }
    else if (key == "RETRACT"){
        output.type = MessageType::RETRACT;
        output.servoValue = value.toInt();
    }
    else{
        output.type = MessageType::ERROR;
        output.errorCode = SerialErrorCode::UNKNOWN_KEY;
    }

    return output;
}

void executeCommand(Message message){
    String returnString = "";
    switch (message.type){
        case MessageType::PING:
            returnString = "<PONG:"+ String(message.pingValue == 1) + ">";
            break;
        case MessageType::EXTEND:
            // TODO: servo command here
            returnString = "<EXTENDED:" + String(message.servoValue) + ">";
            break;
        case MessageType::RETRACT:
            // TODO: servo command here
            returnString = "<RETRACTED:" + String(message.servoValue) + ">";
            break;
        case MessageType::ERROR:
            returnString = "<ERROR_CODE:" + String(message.errorCode) + ">";
            break;
        default:
            returnString = "<ERROR_CODE:" + String(SerialErrorCode::UNKNOWN_EXECUTION) + ">";
    }
    if (returnString != ""){
        Serial.println(returnString);
    }
}

// === TASK === //

void serialTask(void *pvParameters) {
    (void)pvParameters;

    /* Make the task execute at a specified frequency */
    const TickType_t xFrequency = configTICK_RATE_HZ / SERIAL_TASK_FREQUENCY;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Serial.println("Set up serialTask");

    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        String incoming;
        Message incomingMessage;
        
        // Check for new messages via serial
        while(Serial.available()>0){
            incoming = Serial.readStringUntil('\n');
            incomingMessage = parseMessage(incoming);
            incomingMessages.push(incomingMessage);
        }

        // Process received messages
        while(!incomingMessages.empty()){
            executeCommand(incomingMessages.front());
            incomingMessages.pop();
        }
    }
}
