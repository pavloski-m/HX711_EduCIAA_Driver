/*
 * HX711port.c
 *
 *  Created on: 9 oct. 2021
 *      Author: Pablo Morzán
 */

#include "HX711port.h"

// ======== Para configurar interrupción =======================/
// SCU
#define GPIO0_SCU_PORT  	6
#define GPIO0_SCU_PIN    	1
#define GPIO0_SCU_FUNC   	SCU_MODE_FUNC0

// GPIO
#define GPIO0_GPIO_PORT  	3
#define GPIO0_GPIO_PIN   	0

// Interrupt
#define PININT_INDEX         0                  // PININT index used for GPIO mapping
#define PININT_IRQ_HANDLER   GPIO0_IRQHandler   // GPIO interrupt IRQ function name
#define PININT_NVIC_NAME     PIN_INT0_IRQn      // GPIO interrupt NVIC interrupt name

#define CICLOS_NO_CONV		8

//%%%%%%%%%%%%%%%%%%%%%%%%%%%  Declaración de variables globales   %%%%%%%%%%%%%%%%

static uint8_t sckCycles = 1;
static gpioMap_t clkSignal;
static gpioMap_t outSignal;
static uint32_t raw_data;
static int8_t ISRFilter;



// Inicialización de la rutina de interrupción con LPC Open
void initISR_HX711(ISRC_State_t int_HX711, int8_t FiltroISR){

	if(CONVERTION == int_HX711){
		ISRFilter = FiltroISR;
	// ---> Comienzo de funciones LPCOpen para configurar la interrupcion
		Chip_PININT_Init( LPC_GPIO_PIN_INT );
		// Configure interrupt channel for the GPIO pin in SysCon block
		Chip_SCU_GPIOIntPinSel( PININT_INDEX, GPIO0_GPIO_PORT, GPIO0_GPIO_PIN );

	   // Configure channel interrupt as edge sensitive and falling edge interrupt
	   Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH0 );
	   Chip_PININT_SetPinModeEdge( LPC_GPIO_PIN_INT, PININTCH0 );
	   Chip_PININT_EnableIntHigh( LPC_GPIO_PIN_INT, PININTCH0 );

	   // Enable interrupt in the NVIC
	   NVIC_ClearPendingIRQ( PININT_NVIC_NAME );
	   NVIC_EnableIRQ( PININT_NVIC_NAME );
	   // ---> Fin de funciones LPCOpen
	}
	else{
		NVIC_DisableIRQ( PININT_NVIC_NAME );
	}


}


// Handler interrupt from GPIO pin or GPIO pin mapped to PININT
void GPIO0_IRQHandler(void)
{	static uint8_t counter = CICLOS_NO_CONV;
   // Se da aviso que se trato la interrupcion

	if(counter<1){
	   NVIC_DisableIRQ( PININT_NVIC_NAME );
	   counter=8;

	   raw_data = ((ISRFilter-1)*raw_data/ISRFilter) + readRawValue()/ISRFilter;  // De esta manera puedo suavizar datos
	}

	counter--;

	NVIC_EnableIRQ( PININT_NVIC_NAME );
	Chip_PININT_ClearIntStatus( LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX) );
}


//Configuración de lo parametros del módulo para selección de canales y pines IN y OUT
bool_t initHx711 (gpioMap_t ADDO, gpioMap_t ADSK, uint8_t channelGain){


	switch (channelGain){
		case 128:
			sckCycles = 1;
			break;

		case 64:
			sckCycles = 2;
			break;

		case 32:
			sckCycles = 3;
			break;

		default: sckCycles = 1;
	}

	clkSignal = ADSK;
	outSignal = ADDO;

	gpioInit( ADSK, GPIO_OUTPUT );
	gpioInit( ADDO, GPIO_INPUT_PULLUP );


	return 1;
}


// Función para consultar el dato que se refresca por ISR
uint32_t readRawValueISR (void){

	return raw_data;
}


// Proceso de lectura del módulo...
uint32_t readRawValue (void){

	uint32_t rawdata;

	while(gpioRead(outSignal));

	for (uint8_t i=0; i<24; i++){

		gpioWrite(clkSignal, 1);

		rawdata = rawdata << 1;

		gpioWrite(clkSignal, 0);

		if(gpioRead(outSignal)) {rawdata++;}
	}


	for (uint8_t i=0; i<sckCycles; i++){
		gpioWrite(clkSignal, 1);

		gpioWrite(clkSignal, 0);


	}

	rawdata=rawdata^0x800000;  // Hace el complemento a 2 con XOR

	return (rawdata);
}
