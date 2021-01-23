/**
 * @file point.h
 * @brief Interfaz publica del TAD Point.
 * @author Javier Mateos
 *
 * @date 23/01/2020
 */

#ifndef POINT_H
#define POINT_H

#include <stdio.h>

#include "types.h"

/*
 * Constantes públicas que definen los tipos de puntos que se permiten en
 * un mapa.
 */
#define ERRCHAR 'E' /**< TODO **/
#define INPUT 'i' /**< TODO **/
#define VISITED 'v' /**< TODO **/
#define OUTPUT 'o' /**< TODO **/
#define BARRIER '+' /**< TODO **/
#define SPACE ' ' /**< TODO **/

typedef struct _Point Point;

/**
 * @brief Inicializa un punto.
 * @param x Coordenada del eje de abcisas.
 * @param y Coordenada del eje de coordenadas.
 * @param s Simbolo asociado al punto.
 * @return El punto inicializado o NULL si se ha producido un error.
 */
Point *point_ini(int x, int y, char s);

/**
 * @brief Libera un punto.
 * @param pp Punto liberado.
 */
void point_free(Point *pp);

/**
 * @brief Obtiene la coordenada del eje de abcisas (Eje X).
 * @param pp Punto del que se obtiene la coordenada.
 * @return Coordenada x o -1 si se produce algun error.
 */
int point_getCoordinateX(const Point *pp);

/**
 * @brief Obtiene la coordenada del eje de coordenadas (Eje Y).
 * @param pp Punto del que se obtiene la coordenada.
 * @return Coordenada y o -1 si se produce algun error.
 */
int point_getCoordinateY(const Point *pp);

/**
 * @brief Obtiene el simbolo de un punto.
 * @param pp Punto del que se obtiene el simbolo.
 * @return Simbolo del punto o ERRCHAR si se produce algun error.
 */
char point_getSymbol(const Point *pp);

/* Funciones derivadas que indican el tipo de punto que tenemos */
/**
 * @defgroup Tipo de punto
 * 
 * Funciones que indican el tipo de punto que tenemos.
 */
Bool point_isInput(Point *pp);
Bool point_isOutput(Point *pp);
Bool point_isBarrier(Point *pp);
Bool point_isSpace(Point *pp);

/**
 * @brief Modifica la coordenada X de un punto.
 * @param pp Punto modificado.
 * @param x Nueva coordenada del eje X.
 * @return OK o ERR si se produce algun error.
 */
Status point_setCoordinateX(Point *pp, const int x);

/**
 * @brief Modifica la coordenada Y de un punto.
 * @param pp Punto modificado.
 * @param y Nueva coordenada del eje Y.
 * @return OK o ERR si se produce algun error.
 */
Status point_setCoordinateY(Point *pp, const int y);

/**
 * @brief Modifica el simbolo de un punto.
 * @param pp Punto modificado.
 * @param s Nuevo simbolo del punto.
 * @return OK o ERR si se produce en algun error.
 */
Status point_setSymbol(Point *pp, const char s);

/**
 * @brief Permite saber si dos puntos son iguales.
 *
 * La comparacion se hace por sus atributos, no por referencia.
 *
 * @param pp1 Uno de los puntos comparados.
 * @param pp2 Otro de los puntos comparados.
 * @return TRUE si son iguales o FALSE si no lo son.
 */
Bool point_equals(const Point *pp1, const Point *pp2);

/* Copia los datos de un punto a otro devolviendo el punto copiado (incluyendo
 * la reserva de la memoria necesaria)
 * si todo ha ido bien, o NULL en otro caso */
/**
 * @brief Copia un punto.
 * 
 * El punto resultante contiene los mismos valores del punto copiado en
 * los atributos del punto.
 *
 * @param pp Punto que se copia.
 * @return Un nuevo punto o NULL si se produce algun error.
 */
Point *point_copy(const Point *pp);

/**
 * @brief Permite imprimir el estado de un punto.
 *
 * Formato: [(X,Y): symbol].
 *
 * @param pf Fichero en el que se imprime el punto.
 * @return Numero de caracteres impresos con exito en el fichero.
 */
int point_print(FILE *pf, const Point *pp);

#endif /* POINT_H */