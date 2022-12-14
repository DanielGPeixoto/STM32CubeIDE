/*Hello World Code
 *
 * Toggle LD_2 - User Led
 * Is connected to PORT A at PIN 5.
 * PORTA is connected to AHB2 BUS
 *
 * We need to find the GPIOA address. Look at memory map (stm32l476rg file).
 *
 * */


#define PERIPH_BASE			(0x40000000UL) 								//UL - Unsigned Long value

#define AHB2_OFFSET			(0x8000000)									//0x48000000−0x40000000 (Peripherals Base Address)
#define AHB1_OFFSET			(0x20000UL)									//0x40020000−0x40000000

#define AHB2_PERIPH_BASE	(PERIPH_BASE + AHB2_OFFSET)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_OFFSET)

#define GPIOA_OFFSET		(0x000UL)									//as it at the beginning of the range, the offset is zero
#define GPIO_BASE			(AHB2_PERIPH_BASE + GPIOA_OFFSET)



#define RCC_OFFSET			(0x1000UL)									//0x40021000−0x40020000
#define RCC_BASE 			(AHB1_PERIPH_BASE + RCC_OFFSET)


							/*(* ( volatile unsigned int *) -> cast to translate as register*/
#define AHB2EN_R_OFFSET		(0x4C)
#define RCC_AHB2EN_R		(*( volatile unsigned int *)(RCC_BASE + AHB2EN_R_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*( volatile unsigned int *)(GPIO_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14)
#define GPIOA_OD_R 			(*( volatile unsigned int *)(GPIO_BASE + OD_R_OFFSET))

#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5


#define GPIOAEN				(1U<<0)										//shifts 1 to position 0

int main(void){

	//Enable clock accesses to GPIOA
	RCC_AHB2EN_R |= GPIOAEN;
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);											//set's only 11th bit to 0


	while(1){

		for(int i = 0; i<100000; i++){}
		GPIOA_OD_R ^= LED_PIN;											//^= toggle operator
	}
}


