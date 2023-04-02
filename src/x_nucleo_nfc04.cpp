#include "x_nucleo_nfc04.h"
#include "Arduino.h"

int X_Nucleo_NFC04::begin()
{
  int ret = 0;

  NFC04A1_LED_Init();
  ledOn(GREEN_LED);
  delay(300);
  ledOn(BLUE_LED);
  delay(300);
  ledOn(YELLOW_LED);
  delay(300);

  ret = ST25DV::begin();

  if (ret != ST25DV_OK) {
    return ret;
  }

  ledOff(GREEN_LED);
  delay(300);
  ledOff(BLUE_LED);
  delay(300);
  ledOff(YELLOW_LED);
  delay(300);
  return NDEF_OK;
}

void X_Nucleo_NFC04::ledOn(int led)
{
  NFC04A1_LED_ON((NFC04A1_Led_E)led);
}

void X_Nucleo_NFC04::ledOff(int led)
{
  NFC04A1_LED_OFF((NFC04A1_Led_E) led);
}

void X_Nucleo_NFC04::NFC04A1_LED_Init(void)
{
  for (uint16_t i = 0; i < sizeof(NFC04A1_Led); i++) {
    pinMode(NFC04A1_Led[i], OUTPUT);
  }
}

void X_Nucleo_NFC04::NFC04A1_LED_DeInit(void)
{

}

void X_Nucleo_NFC04::NFC04A1_LED_ON(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], HIGH);
}

void X_Nucleo_NFC04::NFC04A1_LED_OFF(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], LOW);
}

void X_Nucleo_NFC04::NFC04A1_LED_Toggle(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], !digitalRead(NFC04A1_Led[led]));
}
