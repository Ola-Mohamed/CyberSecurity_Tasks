/*
 * SD.h
 *
 *  Created on: 21 Dec 2023
 *      Author: Ola Mohamed
 */

#ifndef SD_H_
#define SD_H_

#include"DIO_interface.h"
#include"lcd_interface.h"
#include"Uart_interface.h"
#include"Timer0_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
/********************************************************************************************************/
/*
char MainService  = 0x31;
#define SubService1         0x01
#define Routine             0xAA00
#define PositiveResponce    0x7101AA00
#define NegativeResponce    0x7F3135
#define SecurityAccess      0x2701
#define SecurityAccessReply 0x6701
#define EncryptionService   0x2702
#define Ok_Responce         0x6702
#define N_Ok_Responce       0x7F2735

*/
#define SIZE_ARRAY 4
#define Initail_i  0
/********************************************************************************************************/
typedef enum{

	E_ok,
	E_Not_ok

}State_Type;

/********************************************************************************************************/

State_Type Initilazition();

State_Type Main_task();

unsigned char asciiHexToDecimal(const char *hexString);

void decimalToAsciiHexString(unsigned char decimalValue, char *hexString);

#endif /* SD_H_ */
