/*
 * RotaryEncoder.cpp
 *
 * Created: 11/16/2013 3:27:47 PM
 *  Author: Tyler
 */ 

#include "ArduinoInterface.h"
#include "RotaryEncoder.h"
#include <stdio.h>


CRotaryEncoder::CRotaryEncoder()
{
	EncoderFailureState =ENCODER_INITIALIZED_INCORRECTLY;
}

CRotaryEncoder::CRotaryEncoder(arduinoPinNames_E A, arduinoPinNames_E B)
{
	arduinoPinNames_E CreateBitfield[8];
	int NumberOfPinsForBitfield = 2;
	
	pinA = A;
	pinB = B;
	
	// Check for errors, if none then assign the pins to Encoder_input
	if (this->FindPort(pinA) != this->FindPort(pinB))
	{
		EncoderFailureState = ENCODER_PINS_NOT_ON_SAME_PORT;
	}
	else if (this->SetReadStatus(pinA) == false)
	{
		EncoderFailureState = ENCODER_PIN_ALREADY_CLAIMED;
	}
	else if (this->SetPullUpStatus(pinA) == false)
	{
		EncoderFailureState = ENCODER_PIN_ALREADY_CLAIMED;
	}
	else if (this->SetReadStatus(pinB) == false)
	{
		EncoderFailureState = ENCODER_PIN_ALREADY_CLAIMED;
	}
	else if (this->SetPullUpStatus(pinB) == false)
	{
		EncoderFailureState = ENCODER_PIN_ALREADY_CLAIMED;
	}
	else
	{
		EncoderFailureState = ENCODER_NO_FAILURE;
		Encoder_input.port = this->FindPort(pinA);
		CreateBitfield[0] = pinA;
		CreateBitfield[1] = pinB;
		this->PackPinsToBitfield(CreateBitfield, &NumberOfPinsForBitfield, &Encoder_input.pins);
		
		EncoderPosition = 32000;	
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
	
	if (EncoderFailureState == ENCODER_NO_FAILURE)
	{
		this->ReadMultipleDigitalPins(&Encoder_input, &CurrentReading);
		
		Pin1State = ( ( CurrentReading & ( 1 << Registers[pinA].AVRlibPinWord ) ) >> Registers[pinA].AVRlibPinWord );
		Pin2State = ( ( CurrentReading & ( 1 << Registers[pinB].AVRlibPinWord ) ) >> Registers[pinB].AVRlibPinWord );
		
		OldReading <<= 2;
		OldReading |= (Pin1State | (Pin2State << 1) );
		
		EncoderPosition += enc_states[OldReading & 0x0f];
	}
}

int CRotaryEncoder::GetEncoderLevel()
{	
	
	return EncoderPosition;
}