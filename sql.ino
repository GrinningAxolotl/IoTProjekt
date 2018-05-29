//SQL INSERT

//Wifi Verbindung aufbauen HOME
//IPAddress server_addr(192,168,43,126); // IP of the MySQL *server* here

//Wifi Verbindung aufbauen FH
IPAddress server_addr(192,168,100,130);
char user[] = "esp32";              // MySQL user login username
char password[] = "47uWrF267aV";        // MySQL user login password

// Sample query
char INSERT_DATA[] = "INSERT INTO weather_station.dht22 (sender_id, temp, humidity) VALUES ('%s','%s','%s')";
char query[128];
char temperature[10];
char humidity[10];
char macAdr[13];

bool connectSQL(){
  //delay(5000);
  Serial.print("Connecting to SQL... ");
  if (conn.connect(server_addr, 3306, user, password)){
    Serial.println("OK.");
    return 1;
  }
  else{
    Serial.println("FAILED.");
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
    sprintf(macAdr, "%X%X%X%X%X%X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    //Serial.printf("MAC Adresse String: %s", macAdr);
}

void sendTemptoSql(){
if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    //convert float to string
    //dtostrf(float, minimum width, precision, character array);
    dtostrf(SensorValues.vTemp, 1, 1, temperature);
    dtostrf(SensorValues.vHydro, 1, 1, humidity);
    
    
    sprintf(query, INSERT_DATA, macAdr, temperature, humidity);
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    Serial.println("DHT22 Data recorded.");
   }
    else
      Serial.println("DHT22 Connection failed.");
    conn.close();
}

