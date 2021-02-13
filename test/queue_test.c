#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "point.h"

#define MAX_LENGTH_READER_BUFFER 7

int main(int argc, char* argv[])
{
    int i, npoints, x, y, size;
    char symbol;
    char buff[MAX_LENGTH_READER_BUFFER];
    Queue* q1 = NULL;
    Queue* q2 = NULL;
    Queue* q3 = NULL;
    Point* pp = NULL;
    FILE* pf = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }

    /* Obtenemos el numero de puntos */
    if (!fgets(buff, MAX_LENGTH_READER_BUFFER, pf)) {
        fclose(pf);
        exit(EXIT_FAILURE);
    };
    sscanf(buff, "%d", &npoints);

    q1 = queue_ini(
      destroy_point_function, copy_point_function, print_point_function);
    if (!q1) {
        fclose(pf);
        exit(EXIT_FAILURE);
    }
    q2 = queue_ini(
      destroy_point_function, copy_point_function, print_point_function);
    if (!q2) {
        fclose(pf);
        queue_free(q1);
        exit(EXIT_FAILURE);
    }
    q3 = queue_ini(
      destroy_point_function, copy_point_function, print_point_function);
    if (!q3) {
        fclose(pf);
        queue_free(q1);
        queue_free(q2);
        exit(EXIT_FAILURE);
    }

    pp = point_ini(0, 0, ERRCHAR);
    if (!pp) {
        fclose(pf);
        queue_free(q1);
        queue_free(q2);
        queue_free(q3);
        exit(EXIT_FAILURE);
    }

    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Estado inicial de las Colas\n");

    printf("Cola 1: ");
    queue_print(stdout, q1);
    printf("Cola 2: ");
    queue_print(stdout, q2);
    printf("Cola 3: ");
    queue_print(stdout, q3);

    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Insertando puntos en la Cola 1\n");

    /*Leemos el fichero linea a linea e introducimos los puntos en la cola 1*/
    for (i = 0; i < npoints; i++) {

        fgets(buff, MAX_LENGTH_READER_BUFFER, pf);

        sscanf(buff, "%d,%d,%c", &x, &y, &symbol);

        point_setCoordinateX(pp, x);

        point_setCoordinateY(pp, y);

        point_setSymbol(pp, symbol);

        queue_insert(q1, pp);
    }

    printf("Cola 1: ");
    queue_print(stdout, q1);
    printf("Cola 2: ");
    queue_print(stdout, q2);
    printf("Cola 3: ");
    queue_print(stdout, q3);

    /*Liberamos el punto temporal usado*/
    point_free(pp);

    /*Sacamos la mitad de los puntos introducidos en la Cola 1 y los
     * introducimos en Cola 2*/
    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Pasando la primera mitad de Cola 1 a Cola 2\n");

    size = queue_size(q1);
    i = 0;
    while (i < (size / 2)) {
        pp = (Point*)queue_extract(q1);
        queue_insert(q2, pp);
        point_free(pp);

        i++;
    }

    printf("Cola 1: ");
    queue_print(stdout, q1);
    printf("Cola 2: ");
    queue_print(stdout, q2);
    printf("Cola 3: ");
    queue_print(stdout, q3);

    /*Sacamos la otra mitad de los puntos introducidos en la Cola 1 y los
     * introducimos en Cola 3*/
    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Pasando la segunda mitad de Cola 1 a Cola 3\n");
    while (!queue_isEmpty(q1)) {
        pp = (Point*)queue_extract(q1);
        queue_insert(q3, pp);
        point_free(pp);
    }

    printf("Cola 1: ");
    queue_print(stdout, q1);
    printf("Cola 2: ");
    queue_print(stdout, q2);
    printf("Cola 3: ");
    queue_print(stdout, q3);

    queue_free(q1);
    queue_free(q2);
    queue_free(q3);
    fclose(pf);

    exit(EXIT_SUCCESS);
}
