/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#define F_CPU 16000000UL    //F_CPU tells the compiler that our crystal is an 16Mhz one so it can generate an accurate delay, must be declared above delay so delay knows what is the value of F_CPU


#include "Encoder.h"

int main (void)
{
	board_init();
	AVRlibPinWords[4];

	// Insert application code here, after the board has been initialized.
}
