/**
 * @file element.c
 * @brief Implementacion del TAD Element con enteros.
 * @author Javier Mateos
 *
 * @date 05/02/2020
 */

#include <stdlib.h>

#include "element.h"

/**
 * Implementacion de un elemento que almacena como informacion un entero.
 */
struct _Element {
    int* info;
};

Element* element_ini()
{
    Element* e = NULL;

    e = (Element*)malloc(sizeof(Element));
    if (!e) {
        return NULL;
    }

    e->info = NULL;

    return e;
}

void element_free(Element* e)
{
    if (!e) {
        return;
    }

    if (e->info) {
        free(e->info);
        e->info = NULL;
    }

    free(e);
}

Status element_setInfo(Element* e, const void* info)
{
    if (!e || !info) {
        return ERR;
    }

    if (e->info) {
        free(e->info);
        e->info = NULL;
    }

    e->info = (int*)malloc(sizeof(int));
    if (!e->info) {
        return ERR;
    }

    *(e->info) = *(int*)info;

    return OK;
}

void* element_getInfo(const Element* e)
{
    int* info = NULL;

    if (!e || !e->info) {
        return NULL;
    }

    info = (int*)malloc(sizeof(int));
    if (!info) {
        return NULL;
    }

    *info = *(e->info);

    return info;
}

Element* element_copy(const Element* e)
{
    Element* e_copy = NULL;

    if (!e) {
        return NULL;
    }

    e_copy = element_ini();
    if (!e_copy) {
        return NULL;
    }

    if (element_setInfo(e_copy, e->info) == ERR) {
        return NULL;
    }

    return e_copy;
}

Bool element_equals(const Element* e1, const Element* e2)
{
    int* e1_info = NULL;
    int* e2_info = NULL;

    if (!e1 || !e2) {
        return FALSE;
    }
    
    e1_info = (int*)element_getInfo(e1);
    e2_info = (int*)element_getInfo(e2);

    /* Comparamos el contenido de la informacion */
    if (*e1_info != *e2_info) {
        return FALSE;
    }

    return TRUE;
}

int element_print(FILE* pf, const Element* e)
{
    if(!pf || !e) {
        return -1;
    }

    return fprintf(pf, "%d", *(int*)(e->info));
}
