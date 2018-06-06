#include "DHTesp.h"

DHTesp dht;

void startDHT(uint16_t dht_pin){
  dht.setup(dht_pin);
}

void readDHT()
{
  
  delay(dht.getMinimumSamplingPeriod());

  SensorValues.vTempDHT = dht.getTemperature();
  SensorValues.vHydro = dht.getHumidity();
  
}
