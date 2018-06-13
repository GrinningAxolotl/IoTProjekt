void core2Task(void * parameter){
  timeval timestamp;  
  while(1){
    
    xSemaphoreTake( xMutex, portMAX_DELAY );
    delay(2000);
    gettimeofday(&timestamp,0);
    
    readSDS011();
    bmpRead();
    ccsRead();
    readDHT();
    SensorValues.vTime = timestamp.tv_sec;
    #if serialDebug == true
    Serial.println("_______________________________________");
    Serial.print("Druck:"); Serial.println(SensorValues.vPressure);
    Serial.print("Feinstaub10:"); Serial.println(SensorValues.vFineDust10);
    Serial.print("Feinstaub25:"); Serial.println(SensorValues.vFineDust25);
    Serial.print("Temperatur DHT:"); Serial.println(SensorValues.vTempDHT);
    Serial.print("Temperatur BMP:"); Serial.println(SensorValues.vTempBMP);
    Serial.print("Luftfeuchtigkeit:"); Serial.println(SensorValues.vHydro);
    Serial.print("CO2:"); Serial.println(SensorValues.vCO2);
    Serial.print("TVOC:"); Serial.println(SensorValues.vTVOC);
    Serial.print("Timestamp:"); Serial.println(SensorValues.vTime);
    Serial.println("_______________________________________");
    #endif
    xSemaphoreGive( xMutex );

    delay(2000);
  }
  }

