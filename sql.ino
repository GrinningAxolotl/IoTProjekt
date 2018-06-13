//SQL INSERT

//Wifi Verbindung aufbauen HOME
//IPAddress server_addr(192,168,43,126); // IP of the MySQL *server* here

//Wifi Verbindung aufbauen FH
IPAddress server_addr(192,168,100,199);
char user[] = "esp32";              // MySQL user login username
char password[] = "47uWrF267aV";        // MySQL user login password

// Sample query
char INSERT_DATA_DHT[] = "INSERT INTO weather_station.dht22 (sender_id, temp, humidity) VALUES ('%s','%s','%s')";
char INSERT_DATA_CCS[] = "INSERT INTO weather_station.ccs811 (sender_id, CO2, TVOC) VALUES ('%s','%s','%s')";
char INSERT_DATA_BMP[] = "INSERT INTO weather_station.bmp280 (sender_id, temp, pressure) VALUES ('%s','%s','%s')";
char INSERT_DATA_SDS[] = "INSERT INTO weather_station.sds011 (sender_id, PM10, PM25) VALUES ('%s','%s','%s')";
char query[128];
char tempDHT[10];
char tempBMP[10];

char humidity[10];
char co2[10];
char tvoc[10];

char pressure[10];
char fdust10[10]; 
char fdust25[10];
char macAdr[13];

bool connectSQL(){
  //delay(5000);
  #if serialDebug == true
  Serial.print("Connecting to SQL... ");
  #endif
  if (conn.connect(server_addr, 3306, user, password)){
    #if serialDebug == true
    Serial.println("OK.");
    #endif
    return 1;
  }
  else{
    #if serialDebug == true
    Serial.println("FAILED.");
    #endif
    return 0;
  }

  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);

}

void saveMacforSQLConnection(){
  
    //WiFi.macAddress(mac);
    uint8_t mac[6];
      
    WiFi.macAddress(mac);
    //Serial.print("MAC Adress char Array: ");
    //Serial.printf("%X : %X : %X : %X : %X : %X \n",mac[0], mac[1], mac[2],mac[3], mac[4], mac[5]);
    #if serialDebug == true
    sprintf(macAdr, "%X%X%X%X%X%X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    #endif
    //Serial.printf("MAC Adresse String: %s", macAdr);
}

void sendTemptoSql(){
if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    //convert float to string
    //dtostrf(float, minimum width, precision, character array);
    dtostrf(SensorValues.vTempDHT, 1, 1, tempDHT);
    dtostrf(SensorValues.vTempBMP, 1, 1, tempBMP);
    dtostrf(SensorValues.vHydro, 1, 1, humidity);
    dtostrf(SensorValues.vPressure, 1, 1, pressure);
    dtostrf(SensorValues.vFineDust25, 1, 1, fdust25);
    dtostrf(SensorValues.vFineDust10, 1, 1, fdust10);
    dtostrf(SensorValues.vCO2, 1, 1, co2);
    dtostrf(SensorValues.vTVOC, 1, 1, tvoc);
    #if serialDebug == true
    sprintf(query, INSERT_DATA_DHT, macAdr, tempDHT, humidity);
    #endif
    cur_mem->execute(query);
    #if serialDebug == true
    sprintf(query, INSERT_DATA_BMP, macAdr, tempBMP, pressure);
    #endif
    cur_mem->execute(query);
    #if serialDebug == true
    sprintf(query, INSERT_DATA_SDS, macAdr, fdust10, fdust25);
    #endif
    cur_mem->execute(query);
    #if serialDebug == true
    sprintf(query, INSERT_DATA_CCS, macAdr, co2, tvoc);
    #endif
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used  
    delete cur_mem;
    #if serialDebug == true
    Serial.println("Sensor Data recorded.");
    #endif
   }
    else{
      #if serialDebug == true
      Serial.println("Connection failed.");
      #endif
    }
    conn.close();
}


