/**
 * @file stack_element.h
 * @brief Interfaz publica del TAD Stack.
 * @author Javier Mateos
 *
 * @date 05/02/2021
 */

#ifndef STACK_ELEMENT_H
#define STACK_ELEMENT_H

#include "functions.h"
#include "types.h"

/** 
 * Maximo numero de elementos que se puede almacenar en la pila
 */
#define MAXSTACK 4096 

/**
 * Estructura que representa una pila FIFO.
 */
typedef struct _Stack Stack;

/**
 * @brief Inicializa la pila reservando memoria.
 * @param f1 Funcion para liberar los elementos de la pila.
 * @param f2 Funcion para copiar los elementos de la pila.
 * @param f3 Funcion para imprimir los elementos de la pila.
 * @return La pila inicializada o NULL si se produce un error.
 */
Stack* stack_ini(free_element_function_type f1,
                 copy_element_function_type f2,
                 print_element_function_type f3);

/**
 * @brief Libera la memoria reservada de la pila.
 * @param ps La pila que se libera.
 */
void stack_free(Stack* ps);

/**
 * @brief Comprueba si la pila esta vacia.
 * @param ps Pila que se comprueba.
 * @return TRUE si esta vacia o FALSE si no lo esta.
 */
Bool stack_isEmpty(const Stack* ps);

/**
 * @brief Comprueba si la pila esta llena.
 * @param ps Pila que se comprueba.
 * @return TRUE si esta llena o FALSE si no lo esta.
 */
Bool stack_isFull(const Stack* ps);

/**
 * @brief Inserta un elemento en la pila.
 *
 * El elemento insertado es una copia.
 *
 * @param ps Pila en la que se inserta.
 * param e Elemento insertado en la pila.
 * @return OK si se inserta o ERR si se produce algun error.
 */
Status stack_push(Stack* ps, const void* e);

/**
 * @brief Extra un elemento en la pila.
 *
 * La pila queda modificada tras la operacion. Ademas, el elemento
 * devuelto tiene memoria reservada.
 *
 * @param ps Pila de la que se extrae.
 * @return El elemento extraido o NULL si se produce un error.
 */
void* stack_pop(Stack* ps);

/**
 * @brief Obtiene el elemento del top de la pila.
 *
 * No modifica la pila. El elemento devuelto es una copia con memoria
 * reservada.
 *
 * @param ps Pila de la que se copia el top.
 * @return Elemento del top de la pila o NULL si se produce algun error.
 */
void* stack_top(Stack* ps);

/**
 * @brief Imprime toda la pila a un fichero.
 *
 * El elemento de la cima de la pila se coloca al principio de la impresion,
 * situando un elemento por linea.
 *
 * @param pf Archivo en el que se imprime.
 * @param ps Pila impresa.
 * @return Numero de elementos de la pila escritos o menor que 0 si se produce 
 * un error.
 */
int stack_print(FILE* pf, const Stack* ps);

#endif /* STACK_ELEMENT_H */
