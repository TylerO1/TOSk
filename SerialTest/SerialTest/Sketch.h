/*
 * Main.cpp
 *
 * Created: 2/23/2014 12:27:08 PM
 *  Author: Tyler
 */


#ifndef SKETCH_H_
#define SKETCH_H_

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef UTILITY_MACROS_H_
#include "Utility\UtilityMacros.h"
#endif

#ifndef BUILDINFO_H_
#include "Utility/Buildinfo.h"
#endif

#include "ArduinoInterface.h"
//#include "uart.h"

/* LED Output */
const uint8_t LED = 13;

/* Delay between blinks */
const unsigned long DELAY_LENGTH = 450;

/* Serial Speed */
const unsigned long SERIAL_SPEED = 9600;

/* Serial Message */
const char* MESSAGE = "Hello World! - ";

void setup();
void loop();

class Test : private CArduinoInterface
{
	public:
	void SetRead(arduinoPinNames_E pin);
	void SetPullUP(arduinoPinNames_E pin);
	void SetWrite(arduinoPinNames_E pin);
	
	int ReadPin(arduinoPinNames_E pin);
	void ReadMultiplePins(portPinUser_s PinsToRead, uint8_t *ReadValue);
	void WritePin(arduinoPinNames_E pin, PinStatus_E status);
	void createBitfield(arduinoPinNames_E pins[8], int *NumberOfPinsToPack, uint8_t *Bitfield);
	
};


#endif /* SKETCH_H_ */