/**
 * @file map.h
 * @brief Interfaz publica del TAD Map.
 * @author Javier Mateos Ines Martin
 *
 * @date 23/01/2020
 */

#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#include "point.h"
#include "types.h"

#define MAX_POINT 4096 /**< Numero maximo de puntos de un mapa */

/**
 * Estructura que define un mapa de un laberinto.
 */
typedef struct _Map Map;

/**
 * @enum Move
 * @brief Movimientos posibles en un mapa.
 */
typedef enum {
    RIGHT,
    UP,
    LEFT,
    DOWN,
    STAY /**< No movimiento **/
} Move;

/**
 * @brief Inicializa un mapa.
 *
 * @return Devuelve el mapa inicializado o NULL si se produce algun error.
 */
Map* map_ini();

/**
 * @brief Libera un mapa.
 * @param pm Mapa que se libera.
 */
void map_free(Map* pm);

/**
 * @brief Obtiene el numero de filas de un mapa.
 * @param pm Mapa del que se obtiene las filas.
 * @return Devuelve el numero de filas o -1 si se produce algun error.
 */
int map_getNrows(const Map* pm);

/**
 * @brief Obtiene el número de columnas de un mapa.
 * @param pm Mapa del que se obtiene las columnas.
 * @return Devuelve el numero de columnas o -1 si se produce algun error.
 */
int map_getNcols(const Map* pm);

/**
 * @brief Obtiene el punto de entrada del mapa.
 * @param pm Mapa del que se obtiene la entrada.
 * @return Devuelve el punto o NULL si se produce algun error o no existe
 * dicho punto en el mapa.
 */
Point* map_getInput(const Map* pm);

/**
 * @brief Obtiene el punto de salida del mapa.
 * @param pm Mapa del que se obtiene la salida.
 * @return Devuelve el punto o NULL si se produce algun error o no existe
 * dicho punto en el mapa.
 */
Point* map_getOutput(const Map* pm);

/**
 * @brief Permite obtener un punto vecino de otro dado un movimiento.
 *
 * Se considera vecino en el mismo eje vertical u horizontal con una
 * posicion de diferencia en uno de los valores de sus coordenadas.
 *
 * @param pm Mapa en el que se encuentran los puntos.
 * @param pp Punto inicial del movimiento.
 * @param mov Movimiento realizado.
 * @return Devuelve el punto tras el movimiento o NULL si se produce algun
 * error o no existe vecino para dicho movimiento.
 */
Point* map_getNeightbarPoint(const Map* pm, const Point* pp, const Move mov);

/**
 * @brief Establece el tamanio de un mapa.
 *
 * Los mapas tendran como minimo una columna y una fila. Ademas,
 * el numero de puntos no podra superar el maximo establecido.
 *
 * @param pm Mapa cuyo tamanio se establece.
 * @param nrow Numero de filas.
 * @param ncol Numero de columnas.
 * @return OK si todo sale bien o ERR si se produce algun eror.
 */
Status map_setSize(Map* pm, int nrow, int ncol);

/**
 * @brief Aniade un punto a un mapa.
 *
 * Si el punto ya se encuentra en el mapa éste es modificado.
 *
 * @param pm Mapa al que se aniade el punto.
 * @param pp Punto aniadido al mapa.
 * @return OK si todo sale bien o ERR si se produce algun error.
 */
Status map_setPoint(Map* pm, const Point* pp);

/**
 * @brief Permite imprimir el estado de un mapa en ASCII.
 * @param pf Fichero en el que se imprime el mapa.
 * @param pm Mapa impreso.
 * @return Numero de caracteres impreso con exito en el fichero
 * o un numero negativo si ocurre algun error.
 */
int map_print(FILE* pf, const Map* pm);

#endif /* MAP_H */
