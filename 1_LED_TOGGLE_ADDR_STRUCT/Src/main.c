/*Hello World Code
 *
 * Toggle LD_2 - User Led using the structure address method
 *
 * Is connected to PORT A at PIN 5.
 * PORTA is connected to AHB2 BUS
 *
 * We need to find the GPIOA address. Look at memory map (stm32l476rg file).
 *
 * */

/*
 * We still need all the registers base addresses*/

#include <stdint.h>														//necessary to use data type

#define PERIPH_BASE			(0x40000000UL) 								//UL - Unsigned Long value
#define AHB2_OFFSET			(0x8000000)									//0x48000000−0x40000000 (Peripherals Base Address)
#define AHB1_OFFSET			(0x20000UL)									//0x40020000−0x40000000
#define AHB2_PERIPH_BASE	(PERIPH_BASE + AHB2_OFFSET)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_OFFSET		(0x000UL)									//as it at the beginning of the range, the offset is zero
#define GPIO_BASE			(AHB2_PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET			(0x1000UL)									//0x40021000−0x40020000
#define RCC_BASE 			(AHB1_PERIPH_BASE + RCC_OFFSET)

/*But we no longer need the add offset method
 * 								//(* ( volatile unsigned int *) -> cast to translate as register
	#define AHB2EN_R_OFFSET		(0x4C)
	#define RCC_AHB2EN_R		(*( volatile unsigned int *)(RCC_BASE + AHB2EN_R_OFFSET))

	#define MODE_R_OFFSET		(0x00UL)
	#define GPIOA_MODE_R		(*( volatile unsigned int *)(GPIO_BASE + MODE_R_OFFSET))

	#define OD_R_OFFSET			(0x14)
	#define GPIOA_OD_R 			(*( volatile unsigned int *)(GPIO_BASE + OD_R_OFFSET))
 *
 * */

typedef struct{
	volatile uint32_t	MODER;
	volatile uint32_t	OTYPER;
	volatile uint32_t	OSPEEDR;
	volatile uint32_t	PUPDR;
	volatile uint32_t	IDR;
	volatile uint32_t	ODR;
	volatile uint32_t	BSRR;
	volatile uint32_t	LCKR;
	volatile uint32_t	AFR[2];
	volatile uint32_t	BRR;
	volatile uint32_t	ASCR;
}GPIO_TypeDef;

#define GPIOA					((GPIO_TypeDef *) GPIO_BASE)


typedef struct{
	volatile uint32_t	CR;
	volatile uint32_t	ICSCR;
	volatile uint32_t	CFGR;
	volatile uint32_t	PLLCFGR;
	volatile uint32_t	PLLSAI1CFGR;
	volatile uint32_t	PLLSAI2CFGR;
	volatile uint32_t	CIER;
	volatile uint32_t	CIFR;
	volatile uint32_t	CICR;
	uint32_t	reserved0;
	volatile uint32_t	AHB1RSTR;
	volatile uint32_t	AHB2RSTR;
	volatile uint32_t	AHB3RSTR;
	uint32_t	reserved1;
	volatile uint32_t	APB1RSTR1;
	volatile uint32_t	APB1RSTR2;
	volatile uint32_t	APB2RSTR;
	uint32_t	reserved2;
	volatile uint32_t	AHB1ENR;
	volatile uint32_t	AHB2ENR;
	volatile uint32_t	AHB3ENR;
	uint32_t	reserved3;
	volatile uint32_t	APB1ENR1;
	volatile uint32_t	APB1ENR2;
	volatile uint32_t	APB2ENR;
	uint32_t	reserved4;
	volatile uint32_t	AHB1SMENR;
	volatile uint32_t	AHB2SMENR;
	volatile uint32_t	AHB3SMENR;
	uint32_t	reserved5;
	volatile uint32_t	APB1SMENR1;
	volatile uint32_t	APB1SMENR2;
	volatile uint32_t	APB2SMENR;
	uint32_t	reserved6;
	volatile uint32_t	CCIPR;
	uint32_t	reserved7;
	volatile uint32_t	BDCR;
	volatile uint32_t	CSR;

}RCC_TypeDef;

#define RCC					((RCC_TypeDef *) RCC_BASE)

#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5


#define GPIOAEN				(1U<<0)										//shifts 1 to position 0

int main(void){

	/*
	//Enable clock accesses to GPIOA
	RCC_AHB2EN_R |= GPIOAEN;
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);											//set's only 11th bit to 0
	 */
	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	//Enabling clock accesses to GIPOA using structures method


	while(1){

		for(int i = 0; i<100000; i++){}
		//GPIOA_OD_R ^= LED_PIN;											//^= toggle operator
		GPIOA->ODR ^= LED_PIN;
	}
}


