void core2Task(void * parameter){
  timeval timestamp;  
  while(1){
    
    xSemaphoreTake( xMutex, portMAX_DELAY );
    gettimeofday(&timestamp,0);
    
    readSDS011();
    readDHT();
    bmpRead();
    ccsRead(); 
    SensorValues.vTime = timestamp.tv_sec;
    /*Serial.println("_______________________________________");
    Serial.print("Druck:"); Serial.println(SensorValues.vPressure);
    Serial.print("Feinstaub10:"); Serial.println(SensorValues.vFineDust10);
    Serial.print("Feinstaub25:"); Serial.println(SensorValues.vFineDust25);
    Serial.print("Temperatur:"); Serial.println(SensorValues.vTemp);
    Serial.print("Luftfeuchtigkeit:"); Serial.println(SensorValues.vHydro);
    Serial.print("CO2:"); Serial.println(SensorValues.vCO2);
    Serial.print("TVOC:"); Serial.println(SensorValues.vTVOC);
    Serial.print("Timestamp:"); Serial.println(SensorValues.vTime);
    Serial.println("_______________________________________");*/
    xSemaphoreGive( xMutex );

    delay(2000);
  }
  }
