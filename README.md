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

_Accessing the shiftregister pins is now almost as simple as using the `digitalWrite(PIN_NUMBER, PIN_STATE);` arduino function.
