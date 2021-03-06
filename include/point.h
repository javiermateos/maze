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
 * Constantes públicas que definen la representacion de puntos que se permiten
 * en un mapa.
 */
#define ERRCHAR 'E' /**< Error en el punto */
#define INPUT 'i'   /**< Punto de entrada del laberinto */
#define VISITED 'V' /**< Punto que ha sido visitado */
#define VISITING 'v' /**< Punto que esta siendo visitado */
#define OUTPUT 'o'  /**< Punto de salida del laberinto */
#define BARRIER '+' /**< Punto no transitable */
#define SPACE ' '   /**< Punto transitable */
#define PATH '.'    /**< Punto perteneciente al camino optimo */

/**
 * Estructura que representa un punto en el mapa.
 */
typedef struct _Point Point;

/**
 * @brief Inicializa un punto.
 * @param x Coordenada del eje de abcisas.
 * @param y Coordenada del eje de coordenadas.
 * @param s Simbolo asociado al punto.
 * @return El punto inicializado o NULL si se ha producido un error.
 */
Point* point_ini(int x, int y, char s);
/**
 * @brief Libera un punto.
 * @param pp Punto liberado.
 */
void point_free(Point* pp);

/**
 * @brief Obtiene la coordenada del eje de abcisas (Eje X).
 * @param pp Punto del que se obtiene la coordenada.
 * @return Coordenada x o -1 si se produce algun error.
 */
int point_getCoordinateX(const Point* pp);

/**
 * @brief Obtiene la coordenada del eje de coordenadas (Eje Y).
 * @param pp Punto del que se obtiene la coordenada.
 * @return Coordenada y o -1 si se produce algun error.
 */
int point_getCoordinateY(const Point* pp);

/**
 * @brief Obtiene el simbolo de un punto.
 * @param pp Punto del que se obtiene el simbolo.
 * @return Simbolo del punto o ERRCHAR si se produce algun error.
 */
char point_getSymbol(const Point* pp);

/**
 * @brief Obtiene el punto desde el que se accedio a otro punto.
 * @param pp Punto al que se accedio.
 * @return El punto padre o NULL si no tiene padre.
 */
Point* point_getParent(const Point* pp);

/**
 * @defgroup Tipo de punto
 *
 * Funciones que indican el tipo de punto que tenemos.
 */
Bool point_isInput(Point* pp);
Bool point_isOutput(Point* pp);
Bool point_isBarrier(Point* pp);
Bool point_isSpace(Point* pp);

/**
 * @brief Modifica la coordenada X de un punto.
 * @param pp Punto modificado.
 * @param x Nueva coordenada del eje X.
 * @return OK o ERR si se produce algun error.
 */
Status point_setCoordinateX(Point* pp, const int x);

/**
 * @brief Modifica la coordenada Y de un punto.
 * @param pp Punto modificado.
 * @param y Nueva coordenada del eje Y.
 * @return OK o ERR si se produce algun error.
 */
Status point_setCoordinateY(Point* pp, const int y);

/**
 * @brief Modifica el simbolo de un punto.
 * @param pp Punto modificado.
 * @param s Nuevo simbolo del punto.
 * @return OK o ERR si se produce en algun error.
 */
Status point_setSymbol(Point* pp, const char s);

/**
 * @brief Modifica el punto desde el que se accedio a un punto.
 * @param pp_child Punto al que se accede.
 * @param pp_parent Punto desde el que se accede.
 * return OK si se establece el punto o ERR si se produce algun error.
 */
Status point_setParent(Point* pp_child, Point* pp_parent);

/**
 * @brief Permite saber si dos puntos son iguales.
 *
 * La comparacion se hace por sus atributos, no por referencia.
 *
 * @param pp1 Uno de los puntos comparados.
 * @param pp2 Otro de los puntos comparados.
 * @return TRUE si son iguales o FALSE si no lo son.
 */
Bool point_equals(const Point* pp1, const Point* pp2);

/**
 * @brief Copia un punto.
 *
 * El punto resultante contiene los mismos valores del punto copiado en
 * los atributos del punto. Esta funcion reserva memoria.
 *
 * @param pp Punto que se copia.
 * @return Un nuevo punto o NULL si se produce algun error.
 */
Point* point_copy(const Point* pp);

/**
 * @brief Permite imprimir el estado de un punto.
 *
 * Formato: [(X,Y): symbol].
 *
 * @param pf Fichero en el que se imprime el punto.
 * @return Numero de caracteres impresos con exito en el fichero
 * o un numero negativo si ocurre algun error.
 */
int point_print(FILE* pf, const Point* pp);

#endif /* POINT_H */
