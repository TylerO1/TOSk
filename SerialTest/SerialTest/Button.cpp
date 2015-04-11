/*
 * Button.c
 *
 * Created: 1/5/2014 3:43:08 PM
 *  Author: Tyler
 */ 

#include "ArduinoInterface.h"
#include "Button.h"


 CButton::CButton()
{
	ButtonFailureStatus = BUTTON_INITIALIZED_INCORRECTLY;
	ButtonStatus = BUTTON_ERROR;
}

 CButton::CButton( arduinoPinNames_E A )
{
	ButtonPin = A;
	
	if (this->SetReadStatus(ButtonPin) == false)
	{
		ButtonFailureState = BUTTON_PIN_ALREADY_CLAIMED;
		ButtonStatus = BUTTON_ERROR;
	}
	else if(this->SetPullUpStatus(ButtonPin) == false)
	{
		ButtonFailureState = BUTTON_PIN_ALREADY_CLAIMED;
		ButtonStatus = BUTTON_ERROR;
	}
	else
	{
		ButtonFailureState = BUTTON_NO_FAILURE;
	}
}

void CButton::ReadButton( void )
{
	if (ButtonFailureState == BUTTON_NO_FAILURE)
	{
		if (this->ReadDigitalPin(&ButtonPin) == 0)
		{
			ButtonStatus = BUTTON_PRESSED;
		} 
		else
		{
			ButtonStatus = BUTTON_RELEASED;
		}
		
	}
}

ButtonStates CButton::GetButtonState( void )
{
	static ButtonStates Output;
	
	if (ButtonFailureStatus != BUTTON_NO_FAILURE)
	{
		Output = BUTTON_ERROR;
	} 
	else
	{
		Output = ButtonStatus;
	}
	
	return Output;
	
}