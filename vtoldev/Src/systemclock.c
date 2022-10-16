/*
 *  Created on: 21/09/2022
 *      Author: Daniel e Paulo
 */
#include "stm32l4xx.h"

void systemclock(){
	//HSI16 always enable for peripheral
	RCC->CR	|=	(1U<<8);
	//Wait for HSI Clock Ready Flag
	while(!(RCC->CR & (1U<<10)));


	//Set Power Enable Clock (Power Interface Clock Enable)
	RCC->APB1ENR1 |= (1U<<28);
	//Set Dynamic Voltage Scaling Management to Range 1
	PWR->CR1 		|=	(1U<<9);
	PWR->CR1 		&=~	(1U<<10);

	//Adjust number of waiting states according to the new frequency
	FLASH->ACR 		|=	(1U<<8); //ENABLE Pre-Fetch, to increase efficiency of bus access
	FLASH->ACR		&=~	(1U<<0);
	FLASH->ACR		&=~	(1U<<1);
	FLASH->ACR		|=	(1U<<2);
	//Configured with 4 wait states
	//PPRE1[2:0]: PPRE2[2:0]: HPRE[3:0]: configure system clock not divide

	//Disable the PLL by setting PLLON
	RCC->CR 		&=~	(1U<<24);
	//Wait until PLLRDY is cleared
	//while((RCC->CR 	&	(1U<<25)));

	//PLLSRC: Main PLL, PLLSAI1 and PLLSAI2 entry clock source
	//10: HSI16 clock selected as PLL, PLLSAI1 and PLLSAI2 clock entry
	RCC->PLLCFGR &= (1U<<0);
	RCC->PLLCFGR |= (1U<<1);

	//PLLM: Division factor for the main PLL and audio PLL = 1
	//VCO input frequency = PLL input clock frequency / PLLM
	RCC->PLLCFGR	&=~	(1U<<4);
	RCC->PLLCFGR	&=~	(1U<<5);
	RCC->PLLCFGR	&=~	(1U<<6);

	//PLLN[6:0]: Main PLL multiplication factor for VCO PLLN = 10
	//VCO output frequency = VCO input frequency x PLLN
	RCC->PLLCFGR	&=~	(1U<<8);
	RCC->PLLCFGR	|=	(1U<<9);
	RCC->PLLCFGR	&=~	(1U<<10);
	RCC->PLLCFGR	|=	(1U<<11);
	RCC->PLLCFGR	&=~	(1U<<12);
	RCC->PLLCFGR	&=~	(1U<<13);
	RCC->PLLCFGR	&=~	(1U<<14);

	//PLLP: Main PLL division factor for PLLSAI3CLK (SAI1 and SAI2 clock).
	//LLSAI3CLK	output clock frequency = VCO frequency / PLLP with PLLP = 7
	RCC->PLLCFGR 	&=~	(1U<<17);

	//PLLQ[1:0]: Main PLL division factor for PLL48M1CLK (48 MHz clock).
	//PLLCLK output clock frequency = VCO frequency / PLLR	with PLLQ = 2
	RCC->PLLCFGR	&=~	(1U<<21);
	RCC->PLLCFGR	&=~	(1U<<22);

	//PLLR[1:0]: Main PLL division factor for PLLCLK = 2
	//PLLCLK output clock frequency = VCO frequency / PLLR
	RCC->PLLCFGR	&=~	(1U<<25);
	RCC->PLLCFGR	&=~	(1U<<26);

	//Enable the PLL by setting PLLON
	RCC->CR 		|=	(1U<<24);
	//while(!(RCC->CR & 	RCC_CR_PLLRDY));

	//PLLPEN: Main PLL PLLSAI3CLK output enable
	RCC->PLLCFGR	|=	(1U<<16);
	//PLLREN: Main PLL PLLCLK output enable
	RCC->PLLCFGR	|=	(1U<<24);

	//SW System clock switch. 11: PLL selected as system clock
	RCC->CFGR		|= (1U<<0);
	RCC->CFGR		|= (1U<<1);

	//SWS System clock switch status. 11: PLL used as system clock
	while( (!(RCC->CFGR	& (1U<<2))) && (!(RCC->CFGR	& (1U<<3)))	);

}
