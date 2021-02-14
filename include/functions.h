/**
 * @file functions.h
 * @brief Funciones envoltorio de los datos que se introducen en la pila.
 * @author Javier Mateos
 *
 * @date 06/02/2021
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

typedef void (*free_element_function_type)(void*);
typedef void (*(*copy_element_function_type)(const void*));
typedef int (*print_element_function_type)(FILE*, const void*);
typedef int (*cmp_element_function_type)(const void*, const void*);

/**
 * @{
 * @ brief Funciones que permiten almacenar enteros en una pila.
 */
void destroy_intp_function(void* e);

void* copy_intp_function(const void* e);

int print_intp_function(FILE* pf, const void* e);

int cmp_intp_function(const void* e1, const void* e2);
/**@}*/

/**
 * @{
 * @brief Funciones que permiten almacenar puntos en una pila.
 */
void destroy_point_function(void* e);

void* copy_point_function(const void* e);

int print_point_function(FILE* f, const void* e);

#endif /* FUNCTIONS_H */
