#ifndef _X_NUCLEO_NFC04_H_
#define _X_NUCLEO_NFC04_H_

#include "ST25DVSensor.h"
#include "BSP/x_nucleo_nfc04a1.h"

class X_Nucleo_NFC04 : public ST25DV {
  public:
    X_Nucleo_NFC04(void);
    int begin();
    void ledOn(int led);
    void ledOff(int led);
};

extern X_Nucleo_NFC04 X_Nucleo_Nfc04;

#endif