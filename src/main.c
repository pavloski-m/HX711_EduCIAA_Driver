#include "main.h"   // <= own header (optional)
#include "sapi.h"     // <= sAPI header
#include "HX711port.h"
#include "HX711_driver.h"




int main (void)  {

	// Inicializar y configurar la plataforma
	boardConfig();



	 // Inicializar UART_USB a 115200 baudios. Esto es de SAPI!
	uartConfig( UART_USB, 115200 );



	/**
	 * Se inicializa el hardware especifico para este proyecto
	 */


	initHx711 (GPIO0, GPIO1, 128);

	inicialize(); //inicialización de balanza

	uartWriteString( UART_USB, "inicializa \r\n" );


	while(1)  {


		msgOffset(actualizarDato());

		delay(100);

	}
}

