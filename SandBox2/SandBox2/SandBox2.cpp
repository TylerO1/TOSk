/*
 * SandBox2.cpp
 *
 * Created: 9/28/2014 1:39:38 PM
 *  Author: Tyler
 */ 

#define F_CPU 16000000L // Clock speed
#define BAUD 57600	  // Baud Rate
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>    // including the avr delay lib
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "RotaryEncoder.h"
#include "Button.h"

int main(void)
{
	USART_Init(MYUBRR); // Initializes the serial communication
	// Initialize room volume knobs
	CRotaryEncoder EncoderRoom1(Pb0, Pb1);
	CButton		ButtonRoom1(Pb2);

	CRotaryEncoder EncoderRoom2(Pb3, Pb4);
	CButton		ButtonRoom2(Pb5);

	CRotaryEncoder EncoderRoom3(Pb0, Pb1);
	CButton		ButtonRoom3(Pb2);

	CRotaryEncoder EncoderRoom4(Pb0, Pb1);
	CButton		ButtonRoom4(Pb2);

	static char string[64];
			
	
    while(1)
    {
		// Read Volume knob states
		EncoderRoom1.ReadEncoder();
		ButtonRoom1.ReadButton();
		
		EncoderRoom2.ReadEncoder();
		ButtonRoom2.ReadButton();
		
		EncoderRoom3.ReadEncoder();
		ButtonRoom3.ReadButton();
		
		EncoderRoom4.ReadEncoder();
		ButtonRoom4.ReadButton();
		
		
		sprintf(string, "%d %d %d %d %d %d %d %d \n", 
		EncoderRoom1.GetEncoderLevel(), ButtonRoom1.GetButtonState(), 
		EncoderRoom2.GetEncoderLevel(), ButtonRoom2.GetButtonState(),
		EncoderRoom3.GetEncoderLevel(), ButtonRoom3.GetButtonState(),
		EncoderRoom4.GetEncoderLevel(), ButtonRoom4.GetButtonState());
		USART_Send_string(string);
    }
}