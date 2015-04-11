/*
 * TylerSerialIO.h
 *
 * Created: 4/27/2014 11:10:19 AM
 *  Author: Tyler
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>


// Definitions for the Serial connection
#define BAUDRATE 76800									      //Serial Baudrate. Change this for different rates.
#define BAUDPRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)   // Calculates the Prescaler.

class CSerialIO{
	
	public:
	CSerialIO();
	unsigned char USART_receive( void );
	void USART_putstring(char* StringPtr);
	
	protected:
	void USART_send( unsigned char data );
	
	private:
	
	
};