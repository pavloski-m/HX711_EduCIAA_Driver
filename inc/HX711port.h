/*
 * HX711port.h
 *
 *  Created on: 10 oct. 2021
 *      Author: pablo
 */

#ifndef HX711_EDUCIAA_DRIVER_INC_HX711PORT_H_
#define HX711_EDUCIAA_DRIVER_INC_HX711PORT_H_

#include "chip.h"
#include "sapi.h"
#include "sapi_gpio.h"


bool_t initHx711 (gpioMap_t ADDO, gpioMap_t ADSK, uint8_t channelGain);

uint32_t readRawValue (void);


#endif /* HX711_EDUCIAA_DRIVER_INC_HX711PORT_H_ */
