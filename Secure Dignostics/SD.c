/*
 * SD.C
 *
 *  Created on: 21 Dec 2023
 *      Author: Ola Mohamed
 */


#include"SD.h"

/********************************************Global Variable******************************/
char Recive_service[SIZE_ARRAY];              // Array to receive service data
char Routine[SIZE_ARRAY];                     // Array to store routine data
char Saved_Routine[SIZE_ARRAY] = {'A','A','0','0'};  // Array storing default routine
char Random_array[SIZE_ARRAY];                // Array to hold randomly generated data
char Encrypted_Random[SIZE_ARRAY];            // Array to hold encrypted random data (ECU)
char Verification_Random[SIZE_ARRAY];         // Array to hold user-entered verification data

char Routine_state;                           // Flag to indicate routine state
volatile char security_access = 0;            // Volatile variable indicating security access status

S_Dio LED_Routine ={PORTA_ID ,PIN0_ID,OUTPUT}; // Structure for LED Routine configuration

/*******************************************************************************************/
State_Type Initilazition(){

    State_Type Init_State = E_Not_ok; // Initialization state variable

    // Initialize various hardware components and peripherals
    // MCAL_Dio_Init();
    MCAL_Dio_SetPinDirection(&LED_Routine);
    MCAL_Timer0_OVF_Init(Prescaler_1024);
    MCAL_UART_init(9600);
    HAL_LCD_init();

    Init_State = E_ok; // Set initialization state as OK

    return Init_State; // Return the initialization state
}
/*******************************************************************************************/
State_Type Main_task(){

    State_Type Process_State = E_Not_ok; // Main task process state variable

    while(1){

        for(int i = Initail_i; i < SIZE_ARRAY ;i++){

            Recive_service[i] = MCAL_UART_receive_sysch(); // Receive service data
        }

        if(Recive_service[0]=='3' && Recive_service[1]=='1' && Recive_service[2]=='0' && Recive_service[3]=='1'){

            for (int i= Initail_i; i< SIZE_ARRAY; i++){
                Routine[i] = MCAL_UART_receive_sysch(); // Receive routine data
            }

            for (int i= Initail_i; i < SIZE_ARRAY; i++){
                if(Routine[i] != Saved_Routine[i]){ // Check if routine matches saved routine

                    HAL_LCD_clearScreen();
                    HAL_LCD_displaystringRowColumn("7F 31 33" , 0 , 3); // Display error message
                }

                if(security_access == 0){ // If security access is not granted

                    HAL_LCD_clearScreen();
                    HAL_LCD_displaystringRowColumn("7F 31 33" , 0 , 3); // Display error message
                }

                else{ // If security access is granted

                    HAL_LCD_clearScreen();
                    HAL_LCD_displaystringRowColumn("71 01 AA 00" , 0 , 2); // Display success message
                    MCAL_Dio_WriteSinglePin(&LED_Routine,PIN0_ID,1); // Turn on LED
                }
            }
        }
        else if (Recive_service[0] =='2' && Recive_service[1] =='7' && Recive_service[2] =='0' && Recive_service[3] =='1'){

            HAL_LCD_clearScreen();
            HAL_LCD_displaystringRowColumn("67 01" , 0 , 2); // Display message

            _delay_ms(1000);
            HAL_LCD_goToRowColumn(1,2);
            for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

                Random_array[i] = '0'+i ; // Generate a random array

                Encrypted_Random[i] = Random_array[i] + 2;   // Encrypt the random array
                HAL_LCD_sendCharacter(Random_array[i]);
                HAL_LCD_sendCharacter(' ');
            }
            security_access = 1; // Set security access flag
        }

        else if(Recive_service[0] =='2' && Recive_service[1] =='7' && Recive_service[2] =='0' && Recive_service[3] =='2' && security_access == 1){

            for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

                Verification_Random[i] = MCAL_UART_receive_sysch(); // Receive verification data from user
            }

            for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

                if(Verification_Random[i] == Encrypted_Random[i]){ // Check if verification matches encrypted random data

                    security_access = 2; // Set security access to level 2
                    HAL_LCD_clearScreen();
                    HAL_LCD_displaystringRowColumn("67 02" , 0 , 2); // Display success message
                }

                else{ // If verification fails

                    HAL_LCD_clearScreen();
                    HAL_LCD_displaystringRowColumn("7F 27 35" , 0 , 2); // Display error message
                }
            }
        }

        else{
            // Do nothing
        }
    }

    return Process_State; // Return the process state
}
