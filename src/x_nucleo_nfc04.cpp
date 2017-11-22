#include "x_nucleo_nfc04.h"
#include "Arduino.h"

extern sCCFileInfo CCFileStruct;

// make this instance available in teh sketch
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
	
	ret = BSP_NFCTAG_Init( );
	if(ret != NDEF_OK)
		return ret;
	
	BSP_NFCTAG_GetExtended_Drv()->ResetMBEN_Dyn( );
	if( NfcType5_NDEFDetection() != NDEF_OK )
	{
		CCFileStruct.MagicNumber = NFCT5_MAGICNUMBER_E1_CCFILE;
		CCFileStruct.Version = NFCT5_VERSION_V1_0;
		CCFileStruct.MemorySize = ( ST25DV_MAX_SIZE / 8 ) & 0xFF;
		CCFileStruct.TT5Tag = 0x05;
		/* Init of the Type Tag 5 component (M24LR) */
		ret = NfcType5_TT5Init( );
		if (ret != NDEF_OK)
			return ret;
	}
	
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

int X_Nucleo_NFC04::writeURI(String protocol, String uri, String info) {
	sURI_Info _URI;
    strcpy( _URI.protocol,protocol.c_str() );
    strcpy( _URI.URI_Message,uri.c_str() );
    strcpy( _URI.Information,info.c_str() );

	return NDEF_WriteURI( &_URI );
}



String X_Nucleo_NFC04::readURI() {
    sURI_Info uri = {"","",""};
    sRecordInfo_t recordInfo;
    // increase buffer size for bigger messages
    if(NDEF_ReadNDEF(NDEF_Buffer))
        return (String)NULL;
    
    if(NDEF_IdentifyBuffer(&recordInfo, NDEF_Buffer))
        return (String)NULL;
    if(NDEF_ReadURI(&recordInfo,&uri))
        return (String)NULL;
    return String(uri.protocol) + String(uri.URI_Message);
}

