/*
 * UART_Message.c
 *
 *  Created on: 16 ago. 2021
 *      Author: pablo
 */

#include "UART_Message.h"

/*=============================================================================
 * Function: *itoa
 * Description: Esta función transforma de dato numérico a un char de caracteres
 * 		ASCII. Lo carga en el vector de char del puntero que recibe. También se
 * 		especifica la base en la que está el número.
 * Input: recibe el valor a convertir, el puntero del vector de char en donde se
 * 		debe escribir el valor convertido y la base en la que se desea decodificar
 * 		el número.
 *===========================================================================*/
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

static char uartBuff[20];

void initUART(uartMap_t UART_CHANNEL, uint32_t BAUD_RATE){
	uartConfig( UART_CHANNEL, BAUD_RATE );
}

void msgNoAdq(void){
	uartWriteString( UART_USB, "Estado de no adquisicion\r\n" );
}

void msgAdq(void){
	uartWriteString( UART_USB, "Comienza la adquisicion\r\n" );
}

void msgOffset(uint32_t Offset){
	uartWriteString( UART_USB, "Inicializacion..\r\n" );
	itoa( Offset, uartBuff, 10 ); /* número en base 10 */
	uartWriteString( UART_USB, "El OFFSET es: " );
	uartWriteString( UART_USB, uartBuff );
	uartWriteString( UART_USB, "\r\n" );
}

void msgValor(int32_t valor){
	itoa( valor, uartBuff, 10 ); /* 10 significa decimal */
	uartWriteString( UART_USB, uartBuff );
	uartWriteString( UART_USB, "\r\n" );
}

void msgError(void){
	uartWriteString( UART_USB, "estado de ERROR\r\n" );
}
