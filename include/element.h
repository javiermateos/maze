/**
 * @file element.h
 * @brief Interfaz publica del TAD Element.
 * @author Javier Mateos
 *
 * @date 05/02/2020
 */

#include <types.h>

/**
 * Estructura que representa un elemento de una pila
 */
typedef struct _Element Element;

/**
 * @brief Inicializa un elemento de pila.
 * @return Elemento inicializado o NULL en caso de error.
 */
Element* element_ini();

/**
 * @brief Libera la memoria reservada de un elemento.
 */
void element_free(Element* e);

/**
 * @brief Modifica los datos asociados a un elemento.
 *
 * El elemento almacenado es una copia del parametro. Ademas,
 * si el elemento tiene informacion almacenada la sobreescribe.
 *
 * @param e Elemento que se modifica.
 * @param info Informacion que se guarda en el elemento.
 * @return OK si se guarda o ERR si se produce algun error.
 */
Status element_setInfo(Element* e, const void* info);

/**
 * @brief Obtiene el contenido almacenado en un elemento.
 *
 * El contenido devuelto es una copia de la informacion.
 *
 * @param e Elemento del que se obtiene el contenido.
 * @return El contenido del elemento o NULL si se produce un error.
 */
void* element_getInfo(const Element* e);

/**
 * @brief Copia un elemento.
 *
 * Esta funcion reserva memoria en el elemento copiado. Ademas,
 * si el elemento copiado no tiene informacion devolvera error.
 *
 * @param e Elemento que se copia.
 * @return Elemento copiado o NULL si se produce un error.
 */
Element* element_copy(const Element* e);

/**
 * @brief Compara dos elementos.
 * @param e1 Primer elemento de la comparacion.
 * @param e2 Segundo elemento de la comparacion.
 * @return TRUE si son iguales o FALSE si no lo son.
 */
Bool element_equals(const Element* e1, const Element* e2);

/**
 * @brief Imprime el elemento en un fichero.
 * @param pf Fichero en el que se imprime el elemento.
 * @param e Elemento que se imprime.
 * @return Numero de caracteres impresos o negativo si se produce un error.
 */
int element_print(FILE* pf, const Element* e);
