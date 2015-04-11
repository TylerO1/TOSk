/*
 * Button.c
 *
 * Created: 1/5/2014 3:43:08 PM
 *  Author: Tyler
 */ 

#include "Button.h"


 CButton::CButton()
{
	ButtonFailureStatus = INITIALIZED_INCORRECTLY;
	ButtonStatus = ERROR;
}

 CButton::CButton( arduinoPinNames_E A )
{
	ButtonPin = A;
	
	if (this->SetReadStatus(ButtonPin) == false)
	{
		ButtonFailureState = PIN_ALREADY_CLAIMED;
		ButtonStatus = ERROR;
	}
	else
	{
		ButtonFailureState = NO_FAILURE;
	}
}

void CButton::ReadButton( void )
{
	if (ButtonFailureState == NO_FAILURE)
	{
		if (this->ReadDigitalPin(ButtonPin) == 1)
		{
			ButtonStatus = PRESSED;
		} 
		else
		{
			ButtonStatus = RELEASED;
		}
		
	}
}

ButtonStates CButton::GetButtonState( void )
{
	static ButtonStates Output;
	
	if (ButtonFailureStatus != NO_FAILURE)
	{
		Output = ERROR;
	} 
	else
	{
		Output = ButtonStatus;
	}
	
	return Output;
	
}