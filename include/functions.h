/**
 * @file functions.h
 * @brief Funciones envoltorio de los datos que se introducen en la pila.
 * @author Javier Mateos
 *
 * @date 06/02/2021
 */

#include <stdio.h>

/**
 * @{
 * @ brief Funciones que permiten almacenar enteros en una pila.
 */
void destroy_intp_function(void* e);

void* copy_intp_function(const void* e);

int print_intp_function(FILE* pf, const void* e);
/**@}*/

/**
 * @{
 * @brief Funciones que permiten almacenar puntos en una pila.
 */
void destroy_point_function(void* e);

void* copy_point_function(const void* e);

int print_point_function(FILE* f, const void* e);
/**@}*/
