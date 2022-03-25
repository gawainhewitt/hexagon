// #include <Wire.h> // this is in MPR121.h
#include "constants.h"
#include "mpr121.h"
#include "wavFilePlayer.h"
#include "reboot.h"
char card[10];
unsigned long cardNumber = 0;
unsigned long card1 = 0x445B722;
unsigned long card2 = 0x4AEF322;
unsigned long card3 = 0x44DB722;
unsigned long lastCard;

#define Wire Wire1 // use this to specify a different i2c bus - For example: #define Wire Wire1 means that we are using bus 1 instead of bus 0 as default.

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  init_mpr121();
  init_player();
  pinMode(rebootButton, INPUT_PULLUP);
  pinMode(volumePin, INPUT);
  delay(500);
}

void readCard(){
  int x = 0;
    Wire.requestFrom(8, 11);    // request 10 bytes from peripheral device #8

    while (Wire.available()) { // peripheral may send less than requested
      card[x] = Wire.read();
      x = x+1;
    }

    // Serial.println("as char");
    // Serial.println(card);         // print the number

    String convertCard = String(card);

    // Serial.println("as string");
    // Serial.println(convertCard);         // print the number


    if (convertCard == card1 && lastCard != card1){
        Serial.println("SUCCESS 1!");
        lastCard = card1;
        for(int i = 0; i < 48; i++){
          toPlay[i] = shapes[i];
        }
    }

    if (convertCard == card2 && lastCard != card2){
        Serial.println("SUCCESS 2!");
        lastCard = card2;
          for(int i = 0; i < 48; i++){
          toPlay[i] = notes[i];
        }
    }

    if (convertCard == card3 && lastCard != card3){
        Serial.println("SUCCESS 3!");
        lastCard = card3;
          for(int i = 0; i < 48; i++){
          toPlay[i] = space[i];
        }
    }

    if (convertCard == "no card"){
        lastCard = 0;
    }
}

void changeVolume() {
  int knob = analogRead(volumePin); // knob = 0 to 1023
  float gain = (float)knob / 1023.0;
  amp1.gain(gain);
  amp2.gain(gain);
}

void touchFunction() {
  currtouched1 = mprBoard_A.touched();

  //For A----------------------------------------------------------
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched of A");
      if(lastCard != 0){
        playSound(i);
      }
    }

    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" released of A");
      stopSound(i);
    }
  }

  lasttouched1 = currtouched1;
  // kill_dead_notes();
}

void loop() {
  if(digitalRead(rebootButton) == LOW){
    doReboot();
  }
  readCard(); // read RFID card
  changeVolume();
  touchFunction();
}
