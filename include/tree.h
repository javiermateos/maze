/**
 * @file tree.h
 * @brief Interfaz publica del TAD Tree.
 * @author Javier Mateos
 *
 * @date 13/02/2021
 */

#ifndef TREE_H
#define TREE_H

#include "types.h"
#include "functions.h"

typedef struct _Tree Tree;

/**
 * @brief Inicializa el arbol reservando memoria para este.
 * @param f1 Funcion que libera la memoria de los elementos del arbol.
 * @param f2 Funcion que copia un elemento del arbol.
 * @param f3 Funcion que imprime un elemento del arbol.
 * @return El arbol inicializado o NULL si se produce algun error.
 */
Tree* tree_ini(free_element_function_type f1,
               copy_element_function_type f2,
               print_element_function_type f3,
               cmp_element_function_type f4);

/**
 * @brief Libera la memoria reservada del arbol.
 * @param pa Arbol del que se libera la memoria.
 */
void tree_free(Tree* pa);

/**
 * @brief Inserta en el arbol una copia del elemento.
 * @param pa Arbol en el que se inserta.
 * @param e Elemento que se inserta.
 * @return OK si se inserta y ERR si se produce algun error.
 */
Status tree_insert(Tree* pa, const void* e);

/**
 * @brief Busca un elemento en un arbol.
 * @param pa Arbol en el que se busca el elemento.
 * @param e Elemento buscado.
 * @return true si se encuentra o false si no se encuentra o se produce
 * algun error.
 */
Bool tree_find(Tree* pa, const void* e);

/**
 * @brief Comprueba si un arbol esta vacio.
 * @param pa Arbol que se comprueba.
 * @return True si esta vacio o False si no lo esta.
 */
Bool tree_isEmpty(const Tree* pa);

/**
 * @brief Obtiene la profundidad de un arbol.
 *
 * Un arbol vacio tiene profundidad -1.
 *
 * @param pa Arbol del que se devuelve la profundidad.
 * @return La profundidad del arbol o -2 si se produce algun error.
 */
int tree_depth(const Tree* pa);

/**
 * @brief Obtiene el numero de nodos de un arbol.
 *
 * Un arbol vacio tiene 0 nodos.
 *
 * @param pa Arbol del que se obtiene los nodos.
 * @return Numero de nodos o -1 si se produce algun error.
 */
int tree_numNodes(const Tree* pa);

/**
 * @brief Imprime el recorrido de un arbol en orden previo.
 * @param pf Archivo en el que se imprime.
 * @param pa Arbol que se imprime.
 * @return OK si se imprime correctamente o ERR si se produce algun error.
 */
Status tree_preOrder(FILE* pf, const Tree* pa);

/**
 * @brief Imprime el recorrido de un arbol en orden medio.
 * @param pf Archivo en el que se imprime.
 * @param pa Arbol que se imprime.
 * @return OK si se imprime correctamente o ERR si se produce algun error.
 */
Status tree_inOrder(FILE* pf, const Tree* pa);

/**
 * @brief Imprime el recorrido de un arbol en orden posterior.
 * @param pf Archivo en el que se imprime.
 * @param pa Arbol que se imprime
 * @return OK si se imprime correctamente o ERR si se produce algun error.
 */
Status tree_postOrder(FILE* pf, const Tree* pa);

#endif /* TREE_H */
