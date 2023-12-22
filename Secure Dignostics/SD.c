/*
 * SD.C
 *
 *  Created on: 21 Dec 2023
 *      Author: Ola Mohamed
 */


#include"SD.h"

/********************************************Global Variable******************************/
char Recive_service[SIZE_ARRAY];
char Routine[SIZE_ARRAY];
char Saved_Routine[SIZE_ARRAY] = {'A','A','0','0'};
char Random_array[SIZE_ARRAY];
char Encrypted_Random[SIZE_ARRAY];     // ECU
char Verification_Random[SIZE_ARRAY];  //user


char Routine_state;   //flag
volatile char security_access = 0;


S_Dio LED_Routine ={PORTA_ID ,PIN0_ID,OUTPUT};

/*******************************************************************************************/
State_Type Initilazition(){

   State_Type Init_State = E_Not_ok;

	//MCAL_Dio_Init();
   MCAL_Dio_SetPinDirection(&LED_Routine);
    MCAL_Timer0_OVF_Init(Prescaler_1024);
	MCAL_UART_init(9600);
	HAL_LCD_init();

	Init_State = E_ok;


	return Init_State;

}
/*******************************************************************************************/
State_Type Main_task(){

	State_Type Process_State = E_Not_ok;

	while(1){

	for(int i = Initail_i; i < SIZE_ARRAY ;i++){

		Recive_service[i] = MCAL_UART_receive_sysch();

	  }

	if(Recive_service[0]=='3' && Recive_service[1]=='1' && Recive_service[2]=='0'  && Recive_service[3]=='1'){

		for (int i= Initail_i; i< SIZE_ARRAY; i++){
		 	Routine[i] = MCAL_UART_receive_sysch();
		}

		for (int i= Initail_i; i < SIZE_ARRAY; i++){
		   if(Routine[i] != Saved_Routine[i]){

			   HAL_LCD_clearScreen();
			   HAL_LCD_displaystringRowColumn("7F 31 33" , 0 , 3);
		    }
			   if( security_access == 0){

				   HAL_LCD_clearScreen();
				   HAL_LCD_displaystringRowColumn("7F 31 33" , 0 , 3);
			   }

			   else{

				   HAL_LCD_clearScreen();
				   HAL_LCD_displaystringRowColumn("71 01 AA 00" , 0 , 2);
				   MCAL_Dio_WriteSinglePin(&LED_Routine,PIN0_ID,1);


			      }
		}
	}
		else if (Recive_service[0] =='2' && Recive_service[1] =='7' && Recive_service[2] =='0'  && Recive_service[3] =='1'){

			 HAL_LCD_clearScreen();
			 HAL_LCD_displaystringRowColumn("67 01" , 0 , 2);

			 _delay_ms(1000);
			 HAL_LCD_goToRowColumn(1,2);
			 for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

				 Random_array[i] = '0'+i ; // Generate a random array

				 Encrypted_Random[i] = Random_array[i] + 2;   //ECU
				// HAL_LCD_clearScreen();
				 HAL_LCD_sendCharacter(Random_array[i]);
				 HAL_LCD_sendCharacter(' ');
			    }
			 security_access =1;
		}


		else if(Recive_service[0] =='2' && Recive_service[1] =='7' && Recive_service[2] =='0'  && Recive_service[3] =='2' && security_access == 1){


			 for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

				 Verification_Random[i] = MCAL_UART_receive_sysch(); //User
			 }

			 for(int i = Initail_i ; i<SIZE_ARRAY ; i++){

				if(Verification_Random[i] == Encrypted_Random[i]){

					security_access=2;
					HAL_LCD_clearScreen();
				    HAL_LCD_displaystringRowColumn("67 02" , 0 , 2);

				  }

				else{

					HAL_LCD_clearScreen();
				    HAL_LCD_displaystringRowColumn("7F 27 35" , 0 , 2);
				}
			 }
		 }

		else{

			 // Do nothing
		}
	}

	return Process_State;
}
