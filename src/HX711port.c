/*
 * HX711port.c
 *
 *  Created on: 9 oct. 2021
 *      Author: Pablo Morzán
 */

#include "HX711port.h"


//%%%%%%%%%%%%%%%%%%%%%%%%%%%  Declaración de variables globales   %%%%%%%%%%%%%%%%

static uint8_t sckCycles = 1;
static gpioMap_t clkSignal;
static gpioMap_t outSignal;

//sbit ADDO = P1^5;
//sbit ADSK = P0^0;
//unsigned long ReadCount(void){
// unsigned long Count;
// unsigned char i;
// ADDO=1;
// ADSK=0;
// Count=0;
// while(ADDO);
// for (i=0;i<24;i++){
// ADSK=1;
// Count=Count<<1;
// ADSK=0;
// if(ADDO) Count++;
// }
// ADSK=1;
// Count=Count^0x800000;
// ADSK=0;
// return(Count);
//}

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

		default: return 1;
	}
	//chequeo si ADDO y ADSK son variables válidas
	clkSignal = ADSK;
	outSignal = ADDO;

	uartWriteString( UART_USB, "inicializa \r\n" );

	gpioInit( clkSignal, GPIO_OUTPUT );
	gpioInit( outSignal, GPIO_INPUT );


	return 0;
}


uint32_t readRawValue (void){

	uint32_t rawdata;

	while(gpioRead(outSignal));

	for (uint8_t i=0; i<24; i++){

		gpioWrite(clkSignal, 1);

		rawdata = rawdata << 1;

		//delayInaccurateUs(1);
		gpioWrite(clkSignal, 0);
		//delayInaccurateUs(1);

		if(gpioRead(outSignal)) {rawdata++;}
	}


	for (uint8_t i=0; i<sckCycles; i++){
		gpioWrite(clkSignal, 1);

		//delayInaccurateUs(1);

		gpioWrite(clkSignal, 0);

		//delayInaccurateUs(1);

	}

	rawdata=rawdata^0x800000;

	return (rawdata);
}
