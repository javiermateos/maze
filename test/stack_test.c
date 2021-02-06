#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "map.h"
#include "point.h"
#include "stack.h"
#include "utils.h"

#define MAX 100

int main(int argc, char* argv[])
{
    char buff[MAX];
    int i, j, nrows, ncols;
    FILE* pf = NULL;
    Point* pp = NULL;
    Stack* ps_p = NULL;
    Stack* ps_x = NULL;
    Stack* ps_y = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }


    if (!fgets(buff, MAX, pf)) {
        fprintf(stderr, "Error leyendo el mapa...\n");
        point_free(pp);
        fclose(pf);
        exit(EXIT_FAILURE);
    };
    sscanf(buff, "%d %d", &nrows, &ncols);

    ps_p = stack_ini(
      destroy_point_function, copy_point_function, print_point_function);
    ps_x =
      stack_ini(destroy_intp_function, copy_intp_function, print_intp_function);
    ps_y =
      stack_ini(destroy_intp_function, copy_intp_function, print_intp_function);

    for (i = 0; i < nrows; i++) {
        fgets(buff, MAX, pf);
        for (j = 0; j < ncols; j++) {
            pp = point_ini(0, 0, ERRCHAR);
            if (point_setCoordinateX(pp, j) == ERR ||
                stack_push(ps_x, &j) == ERR) {
                fclose(pf);
                stack_free(ps_p);
                stack_free(ps_x);
                stack_free(ps_y);
                point_free(pp);
                exit(EXIT_FAILURE);
            }
            if (!point_setCoordinateY(pp, i) ||
                stack_push(ps_y, &i) == ERR) {
                stack_free(ps_p);
                stack_free(ps_x);
                stack_free(ps_y);
                point_free(pp);
                return 1;
            }
            if (point_setSymbol(pp, buff[j]) == ERRCHAR) {
                stack_free(ps_p);
                stack_free(ps_x);
                stack_free(ps_y);
                point_free(pp);
                return 1;
            }
            if (stack_push(ps_p, pp) == ERR) {
                stack_free(ps_p);
                stack_free(ps_x);
                stack_free(ps_y);
                point_free(pp);
                return 1;
            }
            point_free(pp);
        }
    }

    printf(
      "------------------------------------------------------------------\n");

    fprintf(stdout, "Pila de coordenadas X:\n");
    stack_print(stdout, ps_x);

    printf(
      "------------------------------------------------------------------\n");

    fprintf(stdout, "Pila de coordenadas Y:\n");
    stack_print(stdout, ps_y);

    printf(
      "------------------------------------------------------------------\n");

    fprintf(stdout, "Pila de puntos:\n");
    stack_print(stdout, ps_p);

    printf(
      "------------------------------------------------------------------\n");

    /*Libera recursos*/
    fclose(pf);
    stack_free(ps_p);
    stack_free(ps_x);
    stack_free(ps_y);

    return 0;
}
