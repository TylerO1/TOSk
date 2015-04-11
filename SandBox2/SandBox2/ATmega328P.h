/*
 * IncFile1.h
 *
 * Created: 9/23/2013 6:11:20 AM
 *  Author: Tyler
 */ 
#pragma once

#include <avr/io.h>

//-------------------------------------------------
// Board specific definitions
#ifdef __AVR_ATmega328P__ //Duemilanove and Uno

#define NUMBER_OF_PINS_ON_BOARD   20

enum arduinoPinNames_E
{
	Pd0,
	Pd1,
	Pd2,
	Pd3,
	Pd4,
	Pd5,
	Pd6,
	Pd7,
	Pb0,
	Pb1,
	Pb2,
	Pb3,
	Pb4,
	Pb5,
	Pc0,
	Pc1,
	Pc2,
	Pc3,
	Pc4,
	Pc5
};

enum arduinoPortNames_E
{
	e_PORTA, //DO NOT USE PORT A!!! this is for power/ground and other vital lines.
	e_PORTB,
	e_PORTC,
	e_PORTD,
	e_INVALIDPORTASSIGNMMENT	
};


#endif // __AVR_ATmega328P__


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

enum PinStatus_E
{
	OFF = 0,
	ON  = 1
};

enum PinClaimedStatus_E
{
	Unclaimed,
	SetToRead,
	SetToPullUp,
	SetToWrite
};
	
// Structure that will hold pins that use a similar port
struct portPinUser_s
{
	arduinoPortNames_E port;
	//Bit packed field of all the pins on the port
	uint8_t pins;
};

struct pinData_S
{
	volatile uint8_t *port;
	volatile uint8_t *pin;
	volatile uint8_t *DDR;
	char AVRlibPinWord;
	PinClaimedStatus_E pinIsClaimed;
};

extern volatile pinData_S Registers[NUMBER_OF_PINS_ON_BOARD];
extern bool RegistersAlreadySet;

class CArduinoProcessor{
	private:
	//Stores a mapping of all valid registers "Registers" variable
	void createMap();
	
	protected:
	CArduinoProcessor(void);
	// Set Read Status requires a given pin to be unassigned prior to being called
	bool SetReadStatus(arduinoPinNames_E PinToBeRead);
	
	// Set Pull Up Status requires a given pin to be set to read prior to being called
	bool SetPullUpStatus(arduinoPinNames_E PinToPullUp);
	
	// Set Write Status requires a given pin to be unassigned prior to being called
	bool SetWriteStatus(arduinoPinNames_E PinToBeWritten);
	
	// No preconditions
	bool SetPinToUnclaimed(arduinoPinNames_E PinToBeUnclaimed);
	
	int ReadDigitalPin(arduinoPinNames_E *PinToRead);
	void ReadMultipleDigitalPins(portPinUser_s *PinsToRead, uint8_t *ReadValue);
	void WriteDigitalPin(arduinoPinNames_E *PinToWrite, PinStatus_E *ValueToWrite);
	arduinoPortNames_E FindPort(arduinoPinNames_E Pin);
	
	//Note: ValueToWrite is bit packed. Non "PinsToWrite" pins MUST be "0" in ValueToWrite
	void WriteMultipleDigitalPins(portPinUser_s *PinsToWrite, uint8_t *ValueToWrite);
	
	// Note: This function assumes pins should be on the same port and will return a "0" if pins aren't on the same port
	// Used on functions that read/write to multiple pins at the same time. The "Bitfield" parameter will be passed in as "PinsToWrite" or "PinsToRead"
	void PackPinsToBitfield(arduinoPinNames_E pins[8], int *NumberOfPinsToPack, uint8_t *Bitfield);
	
	public:
	PinClaimedStatus_E StatusOfBoardsPin(arduinoPinNames_E *pinInQuestion);


};