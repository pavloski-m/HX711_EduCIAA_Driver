/*
 * HX711_driver.c
 *
 *  Created on: 11 oct. 2021
 *      Author: pablo
 */

#include "HX711_driver.h"

// ======== Para configurar la ganancia =======================/

#define   	FACTOR_ESCALA_MG   	719  //Número por el que se divide la cuenta para que el valor se de en milgramos
#define		TARE_BUFFER			4
#define		MS_TARE_SAMPLES		10

/**
 * Se define una estructura interna al driver que no es visible al usuario.
 * Se utiliza para cargar las funciones definidas especificamente como port para
 * el hardware especifico.
 */

static port_HX711_t port_HX711_ctrl; //



// Función para inicializar el driver con las funciones del port y el módulo

bool_t init_HX711_Driver(module_t *modulo, gpioMap_t ADDO, gpioMap_t ADSK, uint8_t channelGain){

	bool_t assertInit;

	port_HX711_ctrl.configParameters = initHx711;
	port_HX711_ctrl.getRawData = readRawValue;
	port_HX711_ctrl.initUpdtISR = initISR_HX711;

	assertInit = port_HX711_ctrl.configParameters (ADDO, ADSK, channelGain);


	// Se cargan la variables del módulo que se pasó por referencia

	modulo->rawData = port_HX711_ctrl.getRawData();
	modulo->offset = modulo->rawData;
	modulo->filterValue = FILTER_INIT;
	modulo->escala = FACTOR_ESCALA_MG;
	modulo->estado_continuo = ONE_READ;

	modulo->offset = (int32_t) updateTare(modulo);

	return assertInit; 	// se puede pasar GPIO para configurar individualmente los módulos
}


// Función que toma la muestra para actualizar la tara
uint32_t updateTare (module_t *modulo){

	uint32_t suma = 0;

	for(int i=0; i<TARE_BUFFER; i++){

		suma += ((port_HX711_ctrl.getRawData())/4);
		delay(MS_TARE_SAMPLES);
	}

	return ((uint32_t) suma);

}

// Función para activar la conversión continua en el port
void activateISRConvertion(void){

	port_HX711_ctrl.initUpdtISR(CONVERTION, 4);

}


//Función para actualizar el valor
int32_t actualizarDato (module_t *modulo){

	static int32_t prevValue=0;

	int32_t datoaux = (int32_t)(port_HX711_ctrl.getRawData() - modulo->offset)/FACTOR_ESCALA_MG;

	float fdatoaux = (float) datoaux;
	float fprevVal = (float) prevValue;
	float ffilter  = ((float) modulo->filterValue) / 100;

	fprevVal = fprevVal*(1-ffilter) + fdatoaux*ffilter;

	prevValue = (int32_t) fprevVal;

	datoaux = prevValue;

	modulo->processedData = datoaux;

	return datoaux;
}

// Cuando quiero tener solo un dato crudo..
int32_t one_time_read_raw (void){
	// Acá tengo que poner solo lectura de un dato crudo
	return (port_HX711_ctrl.getRawData());
}


void calibrate(void){

	// rutina de calibración
	// se actualiza  el valor de escala
	// (Raw value con peso1 - Rawvalue sin peso) / peso1;

}
