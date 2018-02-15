/*************************************************************
Protocentral_ADS1220.ino
this example gives differential voltage across the AN0 And AN1 in mV
Hooking-up with the Arduino
|ads1220 pin label| Pin Function         |Arduino Connection|
|-----------------|:--------------------:|-----------------:|
| DRDY            | Data ready Output pin|  D6              |             
| MISO            | Slave Out            |  D12             |
| MOSI            | Slave In             |  D11             |
| SCLK            | Serial Clock         |  D13             |
| CS              | Chip Select          |  D7              |
| DVDD            | Digital VDD          |  +5V             |
| DGND            | Digital Gnd          |  Gnd             |
| AN0-AN3         | Analog Input         |  Analog Input    |
| AVDD            | Analog VDD           |  -               |
| AGND            | Analog Gnd           |  -               |
*************************************************************/

#include <SPI.h>
#include "Dac.h"

  float sum;
  float meanVout;
  int measurements;
  int samplesPr = 10;
  float average;
  float lastAverage;
  float lastRaw;
  
void setup()
{
  DAC.init();
}

void loop()
{

  if(DAC.checkDataAvilable() == true) {
    float Vout = DAC.convertToMv();
    delay(75);
    average = DAC.smoothing(average, 2, Vout);
    sum = sum + Vout;
    if (++measurements == 2) {
    //if (++measurements == samplesPr) {
      measurements = 0;
      meanVout = sum / samplesPr;
      meanVout -= 0.010; //offset
      sum = 0;
      Serial.print("Raw:");  
      Serial.print(Vout, 3);
      //Serial.print(meanVout, 3);
      Serial.print(" mV");  
      Serial.print("(");  
      Serial.print(( Vout - lastRaw)*1000, 0);  
      Serial.print(" mV), average:");
      Serial.print(average, 3);
      Serial.print(" mV");  
      Serial.print("(");  
      Serial.print(( average - lastAverage)*1000, 0);  
      Serial.println("uV)");  
      lastAverage = average;
      lastRaw = Vout;
    }
    //Serial.print("Vout in mV : ");  
    //Serial.print(Vout, 3);
    //Serial.print(" average:");
    //Serial.print(average, 4);
    //Serial.print("  32bit HEX : ");
    // Serial.println(bit32,HEX);
  }
}
 
 
