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
/* Preprocessor */
#define SIZE_ARRAY 4      /* Define the size of an array as 4 */
#define Initail_i  0      /* Define Initial value for i as 0 */

/********************************************************************************************************/
/* Enum for states */
typedef enum {
    E_ok,               /* Enum state for OK */
    E_Not_ok            /* Enum state for Not OK */
} State_Type;

/********************************************************************************************************/
/* Function Prototypes */

/* Initialization function */
State_Type Initilazition();

/* Main task function */
State_Type Main_task();

/* Convert ASCII hex to decimal */
unsigned char asciiHexToDecimal(const char *hexString);

/* Convert decimal to ASCII hex string */
void decimalToAsciiHexString(unsigned char decimalValue, char *hexString);

#endif /* SD_H_ */
