/*
 * defs.h
 *
 *  Created on: 04/10/2017
 *      Author: Fernando
 */

#ifndef SOURCES_DEFS_H_
#define SOURCES_DEFS_H_

#include "MKL25Z4.h"
#include <stdint.h>

#ifndef NULL
#define NULL  ((void*)0)
#endif

typedef enum {
   FALSE,
   TRUE
} bool_t;

#define disable() NVIC_DisableIRQ(SysTick_IRQn);
#define enable()  NVIC_EnableIRQ(SysTick_IRQn);


#endif /* SOURCES_DEFS_H_ */
