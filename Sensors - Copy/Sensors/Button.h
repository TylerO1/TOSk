/*
 * Button.h
 *
 * Created: 1/5/2014 3:43:24 PM
 *  Author: Tyler
 */ 

#include "ArduinoInterface.h"

enum ButtonFailureReasons{
	NO_FAILURE,
	INITIALIZED_INCORRECTLY,
	PIN_ALREADY_CLAIMED
};

enum ButtonStates{
	ERROR,
	PRESSED,
	RELEASED
	};


class CButton : private CArduinoInterface
{
	public:
	ButtonFailureReasons ButtonFailureState;

	CButton();
	CButton(arduinoPinNames_E A);
	void ReadButton(void);
	ButtonStates GetButtonState(void);
	
	protected:
	volatile ButtonStates ButtonStatus;
	ButtonFailureReasons ButtonFailureStatus;
	
	private:
	arduinoPinNames_E ButtonPin;
	volatile bool ButtonPressedWaitingforCall;
	
	};