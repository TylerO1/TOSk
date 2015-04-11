/*
 * TylerSerialIO.cpp
 *
 * Created: 4/27/2014 11:11:28 AM
 *  Author: Tyler
 */ 

#include "TylerSerialIO.h"


 CSerialIO::CSerialIO()
{
	UBRR0H = (uint8_t)(BAUDPRESCALER>>8);
	UBRR0L = (uint8_t)(BAUDPRESCALER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}

unsigned char CSerialIO::USART_receive( void )
{
	 while(!(UCSR0A & (1<<RXC0)));
	 return UDR0;
}

void CSerialIO::USART_putstring( char* StringPtr )
{
	while(*StringPtr != 0x00)
	{    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
		this->USART_send(*StringPtr);    //Using the simple send function we send one char at a time
		StringPtr++;        //We increment the pointer so we can read the next char
	}
}

void CSerialIO::USART_send( unsigned char data )
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}