/********************************************************************************
 * Estudos RTOS
 *Exemplo de criação e utilização de Task
 * 
********************************************************************************/
//Biblioteca da plataforma arduino
#include <Arduino.h>

//Biblioteca do FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Mapeamento de Pino da LED
#define LED 2

//Variváeis para armazenamento do Handle das tasks
TaskHandle_t taskBlinkLedHandle = NULL;
TaskHandle_t taskReadSerialHandle = NULL;

//Protótipo das Tasks
void taskBlinkLed(void *pvParameters);
void taskReadSerial(void *pvParameters);

void setup() {
  Serial.begin(9600);
  xTaskCreate(taskBlinkLed, "taskBlinkLed", configMINIMAL_STACK_SIZE, NULL, 1, &taskBlinkLedHandle);
  xTaskCreate(taskReadSerial, "taskReadSerial", configMINIMAL_STACK_SIZE+1024, NULL, 2, &taskReadSerialHandle); //Task com maior prioridade
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelay(1000);
}

void taskBlinkLed(void *pvParameters){
  pinMode(LED,OUTPUT);
  while (1){
    digitalWrite(LED, !digitalRead(LED));
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void taskReadSerial(void *pvParameter){
  int cont = 0;
  while (1){
    Serial.println("Read Serial: " + String(cont++));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}