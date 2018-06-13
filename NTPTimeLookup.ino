//-----------------------UDP------------------------
WiFiUDP udp;

unsigned int localPort = 4000;

void startUDPService() {
  Serial.println("Starting UDP");
  udp.begin(localPort);
}


//------------------------NTP-----------------------
RTC_DATA_ATTR int bootCount = 0;


IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "de.pool.ntp.org";
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

unsigned long sendNTPpacket(IPAddress& address)
{
  #if serialDebug == true
  Serial.println("sending NTP packet...");
  #endif
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

unsigned long getTimeStamp() {
  bool timeStampFlag = false;
  while (!timeStampFlag) {
    WiFi.hostByName(ntpServerName, timeServerIP);
    #if serialDebug == true
    Serial.print("Time Server IP: ");
    Serial.println(timeServerIP);
    #endif
    sendNTPpacket(timeServerIP);
    int cb = udp.parsePacket();
    if (!cb) {
      #if serialDebug == true
      Serial.println("no packet yet");
      #endif
    }
    else {
      #if serialDebug == true
      Serial.print("packet received, length=");
      Serial.println(cb);
      #endif
      // We've received a packet, read the data from it
      udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

      //the timestamp starts at byte 40 of the received packet and is four bytes,
      // or two words, long. First, esxtract the two words:

      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      #if serialDebug == true
      Serial.println("---------------------------------------------------");
      #endif
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      #if serialDebug == true
      Serial.print("Seconds since Jan 1 1900 = " );
      Serial.println(secsSince1900);

      // now convert NTP time into everyday time:
      Serial.print("Unix time = ");
      #endif
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = secsSince1900 - seventyYears;
      #if serialDebug == true
      // print Unix time:
      Serial.println(epoch);
      #endif
      
      t = epoch;
      #if serialDebug == true
      // print the hour, minute and second:
      Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
      Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
      Serial.print(':');
      #endif
      if ( ((epoch % 3600) / 60) < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        #if serialDebug == true
        Serial.print('0');
        #endif
      }
      #if serialDebug == true
      Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
      Serial.print(':');
      #endif
      if ( (epoch % 60) < 10 ) {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        #if serialDebug == true
        Serial.print('0');
        #endif
      }
      #if serialDebug == true
      Serial.println(epoch % 60); // print the second
      // print the hour, minute and second:
      Serial.print("Your local time is ");       // UTC is the time at Greenwich Meridian (GMT)
      Serial.print(((epoch  % 86400L) / 3600) + 2); // print the hour (86400 equals secs per day)
      Serial.print(':');
      #endif
      if ( ((epoch % 3600) / 60) < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        #if serialDebug == true
        Serial.print('0');
        #endif
      }
      #if serialDebug == true
      Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
      Serial.print(':');
      #endif
      if ( (epoch % 60) < 10 ) {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        #if serialDebug == true
        Serial.print('0');
        #endif
      }
      #if serialDebug == true
      Serial.println(epoch % 60); // print the second
      Serial.println("---------------------------------------------------");
      #endif
      timeStampFlag = true;
      return(secsSince1900);
    }
    // wait ten seconds before asking for the time again
    delay(10000);
  }
}

