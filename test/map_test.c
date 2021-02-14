#include <stdlib.h>

#include "map.h"
#include "utils.h"

int main(int argc, char* argv[]) {

    int nrow, ncol;
    Map* pm = NULL;
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

    /* Cargar el mapa en memoria */
    pm = map_read(pf);
    if (!pm) {
        fclose(pf);
        map_free(pm);
        fprintf(stderr, "Error leyendo el mapa en memoria...\n");
        exit(EXIT_FAILURE);
    }

    /* Comprobamos que los valores son correctos */
    nrow = map_getNrows(pm);
    ncol = map_getNcols(pm);
    printf("%d %d\n", nrow, ncol);
    if (map_print(stdout, pm) <= 0) {
        fclose(pf);
        map_free(pm);
        fprintf(stderr, "Error imprimiendo el mapa...\n");
        exit(EXIT_FAILURE);
    }

    fclose(pf);
    map_free(pm);
    exit(EXIT_SUCCESS);
}
