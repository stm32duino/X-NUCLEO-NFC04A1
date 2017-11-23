#ifndef _X_NUCLEO_NFC04_H_
#define _X_NUCLEO_NFC04_H_
#include "BSP/x_nucleo_nfc04a1_nfctag.h"
#include "LibNDEF/NDEFcommon.h"
#include "LibNDEF/tagtype5_wrapper.h"
#include "LibNDEF/lib_NDEF_URI.h"
#include "LibNDEF/lib_NDEF_AAR.h"
#include "LibNDEF/lib_NDEF_Bluetooth.h"
#include "LibNDEF/lib_NDEF_Email.h"
#include "LibNDEF/lib_NDEF_Handover.h"
#include "LibNDEF/lib_NDEF_Geo.h"
#include "LibNDEF/lib_NDEF_MyApp.h"
#include "LibNDEF/lib_NDEF_SMS.h"
#include "LibNDEF/lib_NDEF_Text.h"
#include "LibNDEF/lib_NDEF_Vcard.h"
#include "LibNDEF/lib_NDEF_Wifi.h"

class X_Nucleo_NFC04 {
    public:
    X_Nucleo_NFC04(void);
    int begin();
    void ledOn(int led);
    void ledOff(int led);
    int writeURI(String protocol, String uri, String info);
    String readURI();

};

extern X_Nucleo_NFC04 X_Nucleo_Nfc04;

#endif