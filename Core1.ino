#define CONN_ESTABLISHED true
#define CONN_FAILED false

void core1Task(void * parameter){
  
  bool connectedToNetwork = CONN_FAILED;
  
  while(1){
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(10000);
    //scanNetworksTest();
    connectedToNetwork = connectToNetwork();
    if(connectedToNetwork == CONN_ESTABLISHED ){
      startUDPService();
      Serial.println(WiFi.macAddress());
      Serial.println(WiFi.localIP());
      SensorValues.vTime = getTimeStamp();
      saveMacforSQLConnection();

      //WiFi.disconnect(true);
    }

    xSemaphoreTake( xMutex, portMAX_DELAY );

    //send temperature to SQL database
    /*if (connectSQL())
    {
      sendTemptoSql();
    }
    */
    //Get Sensordata to Send via WLAN
    Serial.print("Druck:");
    Serial.println(SensorValues.vPressure);
    Serial.print("Feinstaub10:");
    Serial.println(SensorValues.vFineDust10);
    Serial.print("Feinstaub25:");
    Serial.println(SensorValues.vFineDust25);
    Serial.print("Temperatur:");
    Serial.println(SensorValues.vTemp);
    Serial.print("Luftfeuchtigkeit:");
    Serial.println(SensorValues.vHydro);
    Serial.print("CO2:");
    Serial.println(SensorValues.vCO2);
    Serial.print("TVOC:");
    Serial.println(SensorValues.vTVOC);
    Serial.print("Timestamp:");
    Serial.println(SensorValues.vTime);
    
    xSemaphoreGive( xMutex );
    
    Serial.println("Going to sleep now");
    
    esp_deep_sleep_start();
    }
  }
