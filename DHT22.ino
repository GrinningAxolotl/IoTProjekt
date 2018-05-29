#include "DHTesp.h"

DHTesp dht;

void readDHT()
{
  
  delay(dht.getMinimumSamplingPeriod());

  SensorValues.vTemp = dht.getTemperature();
  SensorValues.vHydro = dht.getHumidity();
  
}
