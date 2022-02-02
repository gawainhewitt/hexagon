#include <Wire.h>
char card[10];
unsigned long cardNumber = 0;
int x = 0;
unsigned long card1 = 0xC27E4E43;
unsigned long card2 = 0x4AEF322;

#define Wire Wire1 // use this to specify a different i2c bus - For example: #define Wire Wire1 means that we are using bus 1 instead of bus 0 as default.


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  x = 0;
  Wire.requestFrom(8, 11);    // request 10 bytes from peripheral device #8

  while (Wire.available()) { // peripheral may send less than requested
    card[x] = Wire.read();
    x = x+1;
  }

  Serial.println("as char");
  Serial.println(card);         // print the number

  String convertCard = String(card);

  Serial.println("as string");
  Serial.println(convertCard);         // print the number

  cardNumber = convertCard.toInt();

  Serial.println("as number");
  Serial.println(cardNumber);         // print the number - this is not always correct

  if (convertCard == card1){
      Serial.println("SUCCESS 1!");

  }

  if (convertCard == card2){
      Serial.println("SUCCESS 2!");

  }



}
