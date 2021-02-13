/**
 * @file queue.h
 * @brief Interfaz publica del TAD Queue.
 * @author Javier Mateos
 *
 * @date 09/02/2021
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#include "functions.h"
#include "types.h"

#define MAXQUEUE 100

typedef struct _Queue Queue;

/**
 * @brief Inicializa una cola.
 * @param f1 Funcion que libera la memoria de los elementos de la cola.
 * @param f2 Funcion que copia un elemento de la cola.
 * @param f3 Funcion que imprime un elemento de la cola.
 * @return La cola inicializada o NULL si se produce algun error.
 */
Queue* queue_ini(free_element_function_type f1,
                 copy_element_function_type f2,
                 print_element_function_type f3);

/**
 * @brief Libera la memoria reservada de una cola.
 * @param pq Cola que se libera.
 */
void queue_free(Queue* pq);

/**
 * @brief Permite obtener si una cola esta vacia.
 * @param pq Cola que se comprueba.
 * @return TRUE si esta vacia o FALSE si no lo está u ocurre algun error.
 */
Bool queue_isEmpty(const Queue* pq);

/**
 * @brief Permite obtener si una cola esta llena.
 * @param pq Cola que se comprueba.
 * @return TRUE si esta llena o FALSE si no lo esta u ocurre algun error.
 */
Bool queue_isFull(const Queue* pq);

/**
 * @brief Inserta un elemento en la cola realizando para ello una copia
 * del mismo.
 * @param pq Cola en la que se inserta.
 * @param e Elemento insertado.
 * @return OK si se inserta el elemento o ERR si ocurre algun error.
 */
Status queue_insert(Queue* pq, const void* e);

/**
 * @brief Extrae un elemento de la cola que tiene memoria reservada.
 * @param q Cola de la que se extrae el elemento.
 * @return El elemento extraido o NULL si se produce algun error.
 */
void* queue_extract(Queue* pq);

/**
 * @brief Obtiene el numero de elementos de una cola.
 * @param pq Cola de la que se extra el numero de elementos.
 * @return Numero de elementos de la cola o -1 si se produce algun error.
 */
int queue_size(const Queue* pq);

/**
 * @brief Imprime toda la cola con un elemento en cada linea.
 * @param pf Archivo en el que se imprime la cola.
 * @param pq Cola que se imprime.
 * @return Numero de elementos de la cola escritos o -1 si se produce algun
 * error.
 */
int queue_print(FILE* pf, const Queue* pq);

#endif /* QUEUE_H */
