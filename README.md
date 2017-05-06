# Teensy-Lua
## An experiment running Lua on the Teensy 3.2.

This project takes the Lua implementation in eLua and compiles it for the Teensy 3.2. This is not a full implementation of eLua.

To compile it you need to have installed Arduino and Teensyduino, define the variable ARDUINOPATH in the Makefile and simply run `make`.

The example load a program that blinks a LED.
