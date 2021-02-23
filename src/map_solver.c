#include "map_solver.h"
#include "map.h"
#include "point.h"
#include "utils.h"
#include "stack.h"
#include "queue.h"

/** Funciones privadas **/
Point* mapsolver_recursive_rec(Map* pm,
                               const Move strat[NUM_MOVEMENTS],
                               Point* pp);
void print_optimal_path(Map* pm);
/************************/

void print_optimal_path(Map* pm)
{
    int counter;
    Point* output = NULL;
    Point* pp = NULL;

    output = map_getOutput(pm);
    point_print(stdout, output);
    for (counter = 0, pp = point_getParent(output); pp != NULL; counter++) {
        if (!point_isInput(pp)) {
            point_setSymbol(pp, PATH);
        }
        point_print(stdout, pp);
        pp = point_getParent(pp);
    }
    map_print(stdout, pm);
    printf("Longitud del camino optimo: %d\n", counter);
}

Bool mapsolver_stack(FILE* map_file, const Move strat[NUM_MOVEMENTS])
{
    int i;
    char s;
    Point* pp = NULL;
    Point* pp_neightbar = NULL;
    Stack* ps = NULL;
    Map* pm = NULL;

    if (!map_file || !strat) {
        return FALSE;
    }

    pm = map_read(map_file);
    if (!pm) {
        return FALSE;
    }

    ps = stack_ini(
      destroy_point_function, copy_point_function, print_point_function);
    if (!ps) {
        map_free(pm);
        return FALSE;
    }

    pp = map_getInput(pm);
    if (!pp) {
        stack_free(ps);
        map_free(pm);
        return FALSE;
    }

    if (!stack_push(ps, pp)) {
        return FALSE;
    }

    while (!stack_isEmpty(ps)) {
        pp = (Point*)stack_pop(ps);
        s = point_getSymbol(pp);
        if (s != VISITED) {
            /* No queremos que el simbolo de entrada se cambie */
            if (s != INPUT) {
                point_setSymbol(pp, VISITED);
                if (!map_setPoint(pm, pp)) {
                    point_free(pp);
                    map_free(pm);
                    stack_free(ps);
                    return FALSE;
                }
            }
            for (i = 0; i < NUM_MOVEMENTS; i++) {
                pp_neightbar = map_getNeightbarPoint(pm, pp, strat[i]);
                if (point_isOutput(pp_neightbar)) {
                    point_setParent(pp_neightbar, map_getPoint(pm, pp));
                    print_optimal_path(pm);
                    point_free(pp);
                    map_free(pm);
                    stack_free(ps);
                    return TRUE;
                }
                if (point_isSpace(pp_neightbar)) {
                    point_setParent(pp_neightbar, map_getPoint(pm, pp));
                    stack_push(ps, pp_neightbar);
                }
            }
        }
        point_free(pp);
    }

    map_free(pm);
    stack_free(ps);

    return FALSE;
}

Bool mapsolver_queue(FILE* map_file, const Move strat[NUM_MOVEMENTS])
{
    int i;
    char s;
    Point* pp = NULL;
    Point* pp_neightbar = NULL;
    Queue* pq = NULL;
    Map* pm = NULL;

    if (!map_file || !strat) {
        return FALSE;
    }

    pm = map_read(map_file);
    if (!pm) {
        return FALSE;
    }

    pq = queue_ini(
      destroy_point_function, copy_point_function, print_point_function);
    if (!pq) {
        map_free(pm);
        return FALSE;
    }

    pp = map_getInput(pm);
    if (!pp) {
        map_free(pm);
        queue_free(pq);
        return FALSE;
    }

    if (!queue_insert(pq, pp)) {
        map_free(pm);
        queue_free(pq);
        return FALSE;
    }

    while (!queue_isEmpty(pq)) {
        pp = (Point*)queue_extract(pq);
        s = point_getSymbol(pp);
        if (s != VISITED) {
            /* No queremos que el simbolo de entrada se cambie */
            if (s != INPUT) {
                point_setSymbol(pp, VISITED);
                if (!map_setPoint(pm, pp)) {
                    point_free(pp);
                    map_free(pm);
                    queue_free(pq);
                    return FALSE;
                }
            }
            for (i = 0; i < NUM_MOVEMENTS; i++) {
                pp_neightbar = map_getNeightbarPoint(pm, pp, strat[i]);
                if (point_isOutput(pp_neightbar)) {
                    point_setParent(pp_neightbar, map_getPoint(pm, pp));
                    print_optimal_path(pm);
                    point_free(pp);
                    map_free(pm);
                    queue_free(pq);
                    return TRUE;
                }
                if (point_isSpace(pp_neightbar)) {
                    point_setParent(pp_neightbar, map_getPoint(pm, pp));
                    queue_insert(pq, pp_neightbar);
                }
            }
        }
        point_free(pp);
    }

    queue_free(pq);
    map_free(pm);

    return FALSE;
}

Bool mapsolver_recursive(FILE* map_file, const Move strat[NUM_MOVEMENTS])
{
    Point* pp = NULL;
    Map* pm = NULL;

    if (!map_file || !strat) {
        return FALSE;
    }

    pm = map_read(map_file);
    if (!pm) {
        return FALSE;
    }

    pp = map_getInput(pm);
    if (!pp) {
        map_free(pm);
        return FALSE;
    }

    pp = mapsolver_recursive_rec(pm, strat, pp);
    if (!pp) {
        map_free(pm);
        return FALSE;
    }

    print_optimal_path(pm);
    map_free(pm);

    return TRUE;
}

Point* mapsolver_recursive_rec(Map* pm,
                               const Move strat[NUM_MOVEMENTS],
                               Point* pp)
{
    int i;
    Point* pp_neightbar = NULL;
    Point* pp_aux = NULL;

    if (point_isOutput(pp)) {
        return pp;
    }

    if (!pp) {
        return NULL;
    }

    if (!point_isInput(pp)) {
        point_setSymbol(pp, VISITED);
    }

    for (i = 0; i < NUM_MOVEMENTS; i++) {
        pp_neightbar = map_getNeightbarPoint(pm, pp, strat[i]);
        if (pp_neightbar) {
            if (point_getSymbol(pp_neightbar) != BARRIER &&
                point_getSymbol(pp_neightbar) != VISITED &&
                point_getSymbol(pp_neightbar) != INPUT &&
                point_getSymbol(pp_neightbar) != VISITING) {
                point_setParent(pp_neightbar, pp);
                if (!point_isOutput(pp_neightbar)) {
                    point_setSymbol(pp_neightbar, VISITING);
                }
                pp_aux = mapsolver_recursive_rec(pm, strat, pp_neightbar);
                if (pp_aux) {
                    return pp_aux;
                }
            }
        }
    }
    
    return NULL;
}
