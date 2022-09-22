/*
 * tim.h
 *
 *  Created on: 22/09/2022
 *      Author: daniel
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32l4xx.h"
#include <stdint.h>



void tim_1hz_init(void);

#define SR_UIF	(1U<<0)									//Status Register Update event flag


#endif /* TIM_H_ */
