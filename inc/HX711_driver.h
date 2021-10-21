/*
 * HX711_driver.h
 *
 *  Created on: 11 oct. 2021
 *      Author: pablo
 */

#include "sapi.h"
#include "sapi_gpio.h"
#include "HX711port.h"

#ifndef HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_
#define HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_

#define FILTER_MAX			100
#define FILTER_MIN			10
#define FILTER_INIT			(FILTER_MAX - FILTER_MIN)/2


//=========================Puntero a funciones======================================

typedef	bool_t	(*INIT_DRIVER)(gpioMap_t, gpioMap_t, uint8_t);        // acá voy a pasar los punteros de funciones al objeto
typedef uint32_t (*HX711_GETDATA) (void);	// es la función que devuelve el dato crudo de la medición.
typedef void	(*CONTINUOUS_UPDATE) (ISRC_State_t int_HX711, int8_t ISRFil);	//

//=======================Estructura con instancia de punteros a funciones===========

typedef struct {							// Estructura con punteros a funciones
	INIT_DRIVER			configParameters;
	HX711_GETDATA 		getRawData;			// Para pedir un dato
	CONTINUOUS_UPDATE 	initUpdtISR;		// Para activar el refresco continuo
}port_HX711_t;


//========================Estructura de cada módulo que se instancia ===============
typedef struct {
	uint32_t		rawData;
	int32_t 		processedData;
	uint32_t 		offset;
	uint16_t 		filterValue;
	uint16_t		escala;
	ISRC_State_t	estado_continuo;
}module_t;


//========================= Prototipos a funciones ====================================
char* itoa(int value, char* result, int base);

bool_t init_HX711_Driver(module_t *modulo, gpioMap_t ADDO, gpioMap_t ADSK, uint8_t channelGain);

uint32_t updateTare (module_t *modulo);

int32_t actualizarDato (module_t *modulo);

int32_t one_time_read_raw (void);

void calibrate(void);


#endif /* HX711_EDUCIAA_DRIVER_INC_HX711_DRIVER_H_ */
