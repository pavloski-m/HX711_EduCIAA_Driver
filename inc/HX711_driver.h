/*
 * HX711_driver.h
 *
 *  Created on: 11 oct. 2021
 *      Author: pablo
 */

#include "sapi.h"
#include "HX711port.h"

#ifndef HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_
#define HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_


char* itoa(int value, char* result, int base);

void inicialize();

void msgOffset(uint32_t Offset);

void incFiltro (void);

void decFiltro (void);

void updateTare ();

int32_t actualizarDato (void);

void calibrate(void);


#endif /* HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_ */
