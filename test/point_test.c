#include "point.h"
#include <stdio.h>

int main()
{
    Point* pp1 = NULL;
    Point* pp2 = NULL;
    char s1;
    int x2;

    pp1 = point_ini(1, 2, BARRIER);
    pp2 = point_ini(3, 4, OUTPUT);

    point_print(stdout, pp1);
    point_print(stdout, pp2);
    printf("\n");

    printf("Son iguales? ");
    if (point_equals(pp1, pp2)) {
        printf("Si\n");
    } else {
        printf("No\n");
    }

    s1 = point_getSymbol(pp1);
    printf("El simbolo del primer punto es: %c\n", s1);

    x2 = point_getCoordinateX(pp2);
    printf("La coordenada X del segundo punto es: %d\n", x2);

    point_free(pp2);
    pp2 = point_copy(pp1);
    point_print(stdout, pp1);
    point_print(stdout, pp2);
    printf("\n");

    printf("Son iguales? ");
    if (point_equals(pp1, pp2)) {
        printf("Si\n");
    } else {
        printf("No\n");
    }

    point_free(pp1);
    point_free(pp2);

    return 0;
}
