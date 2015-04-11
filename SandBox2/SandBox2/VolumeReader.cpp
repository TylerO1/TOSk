/*
 * Main.cpp
 *
 * Created: 2/2/2014 1:10:44 PM
 *  Author: Tyler
 */



#ifndef SKETCH_H_
#include "Sketch.h"
#endif

#include "ArduinoInterface.h"
#include "RotaryEncoder.h"
#include "Button.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

// Definitions for the Serial connection
#define BAUDRATE 115200									      //Serial Baudrate. Change this for different rates.


// Local function prototypes
void SensorInputInterruptsInit(void);

// Global Objects
CRotaryEncoder EncoderRoom1(Pb0, Pb1);
CButton		ButtonRoom1(Pb2);
 
CRotaryEncoder EncoderRoom2(Pb3, Pb4);
CButton		ButtonRoom2(Pb5);
 
CRotaryEncoder EncoderRoom3(Pb0, Pb1);
CButton		ButtonRoom3(Pb2);
 
CRotaryEncoder EncoderRoom4(Pb0, Pb1);
CButton		ButtonRoom4(Pb2);


#pragma message "Sketch Running At: " XSTR(F_CPU) " HZ"

 void setup()
 {
	 // Setup and start the interrupts
	 //SensorInputInterruptsInit();
	 
	 // Setup and start serial communication
	 Serial.begin(BAUDRATE);
	 
	 /* Show build information via serial interface */
#if defined(ENABLE_TEXT_MESSAGE)
	ShowBuildInfo();
#endif	

 }

 void loop()
 {
	 static char string[64];
	 static char buffer[33];
	 static char buffer2[33];
	 char Portbee;
	 EncoderRoom1.ReadEncoder();
	 ButtonRoom1.ReadButton();
	 
	 EncoderRoom2.ReadEncoder();
	 ButtonRoom2.ReadButton();
	 
	 EncoderRoom3.ReadEncoder();
	 ButtonRoom3.ReadButton();
	 
	 EncoderRoom4.ReadEncoder();
	 ButtonRoom4.ReadButton();
	 
	 sprintf(string, "%d %d %d %d %d %d %d %d\n",
	 //sprintf(string, "%d %d %d %d %d %d\n",
	 EncoderRoom1.GetEncoderLevel(), ButtonRoom1.GetButtonState(),
	 EncoderRoom2.GetEncoderLevel(), ButtonRoom2.GetButtonState(),
	 EncoderRoom3.GetEncoderLevel(), ButtonRoom3.GetButtonState(),
	 EncoderRoom4.GetEncoderLevel(), ButtonRoom4.GetButtonState() );
	 
	 //itoa (EncoderRoom1.Encoder_input.pins, buffer, 2);
	 //itoa (EncoderRoom2.Encoder_input.pins, buffer2, 2);
	 //sprintf(string, "Room1 String: %s Room2 String: %s\n", buffer, buffer2);
	 
	 Serial.write(string);
	 
	 //Portbee = PINB;
	 //if (Portbee != 0x3f)
	 //{
		 //itoa (Portbee, buffer, 2);
		 //sprintf(string, "%s\n", buffer);
		 //Serial.write(string);
	 //}
	 
 }
 
 //void SensorInputInterruptsInit(void)
 //{
	 //// Enable Interrupts on for OCR1A
	 //TIMSK1 |= (1 << OCIE1A);
	 //// Enable CTC mode based on the OCR1A time limit
	 //TCCR1B |= (1 << WGM12);
	 //// Set the time to trigger the interrupt (Once every 0.5 milliseconds)
	 //OCR1A |= 0x1F40;
	 //// Enable global interrupts
	 //sei();
 //}
 //
 //// Whenever the Sensor interrupt happens, read all encoders and buttons.
 //ISR (TIMER1_COMPA_vect)
 //{
	 //EncoderRoom1.ReadEncoder();
	 //ButtonRoom1.ReadButton();
	 //
	 //EncoderRoom2.ReadEncoder();
	 //ButtonRoom2.ReadButton();
	 //
	 //EncoderRoom3.ReadEncoder();
	 //ButtonRoom3.ReadButton();
	 //
	 //EncoderRoom4.ReadEncoder();
	 //ButtonRoom4.ReadButton();
 //}
//
 