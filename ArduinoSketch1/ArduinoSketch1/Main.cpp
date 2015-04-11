/*
 * Main.cpp
 *
 * Created: 9/16/2013 7:17:17 PM
 *  Author: Tyler
 */



#ifndef SKETCH_H_
#include "Sketch.h"
#endif


/* Running counter */
static unsigned long counter = 0;


//#pragma message "Sketch Running At: " XSTR(F_CPU) " HZ"

 void setup()
 {
	 /* Setup pin connected to board LED for output */
	 pinMode(LED, OUTPUT);
	 
	 /* Initialize serial interface */
	 Serial.begin(SERIAL_SPEED);
	 
	 /* Show build information via serial interface */
#if defined(ENABLE_TEXT_MESSAGE)
	ShowBuildInfo();
#endif	

 }

 void loop()
 {
	 digitalWrite(LED, HIGH);
	 delay(DELAY_LENGTH);
	 digitalWrite(LED, LOW);
	 delay(DELAY_LENGTH);
	 Serial.print(MESSAGE);
	 Serial.println( ++counter );
 }