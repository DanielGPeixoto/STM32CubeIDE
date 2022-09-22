/*
 * adc.h
 *
 *  Created on: 21/09/2022
 *      Author: daniel
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32l4xx.h"
#include <stdint.h>

void PA4_ADC1_INIT(void);
uint32_t adc_read(void);
void start_conversion(void);


#endif /* ADC_H_ */
