/*********************************************************************************************************
 *
 * \file		${file_name}
 * \brief		Librería para el manejo de pines GPIO
 * \date		${date}
 * \author		Nicolás Ferragamo
 * \version     1.0 
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"


/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/
#define GPIO_BASE_PIN_ADDR  0x23
#define GPIO_BASE_DDR_ADDR  0x24
#define GPIO_BASE_PORT_ADDR 0x25

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
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
*********************************************************************************************************/
volatile uint8_t* const GPIO_PIN  = (uint8_t*)  GPIO_BASE_PIN_ADDR;
volatile uint8_t* const GPIO_DDR  = (uint8_t*)  GPIO_BASE_DDR_ADDR;
volatile uint8_t* const GPIO_PORT = (uint8_t*)  GPIO_BASE_PORT_ADDR;

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
*********************************************************************************************************/

/**
	\fn  		void GPIO_InitPin(gpio_port_e port, gpio_pin_e pin, gpio_mode_e mode)
	\brief 		Función encargada de la inicialización de los pines
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
    \param      mode [in] Modo del pin GPIO_OUTPUT, GPIO_INPUT, GPIO_INPUT_PU
    \return     void
*/
void GPIO_InitPin(gpio_port_e port, gpio_pin_e pin, gpio_mode_e mode)
{
	*(GPIO_DDR + port*3)  &= ~(1 << pin);
	*(GPIO_DDR + port*3)  |= ((mode&0x01) << pin);
	*(GPIO_PORT + port*3) |= (((mode>>0x1)&0x01) << pin);
}

/**
	\fn  		void GPIO_WritePin(gpio_port_e port, gpio_pin_e pin, bool value)

	\brief 		Función encargada de escribir los pines
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
    \param      value [in] HIGH, LOW
    \return     void
*/
void GPIO_WritePin(gpio_port_e port, gpio_pin_e pin, bool value)
{
	*(GPIO_PORT + port*3)  &= ~(1 << pin);
	*(GPIO_PORT + port*3)  |= ((value&0x01) << pin);
}

/**
	\fn  		inline void GPIO_TogglePin(gpio_port_e port, gpio_pin_e pin)
	\brief 		Función encargada de invertir el valor del pin
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
    \return     void
*/
inline void GPIO_TogglePin(gpio_port_e port, gpio_pin_e pin)
{
	*(GPIO_PORT + port*3)  ^= (1 << pin);
}

/**
	\fn  		GPIO_ReadPin(gpio_port_e port, gpio_pin_e pin)
	\brief 		Función encargada de leer el valor del pin
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
	\param      pin  [in] value true, false
    \return     Retorna true si el pin tiene el mismo estado que value, de lo contrario retorna false
*/
inline bool GPIO_ReadPin(gpio_port_e port, gpio_pin_e pin, bool value)
{ 
	return (((*(GPIO_PIN + port*3) >> pin) & 0x01) == value) ? true : false;
}

/**
	\fn  		GPIO_WritePort(gpio_port_e port, uint8_t value)
	\brief 		Función encargada de escribir el valor del puerto
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
    \return     void
*/
inline void GPIO_WritePort(gpio_port_e port, uint8_t value)
{
	*(GPIO_PORT + port*3)  = value;
}

/**
	\fn  		inline uint8_t GPIO_ReadPort(gpio_port_e port)
	\brief 		Función encargada de leer el valor del puerto
	\date		${date}
    \author		Nicolás Ferragamo
    \param      port [in] Puerto B, C, D
    \param      pin  [in] pin 1,2 ... 7
    \return     value: el valor del puerto
*/
inline uint8_t GPIO_ReadPort(gpio_port_e port)
{
	return ((*(GPIO_PIN + port*3) & 0xFF));
}
