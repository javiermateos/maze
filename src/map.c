/**
 * @file map.c
 * @brief Implementacion del TAD Map.
 * @author Javier Mateos
 *
 * @date 23/01/2020
 */
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"

struct _Map {
    int nrow;
    int ncol;
    Point* points[MAX_POINT];
};

Map* map_ini() {
    int i;
    Map* pm = NULL;

    pm = (Map*)malloc(sizeof(Map));
    if (!pm) {
        return NULL;
    }

    for (i = 0; i < MAX_POINT; i++) {
        pm->points[i] = NULL;
    }

    return pm;
}

void map_free(Map* pm)
{
    int i;

    if (!pm) {
        return;
    }

    for (i = 0; i < MAX_POINT; i++) {
        if (pm->points[i] != NULL) {
            point_free(pm->points[i]);
        }
    }

    free(pm);
}

int map_getNrows(const Map* pm)
{
    if (!pm) {
        return -1;
    }

    return pm->nrow;
}

int map_getNcols(const Map* pm)
{
    if (!pm) {
        return -1;
    }

    return pm->ncol;
}

Point* map_getInput(const Map* pm)
{
    int i;
    Point* input = NULL;

    if (!pm) {
        return NULL;
    }

    for (i = 0; i < MAX_POINT && pm->points[i] != NULL; i++) {
        if (point_getSymbol(pm->points[i]) == INPUT) {
            input = point_copy(pm->points[i]);
        }
    }

    return input;
}

Point* map_getOutput(const Map* pm)
{
    int i;
    Point* output = NULL;

    if (!pm) {
        return NULL;
    }

    for (i = 0; i < MAX_POINT && pm->points[i] != NULL; i++) {
        if (point_getSymbol(pm->points[i]) == OUTPUT) {
            output = point_copy(pm->points[i]);
        }
    }

    return output;
}

Point* map_getNeightbarPoint(const Map* pm, const Point* pp, const Move mov)
{
    int i;
    int x, y;
    Point* pp_neightbar = NULL;

    if (!pm || !pp) {
        return NULL;
    }

    switch (mov) {
        case RIGHT:
            x = point_getCoordinateX(pp) + 1;
            y = point_getCoordinateY(pp);
            break;
        case UP:
            x = point_getCoordinateX(pp);
            y = point_getCoordinateY(pp) + 1;
            break;
        case LEFT:
            x = point_getCoordinateX(pp) - 1;
            y = point_getCoordinateY(pp);
            break;
        case DOWN:
            x = point_getCoordinateX(pp);
            y = point_getCoordinateY(pp) - 1;
            break;
        case STAY:
            x = point_getCoordinateX(pp);
            y = point_getCoordinateY(pp);
            break;
        default:
            /* El movimiento no existe */
            return NULL;
    }

    for (i = 0; i < MAX_POINT && pm->points[i] != NULL; i++) {
        if (point_getCoordinateX(pm->points[i]) == x &&
            point_getCoordinateY(pm->points[i]) == y) {
            pp_neightbar = point_copy(pm->points[i]);
        }
    }

    return pp_neightbar;
}

Status map_setSize(Map* pm, int nrow, int ncol)
{
    if (!pm || nrow <= 0 || ncol <= 0 || ((ncol * nrow) >= MAX_POINT)) {
        return ERR;
    }

    pm->nrow = nrow;
    pm->ncol = ncol;

    return OK;
}

Status map_setPoint(Map* pm, const Point* pp)
{
    char s;
    int ncols, indice, x, y;
    Point* pp_aux = NULL;

    if (!pm || !pp) {
        return ERR;
    }

    ncols = map_getNcols(pm);
    x = point_getCoordinateX(pp);
    y = point_getCoordinateY(pp);

    indice = y * ncols + x;
    if (indice >= MAX_POINT) {
        return ERR;
    }

    /** Comprobamos si existe el punto **/
    if (pm->points[indice]) {
        s = point_getSymbol(pp);
        point_setSymbol(pm->points[indice], s);
    } else {
        pp_aux = point_copy(pp);
        if (!pp_aux) {
            return ERR;
        }
        pm->points[indice] = pp_aux;
    }

    return OK;
}

int map_print(FILE* pf, const Map* pm)
{
    int i, j;
    int index;
    int counter = 0;
    char c;

    if (!pf || !pm) {
        return -1;
    }

    for (i = 0; i < pm->nrow; i++) {
        for (j = 0; j < pm->ncol; j++) {
            index  = (pm->ncol) * i + j;
            c = point_getSymbol(pm->points[index]);
            counter += fprintf(pf, "%c", c);
        }
        counter += fprintf(pf, "\n");
    }
    return counter;
}
