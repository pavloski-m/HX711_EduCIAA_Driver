/*
 * HX711_driver.c
 *
 *  Created on: 11 oct. 2021
 *      Author: pablo
 */

#include "HX711_driver.h"

static char uartBuff[10];
static uint32_t sgnFilter;
static uint32_t dataTare;
//


char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


void inicialize(){
	updateTare();

	sgnFilter = 50;
	//prevValue=0;

	uartWriteString( UART_USB, "Inicilización correcta..\r\n" );
}


void msgOffset(uint32_t Offset){

	itoa( Offset, uartBuff, 10 ); /* número en base 10 */
	uartWriteString( UART_USB, uartBuff );
	uartWriteString( UART_USB, "\r\n" );

}


void incFiltro (void){

	sgnFilter += 5;
	if (sgnFilter>100){
		sgnFilter = 100;}

}


void decFiltro (void){

	sgnFilter -= 5;
	if (sgnFilter<5){
		sgnFilter = 5;}

}


void updateTare (){

	dataTare = readRawValue();

//	uint32_t suma = 0;
//	for(int i=0; i<4; i++){
//		suma += readRawValue()/4;
//		delay(10);
//	}
//	dataTare = (uint32_t) suma;
}


int32_t actualizarDato (void){

	static int32_t prevValue=0;

	int32_t datoaux = readRawValue() - dataTare;

	prevValue = prevValue/2 + datoaux/2;

	datoaux = prevValue/719;

	return datoaux;
}


void calibrate(void){


}
