void core2Task(void * parameter){
  timeval timestamp;  
  while(1){
    
    xSemaphoreTake( xMutex, portMAX_DELAY );
    Serial.println("Task 2 changing values");
    gettimeofday(&timestamp,0);
    
    readSDS011();
    readDHT();
    bmpRead();
    ccsRead(); 
    SensorValues.vTime = timestamp.tv_sec;
    
    xSemaphoreGive( xMutex );

    delay(2000);
  }
  }
