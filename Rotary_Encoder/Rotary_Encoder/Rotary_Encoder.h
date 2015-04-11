/*
 * Rotary_Encoder.h
 *
 * Created: 9/22/2013 11:26:42 AM
 *  Author: Tyler
 */ 

#include <avr/io.h>

enum SupportedBoards_E
{
	arduinoUNO
};

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
	Pc0,
	Pc1,
	Pc2,
	Pc3,
	Pc4,
	Pc5
};

char AVRlibPinWords_UNO[18] =
{
	PORTD0,
	PORTD1,
	PORTD2,
	PORTD3,
	PORTD4,
	PORTD5,
	PORTD6,
	PORTD7,
	PORTB1,
	PORTB2,
	PORTB3,
	PORTC0,
	PORTC1,
	PORTC2,
	PORTC3,
	PORTC4,
	PORTC5
};


struct encoderPin_T
{
	arduinoPinNames_E pinA;
	arduinoPinNames_E pinB;
};


class Encoder{
	//variables
	encoderPin_T encoderPin;
	arduinoPinNames_E pinsToRead[2];
	SupportedBoards_E targetBoard;

	//function prototypes
	Encoder(encoderPin_T, SupportedBoards_E);
	void readPins(void);
	int getEnocderState(void);
}