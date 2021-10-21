#include "main.h"   // <= own header (optional)
#include "sapi.h"     // <= sAPI header
#include "HX711port.h"
#include "HX711_driver.h"
#include "UART_Message.h"
#include "sapi_gpio.h"

#define BAUD_RATE			115200
#define UART_CHANNEL		UART_USB



int main (void)  {


	// Inicializar y configurar la plataforma
	boardConfig();

	// Inicializar UART_USB a 115200 baudios.
//================ UART ======================
	uartMap_t UART_CHANNEL = UART_USB;

	initUART(UART_CHANNEL, BAUD_RATE);
//============================================

	module_t modulo1;			// Aqui instancio las variables de  mi módulo

	bool_t assert;


	assert = init_HX711_Driver(&modulo1, GPIO0, GPIO1, 128); // Inicializo el driver con el módulo

	if(!assert){
		msgError();
	}

	uint32_t a;

	while(1)  {


		a = actualizarDato (&modulo1);

		msgValor(a);

		delay(100);

	}
}

