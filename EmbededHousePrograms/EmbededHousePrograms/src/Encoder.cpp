#include "Encoder.h"

#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC


Encoder::Encoder(encoderPin_T inputPins)
{
	encoderPin.pinA = inputPins.pinA;
	encoderPin.pinB = inputPins.pinB;
   pinsToRead[2] = {encoderPin.pinA, encoderPin.pinB};
}

Encoder::readPins()
{
	int pinCount;
	static int enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
		static int old_AB = 0;
   
	/**/
	old_AB <<= 2;                   //remember previous state
	
	for(pinCount = 0, pinCount>2; pinCount++)
{
   //add Pin A's current state
	switch (encoderPin.pinA)
   {
   case Pd0:
   case Pd1:
   case Pd2:
   case Pd3:
   case Pd4:
   case Pd5:
   case Pd6:
   case Pd7:
      //"AND" in the value of that pin
	  old_AB |= ( PIND & (1 << AVRlibPinWords( pinsToRead( pinCount ) ) ) );
	  break;
   case Pb0:
   case Pb1:
   case Pb2:
   case Pb3:
      //"AND" in the value of that pin
      old_AB |= ( PINB & (1 << AVRlibPinWords( pinsToRead( pinCount ) ) ) );
      break;
   //Read in the "analog" pins, if used
   case Pc0:
   case Pc1:
   case Pc2:
   case Pc3:
   case Pc4:
   case Pc5:
      //"AND" in the value of that pin
      old_AB |= ( PINC & (1 << AVRlibPinWords( pinsToRead( pinCount ) ) ) );
      break;
   default:
      break;
   }
}
	
	return ( enc_states[( old_AB & 0x0f )]);

}