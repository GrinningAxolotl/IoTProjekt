#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_sleep.h>
#include <esp_clk.h>
#include <Time.h>
#include <SPI.h>
#include<string>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 20 /* Time ESP32 will go to sleep (in seconds) */

TaskHandle_t xTask1;
TaskHandle_t xTask2;
SemaphoreHandle_t xMutex;

WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

HardwareSerial Serial2(2);

typedef struct SensorData {
  int vPressure = 0;
  float vFineDust25 = 0;
  float vFineDust10 = 0;
  float vTemp = 0;
  float vHydro = 0;
  uint16_t vCO2 = 0;
  uint16_t vTVOC = 0;
  unsigned long vTime =0;
} SensorData;

RTC_DATA_ATTR SensorData SensorValues;
time_t t;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1, 12, 13); 
  //dht.setup(17);
  //setTime(t);
  xMutex = xSemaphoreCreateMutex();

  
  
  xTaskCreatePinnedToCore(
      core1Task,           /* Task function. */
      "core1Task",        /* name of task. */
      10000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      1,                        /* priority of the task */
      &xTask1,                /* Task handle to keep track of created task */
      0);                    /* pin task to core 0 */
      
  xTaskCreatePinnedToCore(
      core2Task,           /* Task function. */
      "core2Task",        /* name of task. */
      10000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      2,                        /* priority of the task */
      &xTask2,            /* Task handle to keep track of created task */
      1);                 /* pin task to core 1 */  
}

void loop() {
}
