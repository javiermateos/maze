#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char* argv[])
{
    int i, num, size;
    List* pl = NULL;
    List* pl_ordered = NULL;
    FILE* pf = NULL;
    void* data = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    pf = fopen(argv[1], "r");
    if (!pf) {
        fprintf(stderr, "Error abriendo el fichero %s", __FILE__);
        exit(EXIT_FAILURE);
    }

    pl = list_ini(destroy_intp_function,
                  copy_intp_function,
                  print_intp_function,
                  cmp_intp_function);
    if (!pl) {
        fclose(pf);
        exit(EXIT_FAILURE);
    }

    /*Imprimimos el estado de la primera lista con cada inserción*/
    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Estado inicial de la lista...\n");

    list_print(stdout, pl);
    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Insertando enteros en la lista...\n");

    /*Leemos el fichero e introducimos los enteros en la pla*/
    while (fscanf(pf, "%d", &num) > 0) {
        if (num % 2 == 0) {
            list_insertFirst(pl, &num);
        } else {
            list_insertLast(pl, &num);
        }
    }

    printf("Estado de la lista: \n");
    list_print(stdout, pl);

    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Extrayendo los numeros de la lista e insertando de manera "
           "ordenada...\n");

    /*Inicializamos la lista para introducir los numeros en orden*/
    pl_ordered = list_ini(destroy_intp_function,
                          copy_intp_function,
                          print_intp_function,
                          cmp_intp_function);
    if (!pl_ordered) {
        fclose(pf);
        list_free(pl);
        exit(EXIT_FAILURE);
    }

    /*Proceso de extraccion de la primera parte*/
    printf(">>>Proceso de extraccion de la primera mitad...\n");
    size = (list_size(pl) / 2);
    for (i = 0; i < size; i++) {
        data = list_extractFirst(pl);
        list_insertInOrder(pl_ordered, data);
        free(data);
    }

    /*Proceso de extraccion de la segunda parte*/
    printf(">>>Proceso de extraccion de la segunda mitad.\n");
    while (!list_isEmpty(pl)) {
        data = list_extractLast(pl);
        list_insertInOrder(pl_ordered, data);
        free(data);
    }

    printf(
      "------------------------------------------------------------------\n");
    printf(">>>Estado final de la lista ordenada: \n");
    list_print(stdout, pl_ordered);

    /*Libera recursos*/
    fclose(pf);
    list_free(pl);
    list_free(pl_ordered);

    exit(EXIT_SUCCESS);
}
