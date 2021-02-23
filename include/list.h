/**
 * @file list.h
 * @brief Interfaz publica del TAD List, que define una lista enlazada.
 * @author Javier Mateos
 *
 * @date 09/02/2021
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "functions.h"
#include "types.h"

typedef struct _List List;

/**
 * @brief Inicializa una lista y todos sus elementos.
 * @param f1 Funcion que libera la memoria de los elementos de la lista.
 * @param f2 Funcion que copia un elemento de la lista.
 * @param f3 Funcion que imprime un elemento de la lista.
 * @param f4 Funcion que compara dos elementos de una lista.
 * return La lista inicializada o NULL si se produce algun error.
 */
List* list_ini(free_element_function_type f1,
               copy_element_function_type f2,
               print_element_function_type f3,
               cmp_element_function_type f4);

/**
 * @brief Libera la memoria reservada para una lista.
 * @param pl Lista que se libera.
 */
void list_free(List* pl);

/**
 * @brief Inserta un elemento en la lista al principio de la misma.
 *
 * Esta funcion realiza una copia del elemento.
 *
 * @param pl Lista en la que se inserta el elemento.
 * @param e Elemento insertado en la lista.
 * @return OK si se se inserta o ERR si se produce algun error.
 */
Status list_insertFirst(List* pl, const void* e);

/**
 * @brief Inserta un elemento en la lista al final de la misma.
 *
 * Esta funcion realiza una copia del elemento.
 *
 * @param pl Lista en la que se inserta el elemento.
 * @param e Elemento insertado en la lista.
 * @return OK si se inserta o ERR si se produce algun error.
 */
Status list_insertLast(List* pl, const void* e);

/**
 * @brief Inserta un element en lista colocandolo en orden.
 *
 * Esta funcion realiza una copia del elemento.
 *
 * @param pl Lista en la que se inserta el elemento.
 * @param e Elemento insertado en la lista.
 * @return OK si se inserta o ERR si se produce algun error.
 */
Status list_insertInOrder(List* pl, const void* e);

/**
 * @brief Extrae el primer elemento de la lista.
 *
 * Esta funcion realiza una copia del elemento.
 *
 * @param pl Lista de la que se extrae.
 * @return El elemento de la lista o NULL si se produce algun error.
 */
void* list_extractFirst(List* pl);

/**
 * @brief Extrae el ultimo elemento de la lista.
 *
 * Esta funcion realiza una copia del elemento.
 *
 * @param pl Lista de la que se extrae.
 * @return El elemento de la lista o NULL si se produce algun error.
 */
void* list_extractLast(List* pl);

/**
 * @brief Comprueba si una lista esta vacia.
 * @param pl Lista que se comprueba.
 * @return TRUE si esta vacia o FALSE si no lo esta u ocurre algun error.
 */
Bool list_isEmpty(const List* pl);

/**
 * @brief Obtiene el elemento i-esimo almacenado en la lista.
 * @param pl Lista de la que se optiene el elemento.
 * @param i posicion del elemento en la lista.
 * @return El elemento o NULL si se produce un error.
 */
const void* list_get(const List* pl, int i);

/**
 * @brief Obtiene el numero de elemento de una lista.
 * @param pl Lista de la que se obtiene el numero de elementos.
 * @return El numero de elementos o -1 si se produce algun error.
 */
int list_size(const List* pl);

/**
 * @brief Imprime una lista con cada elemento en una nueva linea en
 * un fichero.
 * @param pf Fichero en el que se imprime la lista.
 * @param pl Lista que se imprime.
 * @return Numero de elementos impresos de la lista o -1 si se produce
 * algun error.
 */
int list_print(FILE* pf, const List* pl);

#endif /* LIST_H */
