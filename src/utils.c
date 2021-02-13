/*
 * @file: utils.c
 * @brief: Implementacion del modulo Utils
 * @author: Javier Mateos
 *
 * @date 03/02/2021
 */

#include "utils.h"
#include "point.h"

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
