/*********************************************************************************************************
 *
 * \file    ${file_name}
 * \brief   Librería para el manejo de pines GPIO
 * \date    ${date}
 * \author  Nicolás Ferragamo
 * \version 1.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/
#define  reserved_bits(x,y,z)   uint8_t reserved_bits##x[z-y+1];

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/
/**
 * @enum    gpio_port_e
 * @brief   Indica el Puerto.
 * @date    ${date}
 * @author  Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 */
typedef enum
{
    GPIO_PORTB = 0,
    GPIO_PORTC,
    GPIO_PORTD
} gpio_port_e;

/**
 * @enum    gpio_pin_e
 * @brief   Indica el pin.
 * @date    ${date}
 * @author  Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 */
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
} gpio_pin_e;


/**
 * @enum    gpio_mode_e
 * @brief   Indica el modo del GPIO.
 * @date    ${date}
 * @author  Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 */
typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 0x1,
    GPIO_GPIO_INPUT_PU = 0x2
} gpio_mode_e;

    


/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/

extern void GPIO_InitPin(gpio_port_e port, gpio_pin_e pin, gpio_mode_e mode); 

extern void GPIO_WritePin(gpio_port_e port, gpio_pin_e pin, bool value); 

extern void GPIO_TogglePin(gpio_port_e port, gpio_pin_e pin);

extern bool GPIO_ReadPin(gpio_port_e port, gpio_pin_e pin, bool value);

extern void GPIO_WritePort(gpio_port_e port, uint8_t value); 

extern uint8_t GPIO_ReadPort(gpio_port_e port);


#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
