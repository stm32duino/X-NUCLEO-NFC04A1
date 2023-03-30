#ifndef _X_NUCLEO_NFC04_H_
#define _X_NUCLEO_NFC04_H_
#include "ST25DVSensor.h"

/**
 * @brief  NFC04A1 Led enumerator definition
 */
typedef enum {
  GREEN_LED = 0,
  BLUE_LED,
  YELLOW_LED
} NFC04A1_Led_E;

/**
 * @brief  NFC04A1 Led structure definition
 */

typedef struct {
  uint16_t          NFC04A1_LED_PIN;
} NFC04A1_Led_TypeDef;

class X_Nucleo_NFC04 : public ST25DV {
  public:
    X_Nucleo_NFC04(int32_t gpo, int32_t lpd, TwoWire *i2c, Stream *serial = NULL) : ST25DV(gpo, lpd, i2c, serial) {}
    int begin();
    void ledOn(int led);
    void ledOff(int led);
    void NFC04A1_LED_Init(void);
    void NFC04A1_LED_DeInit(NFC04A1_Led_E led);
    void NFC04A1_LED_ON(const NFC04A1_Led_E led);
    void NFC04A1_LED_OFF(const NFC04A1_Led_E led);
    void NFC04A1_LED_Toggle(const NFC04A1_Led_E led);
  private:
    sCCFileInfo CCFileStruct;
    uint8_t NFC04A1_Led[3] = {  5, 4, 2};
};

#endif
