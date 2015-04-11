/*
 * ArduinoInterface.h
 *
 * Created: 9/22/2013 12:37:20 PM
 *  Author: Tyler
 */ 

/*
Arduino Interface:
This object is intended to be the base of all IO for any Arduino projects.
Currently a work in progress, the object should detect which board is being used and route pin numbers to the correct IO.

This is a method to avoid DigitalRead/Write to save time and use some bitwise math (particularly for bitwise operators)

How this object works:
Currently Digital pin setting, reads, and writes are implemented for the Uno board. While I had hoped that the similiar code
for all these functions could be abstracted away to a single function (and make it easier to add in new boards) it would appear
that DDRx, PINx, and PORTx cannot be passed as variables. Drat.

Board support:
It is impossible for this object to know what Arduino board is being used, but it can know what processor is being used.
It is up to the developer/object to not do something silly like overwriting the serial port. PROGRAMMER BEWARE!!

Adding new processors:
Adding new processors involves finding the pin definitions and mapping them to a struct (use the Uno as an example). For
every new processor, create a new object and wrap the "include" with that processor's #DEFINE
Known DEFINEs:

Constant				CPU				Board
__AVR_ATmega168__		ATMega 168		Decimilia and older
__AVR_ATmega328P__		ATMega 328P		Duemilanove and Uno
__AVR_ATmega1280__		ATMega 1280		Mega
__AVR_ATmega2560__		ATMega 2560		Mega 2560
__AVR_ATmega32U4__		ATMega 32U4		Leonardo
__SAM3X8E__				AT91SAM3X8E		Due

*/

#ifndef ARDUINOINTERFACE_H_
#define ARDUINOINTERFACE_H_

// Included the necessary board drivers
#ifdef __AVR_ATmega328P__ //Duemilanove and Uno
#include "ATmega328P.h"
#endif


class CArduinoInterface : public CArduinoProcessor
{
	/*
	There is nothing unique about this class, it allows for applications to use this object without caring which
	board is being used. For the sake of completeness, here is what all base processor classes have defined:
	
	
	//-------------------------------------------------
	// Board specific definitions
	
	#define NUMBER_OF_PINS_ON_BOARD   (#)     <----- Use this to define any arrays that come up
	
	enum arduinoPinNames_E
	{
		Pd0,
		(shortened pin names, such as Pd0 or Pc2, that are often used in pin descriptions. These names are what is used by
		outside function to access pins.)
	};

	char AVRlibPinWords[NUMBER_OF_PINS_ON_BOARD] =
	{
		PORTD0,
		(verbose pin names, such as PORTD0 or PORTC2 that are defined by winavr for I/O. These names are not important to the
		outside user.)
	};
	
	enum arduinoPortNames_E
	{
		PORTA,
		(names of port on the board. Used for specifying multi-pin reads/writes)

	//-------------------------------------------------
	// Universal definitions
	
	// Optional, use this to assign a generic port if needed.
	enum genericPinNames_E
	{
		pin0,
		pin1,
		pin2,
		pin3,
		pin4,
		pin5,
		pin6,
		pin7
	};

	enum PinStatus_E          <-----     (Used in Write situations)
	{
		OFF = 0,
		ON  = 1
	};

enum PinClaimedStatus_E
{
	Unclaimed,
	SetToRead,
	SetToWrite,
};

// Structure that will hold pins that use a similar port
struct portPinUser_s
{
	arduinoPortNames_E port;
	//Bit packed field of all the pins on the port (everything else must be 0)
	int pins;
};

class CArduinoProcessor{
	private:
	PinClaimedStatus_E pinIsClaimed[NUMBER_OF_PINS_ON_BOARD];
	
	protected:
	bool SetReadStatus(arduinoPinNames_E PinToBeRead);
	bool SetWriteStatus(arduinoPinNames_E PinToBeWritten);
	bool SetPinToUnclaimed(arduinoPinNames_E PinToBeUnclaimed);
	int ReadDigitalPin(arduinoPinNames_E *PinToRead);
	void ReadMultipleDigitalPins(portPinUser_s *PinsToRead, uint8_t *ReadValue);
	void WriteDigitalPin(arduinoPinNames_E *PinToWrite, PinStatus_E *ValueToWrite);
	arduinoPortNames_E FindPort(arduinoPinNames_E Pin);
	
	//Note: ValueToWrite is bit packed. Non "PinsToWrite" pins MUST be "0" in ValueToWrite
	void WriteMultipleDigitalPins(portPinUser_s *PinsToWrite, uint8_t *ValueToWrite);
	
	// Note: This function assumes pins should be on the same port and will return a "0" if pins aren't on the same port
	void PackPinsToBitfield(arduinoPinNames_E *pins[8], int *NumberOfPinsToPack, uint8_t *Bitfield);
	
	public:
	PinClaimedStatus_E * StatusOfBoardsPins(void);

};
	
	*/
	
};


#endif