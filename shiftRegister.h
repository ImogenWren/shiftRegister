/* shiftRegister.h

    Simple API for interacting with a 4094 shift register, and accessing pins in a similar manner to other arduino pins.

    Imogen Heard
    5.05.2022

  Shiftregister pin defintions are tied to bitmasks that can be applied to the shiftregister output


  #define Q0 0b00000001
  #define Q1 0b00000010
  #define Q2 0b00000100
  #define Q3 0b00001000
  #define Q4 0b00010000
  #define Q5 0b00100000
  #define Q6 0b01000000
  #define Q7 0b10000000



*/




#ifndef shiftRegister_h
#define shiftRegister_h

#if (ARDUINO >=100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif







class shiftRegister
{
  public:

    // constructor
    shiftRegister(char pico_pin = 11, char sck_pin = 13, char latch_pin = 8);

    // Methods

    void begin(uint32_t baudrate = 115200);                                               // Begin function sets up output pins

    void allWrite(unsigned char pinNumber, bool state);                                   // aims to tie shiftWrite and digitalWrite together such that any pinnumber can be passed to set the correct output. Making operation seamless between shift register pins and arduino

    void allOff();

    void shiftWrite(unsigned char bitmask, bool state);                                   // Mirrors function of digitalWrite for shiftRegister channels

    void printByte(unsigned char bite);                                                   // Prints chars or bytes in binary for easy debugging


    // Function outputs the exact byte passed to shift register, regardless of previous data
    // Note the only function that actually outputs to hardware so far - the rest are software functions only.
    // It is best (at the moment) to track the current state of the shiftRegisters outputs, and use this to update this global byte, unless you want to totally
    // overwrite all shift register outputs
    void overwriteOutput(unsigned char bite);


    void overwriteState(unsigned char bite);                                              // Another function here to overwrite shiftstate? Does the same operation as overwriteOutput but also updates shiftState

    void printState();                                                                    // Prints the current state of the output bits

    void testShiftReg();                                                                  // Sequentually lights up shiftReg outputs for testing



#define Q0 0b00000001
#define Q1 0b00000010
#define Q2 0b00000100
#define Q3 0b00001000
#define Q4 0b00010000
#define Q5 0b00100000
#define Q6 0b01000000
#define Q7 0b10000000

    unsigned char shiftPinArray[8] {Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7};                      // Useful for accessing shift register pins in an array

  private:


    unsigned char setBits(unsigned char currentData, unsigned char bitmask);              // Sets 1 bits in bitmask

    unsigned char clearBits(unsigned char currentData, unsigned char bitmask);            // Only resets 0 bits in bitmask, leaves others unchanged

    unsigned char flipBits(unsigned char currentData, unsigned char bitmask);             // Flips all 1 bits using bitmask

    unsigned char flipAllBits(unsigned char bits);                                        // Flips all the bits in a byte - very useful for generating bitmasks for mirroring digtalWrite function for shift register

    char dataPin  = 11;
    char clockPin = 13;
    char latchPin = 8;


    unsigned char shiftState = 0b00000000;   // Global Variable to hold the state of the shiftRegister


};


#endif
