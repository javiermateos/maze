/*
 * @file: utils.h
 * @brief: Interfaz publica del modulo Utils
 * @author: Javier Mateos
 *
 * @date 03/02/2021
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "map.h"
#include "types.h"

#define MAX 100 /**< Numero maximo de columnas del laberinto */

/**
 * @brief Carga el mapa leido de un fichero de texto.
 * @param pf Archivo en el que se encuentra el mapa.
 * @param pl Mapa en el que se carga.
 * @return OK si todo sale bien o ERR si se produce algun error.
 */
Status map_read(FILE* pf, Map* pl);

#endif
