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
#include "x_nucleo_nfc04a1.h"
#include "x_nucleo_nfc04a1_nfctag.h"
#include "Arduino.h"

Stream *_serial = NULL;
#if defined(ARDUINO_SAM_DUE)
TwoWire *_wire = &Wire1;
#else
TwoWire *_wire = &Wire;
#endif
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
uint8_t NFC04A1_Led[3] = {  5 , 4 , 2};

/**
 * @}
 */

/* Private function prototypes -----------------------------------------------*/

NFCTAG_StatusTypeDef ST25DV_IO_Init( void );
NFCTAG_StatusTypeDef ST25DV_IO_MemWrite( const uint8_t * const pData, const uint8_t DevAddr, const uint16_t TarAddr, const uint16_t Size );
NFCTAG_StatusTypeDef ST25DV_IO_MemRead( uint8_t * const pData, const uint8_t DevAddr, const uint16_t TarAddr, const uint16_t Size );
NFCTAG_StatusTypeDef ST25DV_IO_Read( uint8_t * const pData, const uint8_t DevAddr, const uint16_t Size );
NFCTAG_StatusTypeDef ST25DV_IO_IsDeviceReady( const uint8_t DevAddr, const uint32_t Trials);
NFCTAG_StatusTypeDef NFCTAG_ConvertStatus(uint8_t ret);

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
void NFC04A1_LED_Init( void )
{
	  for(uint16_t i = 0; i < sizeof(NFC04A1_Led); i++)
		pinMode(NFC04A1_Led[i], OUTPUT);
 }

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init. 
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
  */
void NFC04A1_LED_DeInit( NFC04A1_Led_E led )
{
}

/**
  * @brief  This function light on selected Led
  * @param  led : Led to be lit on
  * @retval None
  */
void NFC04A1_LED_ON( const NFC04A1_Led_E led )
{
  digitalWrite( NFC04A1_Led[led], HIGH );
}

/**
  * @brief  This function light off selected Led
  * @param  led : Led to be lit off
  * @retval None
  */
void NFC04A1_LED_OFF( const NFC04A1_Led_E led )
{
  digitalWrite( NFC04A1_Led[led], LOW );
}

/**
  * @brief  Toggles the selected LED
  * @param  led : Specifies the Led to be toggled
  * @retval None
  */
void NFC04A1_LED_Toggle( const NFC04A1_Led_E led )
{
  digitalWrite( NFC04A1_Led[led], !digitalRead(NFC04A1_Led[led]) );
}

/**
  * @brief  This function initialize the GPIO to manage the NFCTAG GPO pin
  * @param  None
  * @retval None
  */
void NFC04A1_GPO_Init( void )
{
	pinMode(12, INPUT);
}

/**
  * @brief  DeInit GPO.
  * @param  None.
  * @note GPO DeInit does not disable the GPIO clock nor disable the Mfx
  */
void NFC04A1_GPO_DeInit( void )
{
}

/**
  * @brief  This function get the GPIO value through GPIO
  * @param  None
  * @retval HAL GPIO pin status
  */
uint8_t NFC04A1_GPO_ReadPin( void )
{
  return digitalRead(12);
}

/**
  * @brief  This function initialize the GPIO to manage the NFCTAG LPD pin
  * @param  None
  * @retval None
  */
void NFC04A1_LPD_Init( void )
{
	pinMode(7,OUTPUT);
	digitalWrite(7,LOW);
}

/**
  * @brief  DeInit LPD.
  * @param  None.
  * @note LPD DeInit does not disable the GPIO clock nor disable the Mfx
  */
void NFC04A1_LPD_DeInit( void )
{
}

/**
  * @brief  This function get the GPIO value through GPIO
  * @param  None
  * @retval HAL GPIO pin status
  */
uint8_t NFC04A1_LPD_ReadPin( void )
{
  return digitalRead(7);
}

/**
  * @brief  This function get the GPIO value through GPIO
  * @param  None
  * @retval HAL GPIO pin status
  */
void NFC04A1_LPD_WritePin( uint8_t LpdPinState )
{
  digitalWrite( 7, LpdPinState );
}

/**
  * @brief  This function select the I2C1 speed to communicate with NFCTAG
  * @param  i2cspeedchoice Number from 0 to 5 to select i2c speed
  * @retval HAL GPIO pin status
  */
void NFC04A1_SelectI2cSpeed( uint8_t i2cspeedchoice )
{
  if(_wire == NULL)
	  return;
  
#if !defined(ARDUINO_ARCH_ARC) && !defined(ARDUINO_ARCH_ARC32)
  switch( i2cspeedchoice )
  {
    case 0:
      
      _wire->setClock(10000);
      break;
    
    case 1:
      
      _wire->setClock(100000);
      break;
    
    case 2:
      
      _wire->setClock(200000);
      break;
    
    case 3:
      
      _wire->setClock(400000);
      break;
    
    case 4:
      
      _wire->setClock(800000);
      break;
    
    case 5:
      
      _wire->setClock(1000000);
      break;
    
    default:
      
      _wire->setClock(1000000);
      break;
  }    
#endif
}

/**
 * @}
 */

/** @defgroup X_NUCLEO_NFC04A1_Private_Functions
 * @{
 */
/******************************** LINK EEPROM COMPONENT *****************************/

/**
  * @brief  Initializes peripherals used by the I2C NFCTAG driver
  * @param  None
  * @retval NFCTAG enum status
  */
NFCTAG_StatusTypeDef ST25DV_IO_Init( void )
{
  if(_wire == NULL)
	  return NFCTAG_ERROR;

  NFC04A1_GPO_Init( );
  
  NFC04A1_LPD_Init( );
  
  _wire->begin();
  NFC04A1_SelectI2cSpeed(3);

  return NFCTAG_OK;
}

/**
  * @brief  Write data, at specific address, through i2c to the ST25DV
  * @param  pData: pointer to the data to write
  * @param  DevAddr : Target device address
  * @param  TarAddr : I2C data memory address to write
  * @param  Size : Size in bytes of the value to be written
  * @retval NFCTAG enum status
  */
NFCTAG_StatusTypeDef ST25DV_IO_MemWrite( const uint8_t * const pData, const uint8_t DevAddr, const uint16_t TarAddr, const uint16_t Size )
{
  NFCTAG_StatusTypeDef pollstatus;
  byte ret;
  uint32_t tickstart;
  uint8_t Addr = DevAddr >> 1;
  char tmp[4];

  if(_wire == NULL)
	  return NFCTAG_ERROR;
  
	if(_serial != NULL) {
	//  _serial->println(SP);
	  _serial->print("  w ");
	  sprintf(tmp,"%02X",Addr);
	  _serial->print(tmp);
	  _serial->print("@");
	  sprintf(tmp,"%02X",TarAddr>>8);
	  _serial->print(tmp);
	  sprintf(tmp,"%02X",TarAddr&0xFF);
	  _serial->print(tmp);
	  _serial->print(":");
	  _serial->println(Size);
	  _serial->print("  ");
	  for(int d=0; d < Size; d++) {
		sprintf(tmp,"%02X",pData[d]);
		_serial->print(tmp);
	  }
	  _serial->println("");
	}

  _wire->beginTransmission(Addr); // transmit to device
  _wire->write(TarAddr >> 8);		// send memory address MSB
  _wire->write(TarAddr & 0xFF);	// send memory address LSB
  _wire->write(pData, Size);        // sends  bytes
  ret = _wire->endTransmission(true);    // stop transmitting
	if(_serial != NULL) {
	  _serial->print("  =");
	  _serial->println(ret);
	}

  if( ret == 0 )
  {
    /* Poll until EEPROM is available */
    tickstart = millis();
    /* Wait until ST25DV is ready or timeout occurs */
    do
    {
      pollstatus = ST25DV_IO_IsDeviceReady( DevAddr, 1);
    } while( ( (millis() - tickstart) < NFC04A1_I2C_TIMEOUT) && (pollstatus != NFCTAG_OK) );
    
    if( pollstatus != NFCTAG_OK )
    {
      return NFCTAG_TIMEOUT;
    }
  }
#if defined(ARDUINO_ARCH_ARC) || defined(ARDUINO_ARCH_ARC32)
// Arduino 101 i2c seems buggy after an address NACK: restart the i2c
  else if(ret == 2) {
	if(_serial != NULL) {
	  _serial->print("  -\n");
	}
	_wire->begin();
  }
#endif
  return NFCTAG_ConvertStatus(ret);
}

/**
  * @brief  Reads data at a specific address from the NFCTAG.
  * @param  pData: pointer to store read data
  * @param  DevAddr : Target device address
  * @param  TarAddr : I2C data memory address to read
  * @param  Size : Size in bytes of the value to be read
  * @retval NFCTAG enum status
  */
NFCTAG_StatusTypeDef ST25DV_IO_MemRead( uint8_t * const pData, const uint8_t DevAddr, const uint16_t TarAddr, const uint16_t Size )
{
	int i = 0;
	uint8_t ret = 4;
	uint8_t Addr = DevAddr >> 1;
    char tmp[4];

  if(_wire == NULL)
	  return NFCTAG_ERROR;

	if(_serial != NULL) {
	//  _serial->println(SP);
	  _serial->print("  r ");
	  sprintf(tmp,"%02X",Addr);
	  _serial->print(tmp);
	  _serial->print("@");
	  sprintf(tmp,"%02X",TarAddr>>8);
	  _serial->print(tmp);
	  sprintf(tmp,"%02X",TarAddr&0xFF);
	  _serial->print(tmp);
	  _serial->print(":");
	  _serial->println(Size);
	}
	_wire->beginTransmission(Addr);    // Get the slave's attention, tell it we're sending a command byte
	_wire->write(TarAddr >> 8);           //  The command byte, sets pointer to register with address of 0x32
	_wire->write(TarAddr & 0xFF);         //  The command byte, sets pointer to register with address of 0x32
	ret = _wire->endTransmission( true );
	// Address is not OK
	if(ret != 0)
		return NFCTAG_ConvertStatus(ret);
	
	// be carefull with the (int)Size, the size parameter us no more on 16 bits but only 15 bits (the cast is required for arduino UNO)
	_wire->requestFrom((int)Addr,(int)Size); // Tell slave we need to read 1byte from the current register

	
	while(_wire->available()) {
		pData[i++] = _wire->read();      // read that byte into 'slaveByte2' variable
	}
	if(_serial != NULL) {
	  _serial->print("  ");
	  for(int d=0; d < i; d++) {
		sprintf(tmp,"%02X",pData[d]);
		_serial->print(tmp);
	  }
	  _serial->println("");
	}
	ret = _wire->endTransmission();   
	if(_serial != NULL) {
		//	_serial->println(pData[0]);
		  _serial->print("  =");
		  _serial->println(ret);
		//  _serial->print("  ");
		//  _serial->println(pData[0]);
		//  _serial->println((uint32_t)pData);
	}
	return NFCTAG_ConvertStatus(ret);
}

NFCTAG_StatusTypeDef NFCTAG_ConvertStatus(uint8_t ret) {
	if (ret == 0) {
		return NFCTAG_OK;
	} else if ((ret == 2) || (ret == 3)) {
		return NFCTAG_NACK;
	} else {
		return NFCTAG_ERROR;
	}
}


/**
  * @brief  Reads data at current address from the NFCTAG.
  * @param  pData: pointer to store read data
  * @param  DevAddr : Target device address
  * @param  Size : Size in bytes of the value to be read
  * @retval NFCTAG enum status
  */
NFCTAG_StatusTypeDef ST25DV_IO_Read( uint8_t * const pData, const uint8_t DevAddr, const uint16_t Size )
{
	int i = 0;
	uint8_t Addr = DevAddr >> 1;
	char tmp[4];
	
  if(_wire == NULL)
	  return NFCTAG_ERROR;
	if(_serial != NULL) {
	  _serial->print("  r");
	  _serial->print(":");
	  _serial->println(Size);
	}
	// be carefull with the (int)Size, the size parameter us no more on 16 bits but only 15 bits (the cast is required for arduino UNO)
	byte ret = _wire->requestFrom((int)Addr,(int)Size); // Tell slave we need to read 1byte from the current register
	while(_wire->available()) {
		pData[i++] = _wire->read();      // read that byte into 'slaveByte2' variable
	}
	
	if(_serial != NULL) {
	  _serial->print("  ");
	  for(int d=0; d < i; d++) {
		sprintf(tmp,"%02X",pData[d]);
		_serial->print(tmp);
	  }
	  _serial->println("");
	}
  ret = _wire->endTransmission();   

	if(_serial != NULL) {
		//	_serial->println(pData[0]);
	  _serial->print("  =");
	  _serial->println(ret);
	}
  return NFCTAG_ConvertStatus( ret);
}


/**
* @brief  Checks if target device is ready for communication
* @note   This function is used with Memory devices
* @param  DevAddr : Target device address
* @retval NFCTAG enum status
*/
NFCTAG_StatusTypeDef ST25DV_IO_IsDeviceReady( const uint8_t DevAddr, const uint32_t Trials)
{ 
  int ret = 4;
  uint32_t count = 0;
  if (_wire == NULL) {
	  return NFCTAG_ERROR;
  }
  if (_serial != NULL) {
	  _serial->println("  ?");
  }

  while ((count++ < Trials) && ret) {
	_wire->beginTransmission(DevAddr>>1);
	ret = _wire->endTransmission();
	  if (_serial != NULL) {
		  _serial->print("  =");
		  _serial->println(ret);
	  }
  }
  return NFCTAG_ConvertStatus(ret);
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
