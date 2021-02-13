#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "point.h"
#include "map.h"
#include "utils.h"
#include "types.h"

int main(int argc, char* argv[]){

    Status st;
    Map* pm = NULL;
    FILE *pf = NULL;
    Stack *ps = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }

    pm = map_ini();

    /* Cargar el mapa en memoria */
    st = map_read(pf, pm);
    if (st == ERR) {
        fclose(pf);
        map_free(pm);
        fprintf(stderr, "Error leyendo el mapa en memoria...\n");
        exit(EXIT_FAILURE);
    }

    ps = stack_ini(destroy_point_function, copy_point_function, print_point_function);
    if (!ps) {
        fclose(pf);
        map_free(pm);
        fprintf(stderr, "Error leyendo el mapa en memoria...\n");
        exit(EXIT_FAILURE);
    }

    if(deep_search(pm, ps)){
        printf("Es posible encontrar un camino\n");
        map_print(stdout, pm);
        stack_print(stdout, ps);
    }
    else{
        map_print(stdout, pm);
        stack_print(stdout, ps);
        printf("No es posible encontrar un camino\n");
    }

    fclose(pf);
    map_free(pm);
    stack_free(ps);

    return 0;
}
