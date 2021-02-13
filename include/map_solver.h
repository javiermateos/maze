/**
 * @file map_solver.h
 * @brief Interfaz publica de las funciones de resolucion de laberintos.
 * @author Javier Mateos
 *
 * @date 12/02/2020
 */

#ifndef MAP_H
#define MAP_H

#include <stdio.h>

/**
 * @brief Busca si un laberinto tiene solucion.
 * @param map_file Fichero en el que se encuentra el laberinto.
 * @param strat Estrategia a seguir para resolver el laberinto.
 * @return El numero de pasos necesarios para resolver el laberinto o un numero
 * negativo si no tiene solucion o se produce algun error.
 */
int mapsolver_stack(const char* map_file, const Move strat[4]);

int mapsolver_queue(const char* map_file, const Move strat[4]);

void mapsolver_run(const char* map_file, const Move strat[][4], const int num_strategies);

#endif /* MAP_H */
