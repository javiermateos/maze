#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main(int argc, char* argv[])
{
    FILE* pf = NULL;
    Tree* pa = NULL;
    int num;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }

    pa = tree_ini(destroy_intp_function,
            copy_intp_function,
            print_intp_function,
            cmp_intp_function);
    if (!pa) {
        fclose(pf);
        exit(EXIT_FAILURE);
    }

    /*Leemos el fichero linea a linea e introducimos los numeros en el arbol*/
    while (fscanf(pf, "%d", &num) > 0) {
        if(!tree_insert(pa, &num)) {
            fprintf(stderr, "Error insertando los elementos en el arbol...\n");
            fclose(pf);
            tree_free(pa);
            exit(EXIT_FAILURE);
        }
    }

    printf("Numero de nodos: %d\n", tree_numNodes(pa));
    printf("Profundidad: %d\n", tree_depth(pa));

    printf("Orden previo:\n");
    tree_preOrder(stdout, pa);
    printf("\n");

    printf("Orden medio:\n");
    tree_inOrder(stdout, pa);
    printf("\n");

    printf("Orden posterior:\n");
    tree_postOrder(stdout, pa);
    printf("\n");

    printf("Introduce un numero: ");
    scanf("%d", &num);

    if (tree_find(pa, &num)) {
        printf("El dato %d se encuentra dentro del Arbol\n", num);
    } else {
        printf("El dato %d NO se encuentra dentro del Arbol\n", num);
    }

    tree_free(pa);
    fclose(pf);

    return 0;
}
