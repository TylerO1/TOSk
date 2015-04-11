/*
 * CPPFile1.cpp
 *
 * Created: 9/23/2013 6:09:56 AM
 *  Author: Tyler
 */ 


#include "ATmega328P.h"
#include <stdio.h>

//Local function prototypes

//Local functions

// External variables

volatile pinData_S Registers[NUMBER_OF_PINS_ON_BOARD];
bool RegistersAlreadySet = false;

//External functions

 CArduinoProcessor::CArduinoProcessor( void )
 {
	// Set up the Pin Register Map
	createMap();
	return;
	 
 }

bool CArduinoProcessor::SetReadStatus(arduinoPinNames_E PinToBeRead)
{
	// Check to see if this pin has already been set
	if (Registers[PinToBeRead].pinIsClaimed == Unclaimed)
	{
		// The DDR* port is set to "0" for the particular pin to be set to read
		*(Registers[PinToBeRead].DDR) &= ~( 1 << Registers[PinToBeRead].AVRlibPinWord );
		
		Registers[PinToBeRead].pinIsClaimed = SetToRead;
		return true;
	}
	else
	{
		return false;
	}
}



bool CArduinoProcessor::SetPullUpStatus( arduinoPinNames_E PinToPullUp )
{
	// Pin must be set to Read first
	if(Registers[PinToPullUp].pinIsClaimed == SetToRead)
	{
		*(Registers[PinToPullUp].port) |= (1 << Registers[PinToPullUp].AVRlibPinWord );
		
		Registers[PinToPullUp].pinIsClaimed = SetToPullUp;
		return true;
	}
	else
	{
		return false;
	}
}


bool CArduinoProcessor::SetWriteStatus(arduinoPinNames_E PinToBeWritten)
{
	// Check to see if this pin has already been set
	if (Registers[PinToBeWritten].pinIsClaimed == Unclaimed)
	{
		*(Registers[PinToBeWritten].DDR) |= (1 << Registers[PinToBeWritten].AVRlibPinWord);
		
		Registers[PinToBeWritten].pinIsClaimed = SetToWrite;
		return true;
	}
	else
	{
		return false;
	}
}

bool CArduinoProcessor::SetPinToUnclaimed( arduinoPinNames_E PinToBeUnclaimed )
{
	Registers[PinToBeUnclaimed].pinIsClaimed = Unclaimed;
	
	return true;
}


int CArduinoProcessor::ReadDigitalPin(arduinoPinNames_E *PinToRead)
{
	return ( ( *(Registers[*PinToRead].pin) & (1 << Registers[*PinToRead].AVRlibPinWord) ) >> Registers[*PinToRead].AVRlibPinWord );
}

void CArduinoProcessor::ReadMultipleDigitalPins(portPinUser_s *PinsToRead, uint8_t *ReadValue)
{
	switch (PinsToRead->port)
	{
		case e_PORTB:
		*ReadValue = (PINB & PinsToRead->pins);
		break;
		
		case e_PORTC:
		*ReadValue = (PINC & PinsToRead->pins);
		break;
		
		case e_PORTD:
		*ReadValue = (PIND & PinsToRead->pins);
		break;
		
		case e_PORTA:
		// DO NOT USE PORT A!!
		default:
		break;
	}
		
	return;	
}

void CArduinoProcessor::WriteDigitalPin(arduinoPinNames_E *PinToWriteTo, PinStatus_E *ValueToWrite)
{
	if ((*ValueToWrite == OFF) || (*ValueToWrite == ON))
	{
		if(*ValueToWrite == ON)
		{
			*(Registers[*PinToWriteTo].port) |= (1 << Registers[*PinToWriteTo].AVRlibPinWord);
		}
		else if(*ValueToWrite == OFF)
		{
			*(Registers[*PinToWriteTo].port) &= ~(1 << Registers[*PinToWriteTo].AVRlibPinWord);
		}
	}
	else
	{
		//Bad data passed in, do nothing.
		//TODO: consider error handling
	}
	
	return;
}

void CArduinoProcessor::WriteMultipleDigitalPins(portPinUser_s *PinsToWrite, uint8_t *ValueToWrite)
{
	
	/*
	This is a little tricky, so here's an example of my math:
	
	PinsToWrite.Pins    = 0101010 (I know its 7 bits, just roll with it...)
	ValueToWrite        = 0100010
	PINB (AKA PinValue) = 1011111
	
	(So the desired state is 1110111)
	
	PinValue & (~PinsToWrite.Pins) =
		1011111 &
		1010101
	   ---------
	    1010101 (aka everything that isn't in PinsToWrite.Pins is intact)
		
		PinValue & (~PinsToWrite.Pins) | ValueToWrite =
		1010101 |
		0100010
	   ---------
	    1110111 <--- the same as our desired state
	*/
	static int PinValue = 0;
	
	switch (PinsToWrite->port)
	{
		case e_PORTB:
		PinValue = PINB;
		PINB = (( PinValue & ( ~ PinsToWrite->pins )) | *ValueToWrite );
		break;
		
		case e_PORTC:
		PinValue = PINC;
		PINC = (( PinValue & ( ~ PinsToWrite->pins )) | *ValueToWrite );
		break;
		
		case e_PORTD:
		PinValue = PIND;
		PIND = (( PinValue & ( ~ PinsToWrite->pins )) | *ValueToWrite );
		break;
		
		case e_PORTA:
		// DO NOT USE PORT A!!
		default:
		break;
	}
	
	return;
}

PinClaimedStatus_E CArduinoProcessor::StatusOfBoardsPin(arduinoPinNames_E *pinInQuestion)
{
	return Registers[*pinInQuestion].pinIsClaimed;
}

arduinoPortNames_E CArduinoProcessor::FindPort( arduinoPinNames_E Pin )
{
	arduinoPortNames_E Port;
	
	switch (Pin)
	{
		case Pd0:
		case Pd1:
		case Pd2:
		case Pd3:
		case Pd4:
		case Pd5:
		case Pd6:
		case Pd7:
		Port = e_PORTD;
		break;
		case Pb0:
		case Pb1:
		case Pb2:
		case Pb3:
		case Pb4:
		case Pb5:
		Port = e_PORTB;
		break;
		//Write in the "analog" pins, if used
		case Pc0:
		case Pc1:
		case Pc2:
		case Pc3:
		case Pc4:
		case Pc5:
		Port = e_PORTC;
		break;
		default:
		Port = e_INVALIDPORTASSIGNMMENT;
		break;
	}
	
	return Port;
}

void CArduinoProcessor::PackPinsToBitfield(arduinoPinNames_E pins[8], int *NumberOfPinsToPack, uint8_t *Bitfield)
{
	arduinoPortNames_E PortUsed = e_INVALIDPORTASSIGNMMENT;
	
	for (int i = 0; i < *NumberOfPinsToPack; i++)
	{
		switch (pins[i])
		{
			case Pd0:
			case Pd1:
			case Pd2:
			case Pd3:
			case Pd4:
			case Pd5:
			case Pd6:
			case Pd7:
			// If this isn't the first pass
			if ( i != 0 )
			{
				// If the last port used is the same as this one's keep on working, otherwise exit
				if (PortUsed == e_PORTD) 
				{
					*Bitfield += ( 1 << Registers[pins[i]].AVRlibPinWord);
					PortUsed = e_PORTD;
				}
				else
				{
					*Bitfield = 0;
					PortUsed = e_INVALIDPORTASSIGNMMENT;
				}
			}
			else
			{
				*Bitfield = ( 1 << Registers[pins[i]].AVRlibPinWord );
				PortUsed = e_PORTD;
			}
			break;
			case Pb0:
			case Pb1:
			case Pb2:
			case Pb3:
			case Pb4:
			case Pb5:
			// If this isn't the first pass
			if ( i != 0 )
			{
				// If the last port used is the same as this one's keep on working, otherwise exit
				if (PortUsed == e_PORTB)
				{
					*Bitfield += ( 1 << Registers[pins[i]].AVRlibPinWord );
					PortUsed = e_PORTB;
				}
				else
				{
					*Bitfield = 0;
					PortUsed = e_INVALIDPORTASSIGNMMENT;
				}
			}
			else
			{
				*Bitfield = ( 1 << Registers[pins[i]].AVRlibPinWord );
				PortUsed = e_PORTB;
			}
			break;
			//Write in the "analog" pins, if used
			case Pc0:
			case Pc1:
			case Pc2:
			case Pc3:
			case Pc4:
			case Pc5:
			// If this isn't the first pass
			if ( i != 0 )
			{
				// If the last port used is the same as this one's keep on working, otherwise exit
				if (PortUsed == e_PORTC)
				{
					*Bitfield += ( 1 << Registers[pins[i]].AVRlibPinWord );
					PortUsed = e_PORTC;
				}
				else
				{
					*Bitfield = 0;
					PortUsed = e_INVALIDPORTASSIGNMMENT;
				}
			}
			else
			{
				*Bitfield = ( 1 << Registers[pins[i]].AVRlibPinWord );
				PortUsed = e_PORTC;
			}
			break;
			default:
			break;
		}
	}
	
	return;
}

void CArduinoProcessor::createMap()
{
	if(RegistersAlreadySet== false)
	{
		Registers[Pd0].port = &PORTD;
		Registers[Pd0].pin = &PIND;
		Registers[Pd0].DDR = &DDRD;
		Registers[Pd0].AVRlibPinWord = PORTD0;
		Registers[Pd0].pinIsClaimed = Unclaimed;

		Registers[Pd1].port = &PORTD;
		Registers[Pd1].pin = &PIND;
		Registers[Pd1].DDR = &DDRD;
		Registers[Pd1].AVRlibPinWord = PORTD1;
		Registers[Pd1].pinIsClaimed = Unclaimed;

		Registers[Pd2].port = &PORTD;
		Registers[Pd2].pin = &PIND;
		Registers[Pd2].DDR = &DDRD;
		Registers[Pd2].AVRlibPinWord = PORTD2;
		Registers[Pd2].pinIsClaimed = Unclaimed;

		Registers[Pd3].port = &PORTD;
		Registers[Pd3].pin = &PIND;
		Registers[Pd3].DDR = &DDRD;
		Registers[Pd3].AVRlibPinWord = PORTD3;
		Registers[Pd3].pinIsClaimed = Unclaimed;

		Registers[Pd4].port = &PORTD;
		Registers[Pd4].pin = &PIND;
		Registers[Pd4].DDR = &DDRD;
		Registers[Pd4].AVRlibPinWord = PORTD4;
		Registers[Pd4].pinIsClaimed = Unclaimed;

		Registers[Pd5].port = &PORTD;
		Registers[Pd5].pin = &PIND;
		Registers[Pd5].DDR = &DDRD;
		Registers[Pd5].AVRlibPinWord = PORTD5;
		Registers[Pd5].pinIsClaimed = Unclaimed;

		Registers[Pd6].port = &PORTD;
		Registers[Pd6].pin = &PIND;
		Registers[Pd6].DDR = &DDRD;
		Registers[Pd6].AVRlibPinWord = PORTD6;
		Registers[Pd6].pinIsClaimed = Unclaimed;

		Registers[Pd7].port = &PORTD;
		Registers[Pd7].pin = &PIND;
		Registers[Pd7].DDR = &DDRD;
		Registers[Pd7].AVRlibPinWord = PORTD7;
		Registers[Pd7].pinIsClaimed = Unclaimed;



		Registers[Pb0].port = &PORTB;
		Registers[Pb0].pin = &PINB;
		Registers[Pb0].DDR = &DDRB;
		Registers[Pb0].AVRlibPinWord = PORTB0;
		Registers[Pb0].pinIsClaimed = Unclaimed;

		Registers[Pb1].port = &PORTB;
		Registers[Pb1].pin = &PINB;
		Registers[Pb1].DDR = &DDRB;
		Registers[Pb1].AVRlibPinWord = PORTB1;
		Registers[Pb1].pinIsClaimed = Unclaimed;

		Registers[Pb2].port = &PORTB;
		Registers[Pb2].pin = &PINB;
		Registers[Pb2].DDR = &DDRB;
		Registers[Pb2].AVRlibPinWord = PORTB2;
		Registers[Pb2].pinIsClaimed = Unclaimed;

		Registers[Pb3].port = &PORTB;
		Registers[Pb3].pin = &PINB;
		Registers[Pb3].DDR = &DDRB;
		Registers[Pb3].AVRlibPinWord = PORTB3;
		Registers[Pb3].pinIsClaimed = Unclaimed;

		Registers[Pb4].port = &PORTB;
		Registers[Pb4].pin = &PINB;
		Registers[Pb4].DDR = &DDRB;
		Registers[Pb4].AVRlibPinWord = PORTB4;
		Registers[Pb4].pinIsClaimed = Unclaimed;

		Registers[Pb5].port = &PORTB;
		Registers[Pb5].pin = &PINB;
		Registers[Pb5].DDR = &DDRB;
		Registers[Pb5].AVRlibPinWord = PORTB5;
		Registers[Pb5].pinIsClaimed = Unclaimed;



		Registers[Pc0].port = &PORTC;
		Registers[Pc0].pin = &PINC;
		Registers[Pc0].DDR = &DDRC;
		Registers[Pc0].AVRlibPinWord = PORTC0;
		Registers[Pc0].pinIsClaimed = Unclaimed;

		Registers[Pc1].port = &PORTC;
		Registers[Pc1].pin = &PINC;
		Registers[Pc1].DDR = &DDRC;
		Registers[Pc1].AVRlibPinWord = PORTC1;
		Registers[Pc1].pinIsClaimed = Unclaimed;

		Registers[Pc2].port = &PORTC;
		Registers[Pc2].pin = &PINC;
		Registers[Pc2].DDR = &DDRC;
		Registers[Pc2].AVRlibPinWord = PORTC2;
		Registers[Pc2].pinIsClaimed = Unclaimed;

		Registers[Pc3].port = &PORTC;
		Registers[Pc3].pin = &PINC;
		Registers[Pc3].DDR = &DDRC;
		Registers[Pc3].AVRlibPinWord = PORTC3;
		Registers[Pc3].pinIsClaimed = Unclaimed;

		Registers[Pc4].port = &PORTC;
		Registers[Pc4].pin = &PINC;
		Registers[Pc4].DDR = &DDRC;
		Registers[Pc4].AVRlibPinWord = PORTC4;
		Registers[Pc4].pinIsClaimed = Unclaimed;

		Registers[Pc5].port = &PORTC;
		Registers[Pc5].pin = &PINC;
		Registers[Pc5].DDR = &DDRC;
		Registers[Pc5].AVRlibPinWord = PORTC5;
		Registers[Pc5].pinIsClaimed = Unclaimed;
		
		RegistersAlreadySet = true;
	}
	
	return;
}

