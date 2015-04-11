/*
 * Main.cpp
 *
 * Created: 2/23/2014 12:27:08 PM
 *  Author: Tyler
 */

// Definitions for the Serial connection
#define BAUDRATE 76800									      //Serial Baudrate. Change this for different rates.


#ifndef SKETCH_H_
#include "Sketch.h"
#endif

#include "Button.h"
#include "RotaryEncoder.h"
//#include "TylerSerialIO.h"
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
/* Running counter */
#pragma message "Sketch Running At: " XSTR(F_CPU) " HZ"

 //Local function prototypes

//Global variables
Test Tyler;
//CSerialIO RS232;
CButton Button1(Pb2);
CRotaryEncoder Encoder1(Pb1, Pb0);
static int VolumeLevel = 32000;
int VolumeLeveltemp = 32000;

 void setup()
 {
	// button
	Tyler.SetWrite(Pb5);
	
	//Rotary Encoder
	Tyler.SetWrite(Pb4);
	Tyler.SetWrite(Pb3);
	
	// Serial
	Serial.begin(115200);
		 
#if defined(ENABLE_TEXT_MESSAGE)
	ShowBuildInfo();
#endif	

 }

 void loop()
 {
	 char string[38];
	 
	 // Button
	 Button1.ReadButton();
	 if(Button1.GetButtonState() == BUTTON_PRESSED)
	 {
		 //LED goes on
		 Tyler.WritePin(Pb5, ON);
	 }
	 else
	 {
		 //LED goes off
		 Tyler.WritePin(Pb5, OFF);
		 
	 }
	 
	 // Rotary Encoder
	 Encoder1.ReadEncoder();
	 VolumeLeveltemp = Encoder1.GetEncoderLevel();
	 
	 if (VolumeLeveltemp > VolumeLevel)
	 {
		 Tyler.WritePin(Pb4, ON);
		 sprintf(string, "Volume: %d up\n", Encoder1.GetEncoderLevel());
		Serial.write(string);
	 }
	 else if (VolumeLeveltemp < VolumeLevel)
	 {
		 Tyler.WritePin(Pb3, ON);
		 sprintf(string, "Volume: %d down\n", Encoder1.GetEncoderLevel());
		Serial.write(string);
	 }
	 else
	 {
		 Tyler.WritePin(Pb4, OFF);
		 Tyler.WritePin(Pb3, OFF);
	 }
	 
	 VolumeLevel = VolumeLeveltemp;
 }
 
 
 
 void Test::SetRead( arduinoPinNames_E pin )
 {
	 this->SetReadStatus(pin);
 }

void Test::SetPullUP( arduinoPinNames_E pin )
{
	this->SetPullUpStatus(pin);
}
 
 
  void Test::SetWrite( arduinoPinNames_E pin )
  {
	  this->SetWriteStatus(pin);
  }

int Test::ReadPin( arduinoPinNames_E pin )
{
	return this->ReadDigitalPin(&pin);
}


void Test::WritePin( arduinoPinNames_E pin , PinStatus_E status)
{
	this->WriteDigitalPin(&pin, &status);
}


void Test::ReadMultiplePins( portPinUser_s PinsToRead, uint8_t *ReadValue )
{
	this->ReadMultipleDigitalPins(&PinsToRead, ReadValue);
}


void Test::createBitfield(arduinoPinNames_E pins[8], int *NumberOfPinsToPack, uint8_t *Bitfield )
{
	this->PackPinsToBitfield(pins, NumberOfPinsToPack, Bitfield);
}