/*
 * UART_Message.h
 *
 *  Created on: 16 ago. 2021
 *      Author: Pablo Morzán
 */

#ifndef _UART_MESSAGE_H_
#define _UART_MESSAGE_H_

#include "sapi.h"

/*=============================================================================
 * Function: initUART
 * Description: Se inicializa la UART en configuración 115200 baudios.
 * 		Se utiliza la configuración standard: 8bits, sin paridad, 1 bit de parada
 *===========================================================================*/
void initUART(uartMap_t UART_CHANNEL, uint32_t BAUD_RATE);

/*=============================================================================
 * Function: msgNoAdq
 * Description: Se envía mensaje por puerto seríe que hace referencia al estado
 * 		de no comunicación.
 *===========================================================================*/
void msgNoAdq(void);

/*=============================================================================
 * Function: msgAdq
 * Description: Se envía mensaje por puerto seríe que hace referencia al estado
 * 		de comienzo de comunicación.
 *===========================================================================*/
void msgAdq(void);

/*=============================================================================
 * Function: msgError
 * Description: Se envía mensaje por puerto seríe que hace referencia al estado
 * 		de entrada de estado de error.
 *===========================================================================*/
void msgError(void);

/*=============================================================================
 * Function: msgOffset
 * Description: Se pasa el valor numérico por parametro, luego se transforma a
 * 		ASCII y se muestra por el puerto serie luego la palabra "Offset: "
 * Input: se le pasa el valor de offset con el que se inicializa.
 * Output: No retorna nada. Pero saca por terminal serie un mensaje haciendo
 * 		referencia al offset de medición.
 *===========================================================================*/
void msgOffset(uint32_t Offset);

/*=============================================================================
 * Function: msgValor
 * Description: Se pasa el valor numérico por parametro, luego se transforma a
 * 		ASCII y se muestra por el puerto serie.
 * Input: se le pasa el valor que hace referencia al led que se quiere encender
 * Output: Si led enciende devuelve 1 y si no 0
 *===========================================================================*/
void msgValor(int32_t valor);


#endif /* _UART_MESSAGE_H_ */
