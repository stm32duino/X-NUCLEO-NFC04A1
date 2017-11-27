#ifndef _X_NUCLEO_NFC04_H_
#define _X_NUCLEO_NFC04_H_
#include "BSP/x_nucleo_nfc04a1_nfctag.h"
#include "libNDEF/NDEFcommon.h"
#include "libNDEF/tagtype5_wrapper.h"
#include "libNDEF/lib_NDEF_URI.h"
#include "libNDEF/lib_NDEF_AAR.h"
#include "libNDEF/lib_NDEF_Bluetooth.h"
#include "libNDEF/lib_NDEF_Email.h"
#include "libNDEF/lib_NDEF_Handover.h"
#include "libNDEF/lib_NDEF_Geo.h"
#include "libNDEF/lib_NDEF_MyApp.h"
#include "libNDEF/lib_NDEF_SMS.h"
#include "libNDEF/lib_NDEF_Text.h"
#include "libNDEF/lib_NDEF_Vcard.h"
#include "libNDEF/lib_NDEF_Wifi.h"

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