/*
 * Button.h
 *
 * Created: 1/5/2014 3:43:24 PM
 *  Author: Tyler
 *
 * Notes: Class assumes the button is wired with the common
 *        port wired to ground.
 *        Class implements a pull up resistor on the Arduino board.
 */ 

class CArduinoInterface;

enum ButtonFailureReasons{
	BUTTON_NO_FAILURE,
	BUTTON_INITIALIZED_INCORRECTLY,
	BUTTON_PIN_ALREADY_CLAIMED
};

enum ButtonStates{
	BUTTON_ERROR,
	BUTTON_PRESSED,
	BUTTON_RELEASED
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