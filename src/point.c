/**
 * @file point.c
 * @brief Implementacion del TAD Point.
 * @author Javier Mateos
 *
 * @date 01/02/2020
 */

#include <stdlib.h>
#include <string.h>

#include "point.h"
#include "types.h"

struct _Point {
    int x;  /**< La coordenada x en el mapa */
    int y;  /**< La coordenada y en el mapa */
    char s; /**< El simbolo de representacion del punto */
};

Point* point_ini(int x, int y, char s)
{
    Point* pp = NULL;

    pp = (Point*)malloc(sizeof(Point));
    if (!pp) {
        return NULL;
    }

    pp->x = x;
    pp->y = y;
    pp->s = s;

    return pp;
}

void point_free(Point* pp)
{
    if (!pp) {
        return;
    }

    free(pp);
}

int point_getCoordinateX(const Point* pp)
{
    if (!pp) {
        return -1;
    }

    return pp->x;
}

int point_getCoordinateY(const Point* pp)
{
    if (!pp) {
        return -1;
    }

    return pp->y;
}

char point_getSymbol(const Point* pp)
{
    if (!pp) {
        return ERRCHAR;
    }

    return pp->s;
}

Bool point_isInput(Point* pp)
{
    if (!pp || pp->s != INPUT) {
        return FALSE;
    }

    return TRUE;
}

Bool point_isOutput(Point* pp)
{
    if (!pp || pp->s != OUTPUT) {
        return FALSE;
    }

    return TRUE;
}

Bool point_isBarrier(Point* pp)
{
    if (!pp || pp->s != BARRIER) {
        return FALSE;
    }

    return TRUE;
}

Bool point_isSpace(Point* pp)
{
    if (!pp || pp->s != SPACE) {
        return FALSE;
    }

    return TRUE;
}

Status point_setCoordinateX(Point* pp, const int x)
{
    if (!pp) {
        return ERR;
    }

    pp->x = x;

    return OK;
}

Status point_setCoordinateY(Point* pp, const int y)
{
    if (!pp) {
        return ERR;
    }

    pp->y = y;

    return OK;
}

Status point_setSymbol(Point* pp, const char s)
{
    if (!pp) {
        return ERR;
    }

    pp->s = s;

    return OK;
}

Bool point_equals(const Point* pp1, const Point* pp2)
{
    if (!pp1 || !pp2 || pp1->x != pp2->x || pp1->y != pp2->y ||
        pp1->s != pp2->s) {
        return FALSE;
    }

    return TRUE;
}

Point* point_copy(const Point* pp)
{
    Point* pp_copy = NULL;

    if (!pp) {
        return NULL;
    }

    pp_copy = (Point*)malloc(sizeof(Point));
    if (!pp_copy) {
        return NULL;
    }

    pp_copy->x = pp->x;
    pp_copy->y = pp->y;
    pp_copy->s = pp->s;

    return pp_copy;
}

int point_print(FILE* pf, const Point* pp)
{
    if (!pf || !pp) {
        return -1;
    }

    return fprintf(pf, "[(%d,%d): %c]", pp->x, pp->y, pp->s);
}
