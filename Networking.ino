

//------------------------WLAN / TCP-----------------

//Wifi Verbindung aufbauen HOME
//const char* ssid = "AndroidCS2";
//const char* pass =  "!5T7m577";

//Wifi Verbindung aufbauen FH
const char* ssid = "FH-Kiel-IoT-NAT";
const char* pass =  "!FH-NAT-001!";



String translateEncryptionType(wifi_auth_mode_t encryptionType) {

  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void scanNetworksTest() {

  int numberOfNetworks = WiFi.scanNetworks();

  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);

  for (int i = 0; i < numberOfNetworks; i++) {

    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));

    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");

  }
}

bool connectToNetwork() {
  bool connectionflag = false;
  int numberOfNetworks = WiFi.scanNetworks();

  Serial.println("Searching for configured SSID...");
  for (int j = 0; j < numberOfNetworks; j++) {
    if (String(ssid) == WiFi.SSID(j)) {
      Serial.println("Configured SSID found");
      connectionflag = true;
    }
  }
  if (connectionflag == true) {
    WiFi.begin(ssid, pass);
    Serial.print("Establishing connection to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected to network");
    return(true);
  }
  else {
    Serial.println("Configured Network not found");
    return(false);
  }
}


