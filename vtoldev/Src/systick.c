/*
 *  Created on: 21/09/2022
 *      Author: Daniel e Paulo
 */
#include "stm32l476xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VALUE		4000 							//value that divided by the system clock gives us 1 ms
#define	CTRL_ENABLE				(1U<<0)							//Enables the systick timer
#define CTRL_CLKSRC				(1U<<2)							//Defines if clock source is internal or external to the processor
#define CTRL_COUNTFLAG			(1U<<16)						//Bit witch returns 1 if timer counted to 0 since last time this was read.



void iSystickDelayMs(int delay){

	/*Reload the systick with the number of cycles per milliseconds*/
	SysTick->LOAD = SYSTICK_LOAD_VALUE;
	/*Clear the systick current value register*/
	SysTick->VAL = 0;
	/*Select the clock source and enable systick*/
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;

	/*creating the delay function it self*/

	for(int i=0; i<delay; i++){
		/*Wait until COUNTFLAG is set*/
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}		//reads the count flag, if it is equal to zero
		//continues waiting, meaning that the counter did not finished yet.
		//once it counts reaches the load value, the flag is raised and it breaks the loop



	}
	//Resets the SysTick Control and Status Register
	SysTick->CTRL = 0;

	// do this until all the milliseconds passed to the function has elapsed
}


