/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout 
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/*#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10*/

Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);


bool connectedBMP = false;

void bmpRead() {
    if(connectedBMP == false){
      while(!bme.begin()) {  
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
        delay(5000);
      }
      connectedBMP = true;
    }
    else{    

    SensorValues.vTempBMP = bme.readTemperature();
    SensorValues.vPressure = bme.readPressure();
    SensorValues.vAltitude = bme.readAltitude(1013.25); // this should be adjusted to your local forcase
    
    Serial.println();
    delay(2000);
    }
}

