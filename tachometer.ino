#include <interrupt.h>


/* This code is written for an Adafruit Trinket microcontroller board, and
  implemented with a 7 segment display board that was laying around the 
  hackerspace. */

//Pin connected to ST_CP of 74HC595
int latchPin = 0;
//Pin connected to SH_CP of 74HC595
int clockPin = 1;
////Pin connected to DS of 74HC595
int dataPin = 3;

int thousands = 0;
int hundreds = 0;
int tens = 0;
int ones = 0;

// These bytes are trial-and-error digits for the seven segment displays I have.

#define zero B11111100
#define one B01100000
#define two B11011010
#define three B11110010
#define four B01100110
#define five B10110110
#define six B10111110
#define seven B11100000
#define eight B11111110
#define nine B11100110


//numbers is used to call specific digits
byte numbers[10] = {zero, one, two, three, four, five, six, seven, eight, nine}; 

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  attachInterrupt(0, increment, FALLING); // 'increment' is my ISR
}


unsigned long time = micros();
unsigned long newTime = micros();
unsigned long delta = 0;



unsigned long rpm = 0;
unsigned long oldTime = 0;
unsigned long updateTime = 0;

void loop() {

  time = micros();
  rpm = 30000000/delta;
  update();
  if( time - updateTime > 30000) { //this statement reduces the refresh rate
    writeDisplay();
  }
}


//Our ISR needs to be as brief as possible, so I just determine the time since
//the last interrupt was triggered
void increment() {
  oldTime = newTime;
  newTime = time;
  delta = newTime - oldTime;
}

void update() {  
  int newRpm = rpm;
  thousands = 0;
  hundreds = 0;
  tens = 0;
  ones = 0;

  thousands = newRpm / 1000;
  
  newRpm -= thousands*1000;

  hundreds = newRpm / 100;
  
  newRpm -= hundreds*100;
  
  tens = newRpm / 10;
  
  newRpm -= tens*10;
  
  ones = newRpm;
    
}

void writeDisplay() {
  updateTime = micros();
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[ones]);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[tens]);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[hundreds]);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[thousands]);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[zero]);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[zero]);
  digitalWrite(latchPin, HIGH);
}
