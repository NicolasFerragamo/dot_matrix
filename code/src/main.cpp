/*********************************************************************************************************
 *                                               <Module name>
 *						<Module description>
 *
 *						<Copyright>
 *
 *						<Copyright or distribution terms>
 *
 *
 *********************************************************************************************************/

/*********************************************************************************************************
 *                                               <File description>
 *
 * Filename	: Filename
 * Version	: Module version
 * Programmer(s) : Programmer initial(s)
 **********************************************************************************************************
 *  Note(s):
 *
 *
 *
 *********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		${file_name}
 * \brief		Descripción del modulo
 * \date		${date}
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version
 *********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
 *********************************************************************************************************/
#include <Arduino.h>
#include "gpio.h"
#include "API_delay.h"
#include "dot_matrix.h"

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 *********************************************************************************************************/
#define MAX_DISPLAY 100
#define BUFFER_SIZE 15
/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 *   se escriben en CamelCase y están precedidas por la identificación del
 *   módulo seguida de un _
 *   ej: MEM_POOL  Mem_PoolHeap;
 *********************************************************************************************************/
volatile uint64_t total_ms = 0, tiempo = 0, tiempo2 = 0;
uint8_t buffer[BUFFER_SIZE];

uint8_t display[MAX_DISPLAY]; //!< cada bit representa una fila, cada byte una columna /*


/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 *   se declaran con static y se escriben en CamelCase y están precedidas por la
 *   identificación del módulo seguida de un _ y usan _ para separar las palabras
 *   cuando tienen nombres compuestos
 *   ej: static MEM_POOL  Mem_Pool_Heap;
 *********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 * se declaran como estáticas y se escriben en CamelCase, están precedidas por la
 * identificación del módulo seguida de un _. No se declaran en el .h
 * ej static void Clk_DateTimer(parámetros)
 *********************************************************************************************************/
void Timer0_init(void);

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 *********************************************************************************************************/
void Timer0_init(void)
{
  TCCR0A = (1 << WGM01);              // Activa el bit CTC (clear timer on compare match) del TCCR0A (timer counter/control register)
  OCR0A = 249;                        // Valor de comparación para interrumpir cada 1 ms (16 MHz / 64 / 1000 - 1)
  TCCR0B = (1 << CS01) | (1 << CS00); // Preescaler de 64
  TIMSK0 = (1 << OCIE0A);             // Habilita las interrupciones en timer compare
}

ISR(TIMER0_COMPA_vect)
{
  total_ms++;
}

/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 *********************************************************************************************************/

/**
  \fn  		  main
  \brief 		Eemplo de uso de la librería dot_matrix
  \author 	Nombre
  \date 		${date}
  \return tipo 	y descripción de retorno
*/

int main(void)
{
  uint8_t index = 0;
  Serial.begin(9600);
  Timer0_init();
  inicializar_matriz();
  sei();
  tiempo = total_ms;
  tiempo2 = total_ms;
  enviar_mensaje(display, sizeof(display) / sizeof(display[0]), (const uint8_t *)"hola mundo");
  Serial.println("Ingrese el mensaje a mostrar: \n");
  while (true)
  {

    if (Serial.available() > 0)
    {
      // Leer un byte del puerto serie
      char receivedChar = Serial.read();
      // Si el carácter es de nueva línea (indicando fin de cadena)
      if (receivedChar == '\n')
      {
        // Agregar un carácter nulo al final para finalizar la cadena
        buffer[index] = '\0';

        // Imprimir la cadena recibida
        Serial.print("Received: ");
        // Reiniciar el índice para la próxima cadena
        index = 0;
        enviar_mensaje(display, sizeof(display) / sizeof(display[0]), (const uint8_t *)buffer);
      }
      else
      {
        // Si el índice es menor que el tamaño del buffer, añadir el carácter
        if (index < BUFFER_SIZE - 1)
        {
          buffer[index++] = receivedChar;
        }
      }
    }

    barrido_matriz(display);
    desplazar_izq(display, sizeof(display) / sizeof(display[0]));
  }
  return 1;
}