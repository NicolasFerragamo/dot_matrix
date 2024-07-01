/*********************************************************************************************************
 *
 * \file        ${file_name}
 * \brief       Librería para el manejo de matriz de puntos
 * \date        ${date}
 * \author      Nicolás Ferragamo
 * \version     1.0
 *********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
 *********************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "dot_matrix.h"
#include "gpio.h"
#include <util/delay.h>
#include "API_delay.h"

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 *********************************************************************************************************/

#define LOW 0
#define HIGH 1

/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 *********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 *********************************************************************************************************/
/**
 * @brief   Tabla de caracteres para mostrar en la matriz de puntos
 * @date    ${date}
 * @author  Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 */

static uint8_t tabla[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // espacio
    0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, // $
    0x23, 0x13, 0x08, 0x64, 0x62, 0x00, // %
    0x36, 0x49, 0x55, 0x22, 0x50, 0x00, // &
    0x00, 0x05, 0x03, 0x00, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, // )
    0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, // +
    0x00, 0x50, 0x30, 0x00, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, // -
    0x00, 0x60, 0x60, 0x00, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, 0x00, // /
    0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, 0x00, // 2
    0x21, 0x41, 0x45, 0x4B, 0x31, 0x00, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, 0x00, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, 0x00, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, 0x00, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, 0x00, // ;
    0x08, 0x14, 0x22, 0x41, 0x00, 0x00, // <
    0x14, 0x14, 0x14, 0x14, 0x14, 0x00, // =
    0x00, 0x41, 0x22, 0x14, 0x08, 0x00, // >
    0x02, 0x01, 0x51, 0x09, 0x06, 0x00, // ?
    0x32, 0x49, 0x79, 0x41, 0x3E, 0x00, // @
    0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, // C
    0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, // F
    0x3E, 0x41, 0x49, 0x49, 0x7A, 0x00, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, // H
    0x41, 0x41, 0x7F, 0x41, 0x41, 0x00, // I
    0x20, 0x40, 0x40, 0x40, 0x3F, 0x00, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, // R
    0x46, 0x49, 0x49, 0x49, 0x31, 0x00, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, // V
    0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00, // W
    0x63, 0x14, 0x08, 0x14, 0x63, 0x00, // X
    0x07, 0x08, 0x70, 0x08, 0x07, 0x00, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, 0x00, // Z
    0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, // [
    0x02, 0x04, 0x08, 0x10, 0x20, 0x00, // "\"
    0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, 0x00, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, 0x00, // _
    0x00, 0x01, 0x02, 0x04, 0x00, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, 0x00, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, // b
    0x38, 0x44, 0x44, 0x44, 0x00, 0x00, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, // d
    0x38, 0x54, 0x54, 0x54, 0x18, 0x00, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, 0x00, // f
    0x08, 0x14, 0x54, 0x54, 0x3C, 0x00, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, // l
    0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, 0x00, // n
    0x38, 0x44, 0x44, 0x44, 0x38, 0x00, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, 0x00, // p
    0x08, 0x14, 0x14, 0x18, 0x7C, 0x00, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, 0x00, // r
    0x48, 0x54, 0x54, 0x54, 0x20, 0x00, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, 0x00, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, // w
    0x44, 0x28, 0x10, 0x28, 0x44, 0x00, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, // z
    0x00, 0x08, 0x36, 0x41, 0x00, 0x00, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, // |
    0x00, 0x41, 0x36, 0x08, 0x00, 0x00, // }
};

// uint8_t index[93];
/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 *********************************************************************************************************/
extern volatile uint64_t totalMillis;
delay_t delay_barrido, delay_desplazamiento;

/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 *********************************************************************************************************/
volatile estado_barrrido_e estado_barrido = FILA1;

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 *********************************************************************************************************/
static void send_row(uint8_t *display, uint8_t row);
void clockCycle(void);

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 *********************************************************************************************************/
/**
    \fn         void send_row(uint8_t *display, uint8_t row)
    \brief      Función encargada de enviar una fila a la matriz de puntos
    \date       ${date}
    \author     Nicolás Ferragamo
    \param      display [in] array donde se guarda el mensaje a mostrar
    \param      row  [in] indica la fila a elviar
    \return     void
*/
static void send_row(uint8_t *display, uint8_t row)
{
    uint8_t fila = 0;
    for (int8_t i = MAX_COLS - 1; i >= 0; i--)
    {
        ((display[i] >> row) & 0x01) == 1 ? GPIO_WritePin(SI, HIGH) : GPIO_WritePin(SI, LOW);
        clockCycle();
    }
    fila |= (1 << row);
    for (uint8_t i = 0; i < 8; i++)
    {
        ((fila >> i) & 0x01) == 1 ? GPIO_WritePin(SI, HIGH) : GPIO_WritePin(SI, LOW);
        clockCycle();
    }
}

/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 *********************************************************************************************************/
/**
    \fn         void barrido_matriz(uint8_t* display)
    \brief      Función encargada de barrer la matriz de puntos
    \date       ${date}
    \author     Nicolás Ferragamo
    \param      display [in] array donde se guarda el mensaje a mostrar
    \return     void
*/

void barrido_matriz(uint8_t *display)
{
    if (delayRead(&delay_barrido))
    {
        GPIO_WritePin(O_L, HIGH);
        estado_barrido = (estado_barrrido_e)((uint8_t)estado_barrido + 1);
        estado_barrido = (estado_barrrido_e)((uint8_t)estado_barrido % MAX_ROWS);
        send_row(display, (uint8_t)estado_barrido);
        GPIO_WritePin(RCK, HIGH);
        GPIO_WritePin(RCK, LOW);
        GPIO_WritePin(O_L, LOW);
        delayRead(&delay_barrido);
    }
}

/**
    \fn         void desplazar_izq(uint8_t* display, size_t cols)
    \brief      Función encargada de desplazar el mensaje a la izquierda
    \date       ${date}
    \author     Nicolás Ferragamo
    \param      display [in] array donde se guarda el mensaje a mostrar
    \param      cols  [in] cantidad de columnas de la matriz
    \return     void
*/
void desplazar_izq(uint8_t *display, size_t cols)
{
    if (delayRead(&delay_desplazamiento))
    {
        uint8_t aux = display[0];
        for (uint8_t i = 0; i < cols - 1; i++)
        {
            display[i] = display[i + 1];
        }
        display[cols - 1] = aux;
        delayRead(&delay_desplazamiento);
    }
}

/**
    \fn         void inicializar_matriz(void);
    \brief      Función encargada de inicializar la matriz de puntos
    \date       ${date}
    \author     Nicolás Ferragamo
    \return     void
*/
void inicializar_matriz(void)
{
    GPIO_InitPin(RCK, GPIO_OUTPUT);
    GPIO_InitPin(SCK, GPIO_OUTPUT);
    GPIO_InitPin(SI, GPIO_OUTPUT);
    GPIO_InitPin(O_L, GPIO_OUTPUT);

    delayInit(&delay_barrido, 2);
    delayInit(&delay_desplazamiento, 100);
}

/**
    \fn         void enviar_mensaje(uint8_t* display, const char* mensaje)
    \brief      Función encargada escribir el mensae deseado en el array a enviar
    \date       ${date}
    \author     Nicolás Ferragamo
    \return     void
*/
void enviar_mensaje(uint8_t *display, size_t max_disp, const uint8_t *mensaje)
{
    uint8_t indice, i = 0;
    memset(display, 0, max_disp);
    for (uint8_t j = 0; mensaje[j] != '\0' && i < max_disp; j++)
    {
        indice = mensaje[j] - 32;
        for (uint8_t k = 0; k < 6; k++)
        {
            display[i] = tabla[indice * 6 + k];
            i++;
        }
    }
}

void clockCycle()
{
    GPIO_WritePin(SCK, HIGH);
    GPIO_WritePin(SCK, LOW);
}