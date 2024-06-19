/*********************************************************************************************************
 *
 * \file		${file_name}
 * \brief		Librería para el manejo de matriz de puntos
 * \date		${date}
 * \author		Nicolás Ferragamo
 * \version     1.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef __DOT_MATRIX_H
#define __DOT_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include <stdlib.h>

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/
#define  RCK GPIO_PORTB,GPIO_PIN0  //!<   /*
#define  SCK GPIO_PORTB,GPIO_PIN1  //!<   /*
#define  SI  GPIO_PORTB,GPIO_PIN2  //!<   /*
#define  G_L GPIO_PORTB,GPIO_PIN3  //!< Es normal negado  /*

#define MAX_ROWS 7
#define MAX_COLS 40

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/
#ifndef _RESERVED_BITS
#define _RESERVED_BITS
#define  reserved_bits(x,y,z)   uint8_t reserved_bits##x[z-y+1];
#endif
/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/
/**
 * @enum  estado_barrrido_e
 * @brief Indica la fila a barrer.
 * @date ${date}
 * @author Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 */
typedef enum
{ FILA1 = 0,
  FILA2,
  FILA3,
  FILA4,
  FILA5,
  FILA6,
  FILA7
} estado_barrrido_e;


/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/

extern void desplazar_izq(uint8_t* display, size_t cols);

extern void inicializar_matriz(void);

extern void enviar_mensaje(uint8_t* display, size_t max_disp, const uint8_t* mensaje);

extern void barrido_matriz(uint8_t *display);

#ifdef __cplusplus
}
#endif

#endif /* __DOT_MATRIX_H */
