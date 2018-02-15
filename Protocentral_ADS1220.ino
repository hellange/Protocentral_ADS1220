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

  float avgVout;
  float lastAverage;
  float lastRaw;
  int smoothingSamples = 5;
void setup()
{
    Serial.begin(115200);            //115200 57600
  DAC.init();
}

void loop()
{

  if(DAC.checkDataAvilable() == true) {
    float Vout = DAC.convertToMv();
    //delay(75);
    delay(75);
    avgVout = DAC.smoothing(avgVout, smoothingSamples, Vout);
//    Serial.print("Raw:");  
//    Serial.print(Vout, 3);
//    Serial.print(" mV");  
//    Serial.print("(");  
//    Serial.print(( Vout - lastRaw)*1000, 1);  
//    Serial.print(" uV),"
    Serial.print("average:");
    Serial.print(avgVout, 3);
    Serial.print(" mV");  
    Serial.print("(");  
    Serial.print(( avgVout - lastAverage)*1000, 1);  
    Serial.println("uV)");  
    lastAverage = avgVout;
    lastRaw = Vout;
     //Serial.print("Vout in mV : ");  
    //Serial.print(Vout, 3);
    //Serial.print(" average:");
    //Serial.print(avgVout, 4);
    //Serial.print("  32bit HEX : ");
    // Serial.println(bit32,HEX);
  }
}
 
 
