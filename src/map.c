#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"
#include "types.h"

#define NCOORD 2 /**< Numero de coordenadas de los puntos del mapa */

struct _Map {
    int nrow;
    int ncol;
    int npuntos;
    Point* input; /** TODO: Pensar que hacer con input y output **/
    Point* output;
    Point* points[MAX_POINT];
};

Map* map_init()
{
    int i;
    Map* pm = NULL;

    pm = (Map*)malloc(sizeof(Map));
    if (!pm) {
        return NULL;
    }

    for (i = 0; i < MAX_POINT; i++) {
        pm->points[i] = NULL;
    }

    pm->npuntos = 0;
    pm->input = NULL;
    pm->output = NULL;

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
    if (!pm) {
        return NULL;
    }

    return pm->input;
}

Point* map_getOutput(const Map* pm)
{
    if (!pm) {
        return NULL;
    }

    return pm->output;
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
            pp_neightbar = pm->points[i];
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

/** TODO: Falta considerar la inserccion del punto de inicio y final del
 * laberinto. Además, hay que controlar que ocurre si se modifica el
 * punto de inicio y final del laberinto. **/
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
    if (indice > MAX_POINT) {
        return ERR;
    }

    /** Comprobamos si existe el punto **/
    if (pm->points[indice] != NULL) {
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
    int counter = 0;

    if (!pf || !pm) {
        return -1;
    }

    for (i = 0; i < pm->nrow; i++) {
        for (j = 0; j < pm->ncol; j++) {
            counter +=
              fprintf(pf, "%c", point_getSymbol(pm->points[i * pm->ncol + j]));
        }
        fprintf(pf, "\n");
    }
    return counter;
}
