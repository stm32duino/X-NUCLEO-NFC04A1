#include "x_nucleo_nfc04.h"
#include "Arduino.h"

extern sCCFileInfo CCFileStruct;

// make this instance available in the sketch
X_Nucleo_NFC04 X_Nucleo_Nfc04;

X_Nucleo_NFC04::X_Nucleo_NFC04(void) {
	
}
int X_Nucleo_NFC04::begin() {
	int ret = 0;
	
	NFC04A1_LED_Init( );
	ledOn( GREEN_LED );
	delay( 300 );
	ledOn( BLUE_LED );
	delay( 300 );
	ledOn( YELLOW_LED );
	delay( 300 );
	
	ret = st25dv.begin(12, 7); // gpo, lpd
	if(ret != ST25DV_OK)
		return ret;

	ledOff( GREEN_LED );
	delay( 300 );
	ledOff( BLUE_LED );
	delay( 300 );
	ledOff( YELLOW_LED );
	delay( 300 );
	return NDEF_OK;
}

void X_Nucleo_NFC04::ledOn(int led) {
	NFC04A1_LED_ON((NFC04A1_Led_E)led);
}

void X_Nucleo_NFC04::ledOff(int led) {
  NFC04A1_LED_OFF((NFC04A1_Led_E) led );
}
