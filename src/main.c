#include <stdlib.h>
#include <string.h>

#include "map_solver.h"
#include "types.h"
#include "utils.h"

#define NUM_STRATEGIES 4

/**
 * @brief Funciones de resolucion de mapas.
 * @param map_file Nombre del fichero en el que se encuentra el mapa.
 * @param strat Orden de aplicacion de las estrategias para la resolucion.
 * @return La longitud del camino optimo segun la estrategia introducida o
 * si no sabe calcularlo el numero de movimientos realizados para resolver
 * el mapa.
 */
void print_optimal_path(Map* pm);
void mapsolver_run(FILE* map_file,
                   const Move strat[][NUM_MOVEMENTS],
                   const int num_strategies,
                   const char* tad);

int main(int argc, char* argv[])
{
    FILE* pf = NULL;
    /** Estrategias seguidas para resolver el laberinto **/
    const Move strat[NUM_STRATEGIES][NUM_MOVEMENTS] = {
        { RIGHT, LEFT, UP, DOWN },
        { DOWN, RIGHT, LEFT, UP },
        { UP, DOWN, RIGHT, LEFT },
        { LEFT, UP, DOWN, RIGHT }
    };

    if (argc != 3) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        fprintf(stderr, "Formato: maze <map_file> <tad>");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }

    mapsolver_run(pf, strat, NUM_STRATEGIES, argv[2]);

    fclose(pf);

    exit(EXIT_SUCCESS);
}

void mapsolver_run(FILE* map_file,
                   const Move strat[][NUM_MOVEMENTS],
                   const int num_strategies,
                   const char* tad)
{
    int i;
    char const* move_to_str[] = {"RIGHT", "UP", "LEFT", "DOWN", "STAY"};

    for (i = 0; i < num_strategies; i++) {
        printf("Buscando el camino mediante la estrategia: ");
        printf("{ %s, %s, %s, %s }\n",
               move_to_str[strat[i][0]],
               move_to_str[strat[i][1]],
               move_to_str[strat[i][2]],
               move_to_str[strat[i][3]]);
        if (!strcmp(tad, "stack")) {
            mapsolver_stack(map_file, strat[i]);
        } else if (!strcmp(tad, "queue")) {
            mapsolver_queue(map_file, strat[i]);
        } else {
            mapsolver_recursive(map_file, strat[i]);
        }
        fseek(map_file, 0, SEEK_SET);
    }
}

