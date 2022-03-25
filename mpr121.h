#include <bus1_MPR121.h> // use this modified adafruit library to allow use of other i2c busses - https://github.com/gawainhewitt/bus1_MPR121
// #include "Adafruit_MPR121.h" // alternatively you can use the standard Adafruit library if using bus 0
#include <Wire.h>

Adafruit_MPR121 mprBoard_A = Adafruit_MPR121();

uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;

void init_mpr121()
{
    if (!mprBoard_A.begin(0x5A)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1);
    }
    Serial.println("MPR121 A found!");

    // mprBoard_A.setThresholds(0x30, 0x05);

    mprBoard_A.writeRegister(MPR121_ECR, 0x00); //stop mpr121
    mprBoard_A.setThreshholds(0x05, 0x00); // maybe i'm using an old library but this is the set thresholds that works!
    mprBoard_A.writeRegister(MPR121_ECR, 0x8F); // start mpr121 again

}
