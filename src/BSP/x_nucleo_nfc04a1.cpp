/**
  ******************************************************************************
  * @file    x_nucleo_nfc04a1.c
  * @author  MMY Application Team
  * @version $Revision: 3351 $
  * @date    $Date: 2017-01-25 17:28:08 +0100 (Wed, 25 Jan 2017) $
  * @brief   This file provides nfc04a1 specific functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Arduino.h"
#include "x_nucleo_nfc04a1.h"

/** @addtogroup BSP
 * @{
 */

/** @defgroup X_NUCLEO_NFC04A1
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/** @defgroup X_NUCLEO_NFC04A1_Global_Variables
 * @{
 */
uint8_t NFC04A1_Led[3] = {  5, 4, 2};

/**
 * @}
 */

/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
/** @defgroup X_NUCLEO_NFC04A1_Public_Functions
 * @{
 */

/**
  * @brief  This function initialize the GPIO to manage the Leds
  * @brief  through GPIO
  * @param  None
  * @retval None
  */
void NFC04A1_LED_Init(void)
{
  for (uint16_t i = 0; i < sizeof(NFC04A1_Led); i++) {
    pinMode(NFC04A1_Led[i], OUTPUT);
  }
}

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init.
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
  */
void NFC04A1_LED_DeInit(NFC04A1_Led_E led)
{
}

/**
  * @brief  This function light on selected Led
  * @param  led : Led to be lit on
  * @retval None
  */
void NFC04A1_LED_ON(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], HIGH);
}

/**
  * @brief  This function light off selected Led
  * @param  led : Led to be lit off
  * @retval None
  */
void NFC04A1_LED_OFF(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], LOW);
}

/**
  * @brief  Toggles the selected LED
  * @param  led : Specifies the Led to be toggled
  * @retval None
  */
void NFC04A1_LED_Toggle(const NFC04A1_Led_E led)
{
  digitalWrite(NFC04A1_Led[led], !digitalRead(NFC04A1_Led[led]));
}

/**
 * @}
 */



/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
