#include <stdlib.h>

#include "stack.h"
#include "map.h"
#include "types.h"

Bool deep_search(Map* pm, Stack* ps_c);
/**
 * @brief Funciones de resolucion de mapas.
 * @param map_file Nombre del fichero en el que se encuentra el mapa.
 * @param strat Orden de aplicacion de las estrategias para la resolucion.
 * @return La longitud del camino optimo segun la estrategia introducida o
 * si no sabe calcularlo el numero de movimientos realizados para resolver
 * el mapa.
 */
int mapsolver_stack(const char* map_file, const Move strat[4]);
int mapsolver_queue(const char* map_file, const Move strat[4]);
int mapsolver_list(const char* map_file, const Move strat[4]);
int mapsolver_tree(const char* map_file, const Move strat[4]);

int main(int argc, char* argv[])
{
    FILE* pf = NULL;

    if (argc != 2) {
        fprintf(pf, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
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
