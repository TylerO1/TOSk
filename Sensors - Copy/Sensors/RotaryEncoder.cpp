/*
 * RotaryEncoder.cpp
 *
 * Created: 11/16/2013 3:27:47 PM
 *  Author: Tyler
 */ 

#include "RotaryEncoder.h"

CRotaryEncoder::CRotaryEncoder()
{
	EncoderFailureState =INITIALIZED_INCORRECTLY;
}

CRotaryEncoder::CRotaryEncoder(arduinoPinNames_E A, arduinoPinNames_E B)
{
	arduinoPinNames_E CreateBitfield[8];
	
	pinA = A;
	pinB = B;
	
	// Check for errors, if none then assign the pins to Encoder_input
	if (this->SetReadStatus(pinA) == false)
	{
		EncoderFailureState = PIN_ALREADY_CLAIMED;
	}
	else if (this->SetReadStatus(pinB) == false)
	{
		EncoderFailureState = PIN_ALREADY_CLAIMED;
	}
	else if (this->FindPort(pinA) != this->FindPort(pinB))
	{
		EncoderFailureState = PINS_NOT_ON_SAME_PORT;
	}
	else
	{
		EncoderFailureState = NO_FAILURE;
		Encoder_input.port = this->FindPort(pinA);
		CreateBitfield[0] = pinA;
		CreateBitfield[1] = pinB;
		Encoder_input.pins = this->PackPinsToBitfield(CreateBitfield, 2);
		
		EncoderPosition = 0;
		
	}
	
}

void CRotaryEncoder::ReadEncoder( void )
{
	// Much of this code was inspired by Oleg in his Circuits@Home blog. The specific post (modified to fit my needs)
	// can be found here: http://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino
	// Thanks Oleg!
	
	static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
	static uint8_t OldReading = 0;
	static uint8_t CurrentReading = 0;
	static uint8_t Pin1State = 0;
	static uint8_t Pin2State = 0;
	
	if (EncoderFailureState == NO_FAILURE)
	{
		CurrentReading = this->ReadMultipleDigitalPins(Encoder_input);
		Pin1State = ( ( CurrentReading & AVRlibPinWords[pinA] ) >> AVRlibPinWords[pinA] );
		Pin2State = ( ( CurrentReading & AVRlibPinWords[pinB] ) >> AVRlibPinWords[pinB] );
		
		OldReading <<= 2;
		OldReading |= (Pin1State | Pin2State);
		
		EncoderPosition += enc_states[OldReading & 0x0f];
	}
}

long long int CRotaryEncoder::GetEncoderLevel()
{
	return EncoderPosition;
}
