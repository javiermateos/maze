/**
 * @file functions.c
 * @brief Implementacion de las funciones envoltorio.
 * @author Javier Mateos
 *
 * @date 06/02/2021
 */

#include <stdlib.h>

#include <functions.h>
#include <point.h>

void destroy_intp_function(void* e)
{
    free((int*)e);
}

void* copy_intp_function(const void* e)
{
    int* e_copy;

    if (!e) {
        return NULL;
    }

    e_copy = (int*)malloc(sizeof(int));

    *(e_copy) = *((int*)e);

    return e_copy;
}

int print_intp_function(FILE* pf, const void* e)
{
    if (!pf || !e) {
        return -1;
    }

    return fprintf(pf, "[%d]\n", *((int*)e));
}

int cmp_intp_function(const void* e1, const void* e2)
{

    if (!e1 || !e2) {
        return 2;
    }

    if (*((int*)e1) == *((int*)e2)) {
        return 0;
    } else if (*((int*)e1) < *((int*)e2)) {
        return -1;
    } else if (*((int*)e1) > *((int*)e2)) {
        return 1;
    }

    return 2;
}

void destroy_point_function(void* e)
{
    point_free((Point*)e);
}

void* copy_point_function(const void* e)
{
    return point_copy((Point*)e);
}

int print_point_function(FILE* pf, const void* e)
{
    return point_print(pf, (Point*)e);
}
