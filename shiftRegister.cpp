/* shiftRegister.cpp

    Simple API for interacting with a 4094 shift register, and accessing pins in a similar manner to other arduino pins.

    Imogen Heard
    5.05.2022


*/


#include "shiftRegister.h"




// Constructor
// Passes pin definitions to shiftRegister Object

shiftRegister::shiftRegister(char pico_pin, char sck_pin, char latch_pin):
  dataPin(pico_pin),
  clockPin(sck_pin),
  latchPin(latch_pin)
{
}


void shiftRegister::begin(uint32_t baudrate) {
 // Serial.begin(baudrate);
  // while ( !Serial ) delay(10);   // Might be required for Nano IoT 33
  delay(2000);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}


// Aims to mirror the function of digitalWrite but for shift register channels
void shiftRegister::shiftWrite(unsigned char bitmask, bool state) {
  if (state) {
    shiftState = shiftRegister::setBits(shiftState, bitmask);
  } else {
    bitmask = shiftRegister::flipAllBits(bitmask);
    shiftState = shiftRegister::clearBits(shiftState, bitmask);
  }
  shiftRegister::overwriteOutput(shiftState);
}


// Another function here to overwrite shiftstate? Does the same operation as overwriteOutput but also updates shiftState
void shiftRegister::overwriteState(unsigned char bite) {
  shiftState = bite;
  shiftRegister::overwriteOutput(shiftState);
}


// Function outputs the exact byte passed to shift register, regardless of previous data
// Note the only function that actually outputs to hardware so far - the rest are software functions only.
// It is best (at the moment) to track the current state of the shiftRegisters outputs, and use this to update this global byte, unless you want to totally
// overwrite all shift register outputs
void shiftRegister::overwriteOutput(unsigned char bite) {
  digitalWrite(latchPin, HIGH);
  delay(100);
  shiftOut(dataPin, clockPin, MSBFIRST, bite);
  delay(100);
  digitalWrite(latchPin, LOW);
}




#define LARGEST_PINNUMBER 30

// aims to tie shiftWrite and digitalWrite together such that any pinnumber can be passed to set the correct output.
// Making operation seamless between shift register pins and arduino
// VERY UNTESTED
// Probably need a better way of doing this
void shiftRegister::allWrite(unsigned char pinNumber, bool state) {
  if (pinNumber >= LARGEST_PINNUMBER) {
    shiftRegister::shiftWrite(pinNumber, state);
  } else {
    digitalWrite(pinNumber, state);
  }
}


void shiftRegister::allOff() {
  shiftState = 0b00000000;
  shiftRegister::overwriteOutput(shiftState);
}



// Bit operations used in backend to update the shiftState variable

// Only sets 1 bits in bitmask, leaves others unchanged
unsigned char shiftRegister::setBits(unsigned char currentData, unsigned char bitmask) {
  currentData |= bitmask;
  return currentData;
}

// Only resets 0 bits in bitmask, leaves others unchanged
unsigned char shiftRegister::clearBits(unsigned char currentData, unsigned char bitmask) {
  currentData &= bitmask;
  return currentData;
}


// Flips all 1 bits using bitmask
unsigned char shiftRegister::flipBits(unsigned char currentData, unsigned char bitmask) {
  currentData ^= bitmask;
  return currentData;
}



// Flips all the bits in a byte - very useful for generating bitmasks for mirroring digtalWrite function for shift register
unsigned char shiftRegister::flipAllBits(unsigned char bits) {
  bits = flipBits(bits, 0b11111111);
  return bits;
}



// Prints chars or bytes in binary for easy debugging
void shiftRegister::printByte(unsigned char bite) {
  char  buffer[2];
  for (int i = 0; i < 8; i++) {
    sprintf(buffer, "%d", !!((bite << i) & 0x80));
    Serial.print(buffer);
  }
  Serial.print("\n");
}


void shiftRegister::printState() {
  shiftRegister::printByte(shiftState);
}


// Runs through sequentially turning pins high then low to test all outputs
void shiftRegister::testShiftReg() {
  for (int i = 0; i < 8; i++) {
    shiftRegister::shiftWrite(shiftPinArray[i], HIGH);
    shiftRegister::printState();
    delay(200);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    shiftRegister::shiftWrite(shiftPinArray[i], LOW);
    shiftRegister::printState();
    delay(200);
  }
  delay(2000);
}
