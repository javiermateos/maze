/*
 * @file: utils.c
 * @brief: Implementacion del modulo Utils
 * @author: Javier Mateos
 *
 * @date 03/02/2021
 */

#include "utils.h"
#include "point.h"
#include "functions.h"

Status map_read(FILE* pf, Map* pm)
{
    char buff[MAX];
    int i, j, nrows, ncols;
    Point* temp;
    Status st = ERR;

    if (!pf || !pm) {
        return ERR;
    }

    /*Crea un punto que se utiliza como buffer*/
    temp = point_ini(0, 0, ERRCHAR);
    if (!temp) {
        fprintf(stderr, "Error inicializando el punto temporal...\n");
        return ERR;
    }

    /*Asignamos dimension al mapa*/
    if (fgets(buff, MAX, pf) == NULL) {
        point_free(temp);
        return ERR;
    };
    sscanf(buff, "%d %d", &nrows, &ncols);
    st = map_setSize(pm, nrows, ncols);
    if (st == ERR) {
        fprintf(stderr, "Error estableciendo las dimensiones del mapa...\n");
        point_free(temp);
        return ERR;
    }

    /*Leemos el fichero linea a linea*/
    for (i = 0; i < nrows; i++) {
        if (fgets(buff, MAX, pf) == NULL) {
            point_free(temp);
            return ERR;
        }
        for (j = 0; j < ncols; j++) {
            point_setCoordinateX(temp, j);
            point_setCoordinateY(temp, i);
            point_setSymbol(temp, buff[j]);
            if (map_setPoint(pm, temp) == ERR) {
                fprintf(stderr, "Error guardando el punto en el mapa...\n");
                point_free(temp);
                return ERR;
            }
        }
    }

    /*Libera recursos*/
    point_free(temp);

    return OK;
}

Bool deep_search(Map* pm, Stack* ps_c)
{
    char s;
    Move move;
    Point* pp = NULL;
    Point* pp_neightbar = NULL;
    Stack* ps = NULL;

    if (!pm || !ps_c) {
        return FALSE;
    }

    ps = stack_ini(destroy_point_function, copy_point_function, print_point_function);
    if (!ps) {
        return FALSE;
    }

    pp = map_getInput(pm);
    if (!pp) {
        stack_free(ps);
        return FALSE;
    }

    if (stack_push(ps, pp) == ERR || stack_push(ps_c, pp) == ERR) {
        return FALSE;
    }

    point_free(pp);

    while (!stack_isEmpty(ps)) {
        pp = (Point*)stack_pop(ps);
        s = point_getSymbol(pp);
        if (s != VISITED) {
            if (s != INPUT) {
                point_setSymbol(pp, VISITED);
                if (map_setPoint(pm, pp) == ERR) {
                    point_free(pp);
                    stack_free(ps);
                    return FALSE;
                }
            }
            for (move = RIGHT; move < STAY; move++) {
                pp_neightbar = map_getNeightbarPoint(pm, pp, move);
                if (point_isOutput(pp_neightbar)) {
                    stack_push(ps_c, pp_neightbar);
                    point_free(pp);
                    stack_free(ps);
                    return TRUE;
                }
                if (point_isSpace(pp_neightbar)) {
                    stack_push(ps, pp_neightbar);
                    stack_push(ps_c, pp_neightbar);
                }
            }
        }
        point_free(pp);
    } 

    return FALSE;
}
