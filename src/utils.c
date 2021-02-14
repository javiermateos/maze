/*
 * @file: utils.c
 * @brief: Implementacion del modulo Utils
 * @author: Javier Mateos
 *
 * @date 03/02/2021
 */

#include "utils.h"
#include "point.h"

Map* map_read(FILE* pf)
{
    char buff[MAX];
    int i, j, nrows, ncols;
    Point* temp = NULL;
    Map* pm = NULL;
    Status st = ERR;

    if (!pf) {
        return NULL;
    }

    pm = map_ini();
    if (!pm) {
        fprintf(stderr, "Error inicializando el mapa...\n");
        return NULL;
    }

    /*Crea un punto que se utiliza como buffer*/
    temp = point_ini(0, 0, ERRCHAR);
    if (!temp) {
        map_free(pm);
        fprintf(stderr, "Error inicializando el punto temporal...\n");
        return NULL;
    }

    /*Asignamos dimension al mapa*/
    if (fgets(buff, MAX, pf) == NULL) {
        map_free(pm);
        point_free(temp);
        return NULL;
    };
    sscanf(buff, "%d %d", &nrows, &ncols);
    st = map_setSize(pm, nrows, ncols);
    if (st == ERR) {
        point_free(temp);
        map_free(pm);
        fprintf(stderr, "Error estableciendo las dimensiones del mapa...\n");
        return NULL;
    }

    /*Leemos el fichero linea a linea*/
    for (i = 0; i < nrows; i++) {
        if (fgets(buff, MAX, pf) == NULL) {
            point_free(temp);
            map_free(pm);
            return NULL;
        }
        for (j = 0; j < ncols; j++) {
            point_setCoordinateX(temp, j);
            point_setCoordinateY(temp, i);
            point_setSymbol(temp, buff[j]);
            if (!map_setPoint(pm, temp)) {
                fprintf(stderr, "Error guardando el punto en el mapa...\n");
                point_free(temp);
                map_free(pm);
                return NULL;
            }
        }
    }

    /*Libera recursos*/
    point_free(temp);

    return pm;
}
