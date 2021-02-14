/**
 * @file map_solver.h
 * @brief Interfaz publica de las funciones de resolucion de laberintos.
 * @author Javier Mateos
 *
 * @date 12/02/2020
 */

#ifndef MAP_SOLVER_H
#define MAP_SOLVER_H

#include "point.h"
#include "map.h"
#include "types.h"

/**
 * @brief Busca si un laberinto tiene solucion.
 * @param map_file Fichero en el que se encuentra el laberinto.
 * @param strat Estrategia a seguir para resolver el laberinto.
 * @return El numero de pasos necesarios para resolver el laberinto o un numero
 * negativo si no tiene solucion o se produce algun error.
 */
Bool mapsolver_stack(FILE* map_file, const Move strat[NUM_MOVEMENTS]);
Bool mapsolver_queue(FILE* map_file, const Move strat[NUM_MOVEMENTS]);
Bool mapsolver_recursive(FILE* map_file, const Move strat[NUM_MOVEMENTS]);

#endif /* MAP_SOLVER_H */
