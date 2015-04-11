#include <io.h>    //This contains definitions for all the registers locations and some other things, must always be included



enum arduinoPinNames_E
{
	Pd0,
	Pd1,
	Pd2,
	Pd3,
	Pd4,
	Pd5,
	Pd6,
	Pd7,
	Pb0,
	Pb1,
	Pb2,
	Pb3,
	Pc0,
	Pc1,
	Pc2,
	Pc3,
	Pc4,
	Pc5
};

char AVRlibPinWords[18] =
{
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	PB1,
	PB2,
	PB3,
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5
};


struct encoderPin_T
{
	arduinoPinNames_E pinA;
	arduinoPinNames_E pinB;
};


class Encoder{
	//vairables
	encoderPin_T encoderPin;
   arduinoPinNames_E pinsToRead[2];

	//function prototypes
	Encoder(encoderPin_T);
	void readPins();
	int getEnocderState();
}
