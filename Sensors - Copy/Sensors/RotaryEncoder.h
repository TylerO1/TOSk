/*
 * RotaryEncoder.h
 *
 * Created: 11/16/2013 3:27:22 PM
 *  Author: Tyler
 *
 * Much of code to process the encoder pins was inspired by Oleg in his Circuits@Home blog.
 * The specific post (modified to fit my needs) can be found here: 
 * http://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino
 * Thanks Oleg!
 */ 

#include "ArduinoInterface.h"

enum EncoderFailureReasons{
	NO_FAILURE,
	INITIALIZED_INCORRECTLY,
	PIN_ALREADY_CLAIMED,
	PINS_NOT_ON_SAME_PORT
};

class CRotaryEncoder : private CArduinoInterface
{
	
	public:	
	EncoderFailureReasons EncoderFailureState;
	
	CRotaryEncoder();
	CRotaryEncoder(arduinoPinNames_E A, arduinoPinNames_E B);
	void ReadEncoder(void);
	long long int GetEncoderLevel(void);
	
	protected:
	
	private:
	arduinoPinNames_E pinA, pinB;
	portPinUser_s Encoder_input;
	volatile long long int EncoderPosition;
	
};