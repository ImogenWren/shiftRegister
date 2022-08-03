# shiftRegister
_Simple API for interacting with a 4094 shift register, Accessible using Arduino friendly API_

Imogen Heard <br>
05.05.2022



## Use

### Precompiler Requirements<br>

`#include <shiftRegister.h>   // Libary include`  <br> <br>

### Object Constructors

Declaring a shiftRegister object:

`shiftRegister shiftReg(MOSI_PIN, SCK_PIN, LATCH_PIN);` <br>

<br>

### Setup Functions:

Setup function must be run once before accessing shiftRegister object to set pins to output mode. <br>

`shiftReg.begin();`<br> <br>

<br><br>


### Accessing Shiftregister Pins

_Accessing the shiftregister pins is now almost as simple as using the `digitalWrite(PIN_NUMBER, PIN_STATE);` arduino function_<br>

ShiftRegister pins can now be accessed using the following AP: <br>

`shiftReg.shiftWrite(PIN_NUMBER, STATE);` <br><br>

Where:
- PIN_NUMBER is the shift register pin, named Q0, to Q7.
- STATE is HIGH or LOW, true or false, or 1 or 0.

## Additional Methods

To print the shiftState register to the serial monitor.
`shiftReg.printState();` <br><br>


## shiftPinArry

`shiftPinArray[8];` <Br>
  Contains an array of all shiftregister pin numbers. 
