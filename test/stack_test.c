#include <stdio.h>
#include <stdlib.h>

#include "stack_element.h"

int main(int argc, char* argv[])
{

    int i;
    int counter;
    int input;
    int* info;
    Element* e = NULL;
    Stack* ps = NULL;
    Stack* ps_par = NULL;
    Stack* ps_impar = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error en el numero de argumentos...\n");
        exit(EXIT_FAILURE);
    }

    /* Inicializacion de la pila */
    ps = stack_ini();
    if (!ps) {
        exit(EXIT_FAILURE);
    }

    if (stack_print(stdout, ps) < 0) {
        stack_free(ps);
        fprintf(stderr, "Error imprimiendo la pila...\n");
        exit(EXIT_FAILURE);
    }

    counter = atoi(argv[1]);

    /* Inserccion de elementos en la pila */
    for (i = 0; i < counter; i++) {
        fprintf(stdout, "Introduce un numero: ");
        scanf("%d", &input);
        e = element_ini();
        if (!e) {
            stack_free(ps);
            exit(EXIT_FAILURE);
        }
        if (element_setInfo(e, &input) == ERR) {
            fprintf(stderr, "Error modificando los datos del elemento..\n");
            stack_free(ps);
            exit(EXIT_FAILURE);
        }
        if (stack_push(ps, e) == ERR) {
            fprintf(stderr, "Error introduciendo el elemento en la pila...\n");
            stack_free(ps);
            exit(EXIT_FAILURE);
        }
        element_free(e);
    }

    if (stack_print(stdout, ps) < 0) {
        fprintf(stderr, "Error imprimiendo la pila...\n");
        stack_free(ps);
        exit(EXIT_FAILURE);
    }

    /* Inicializacion de la pila par e impar */
    ps_par = stack_ini();
    if (!ps_par) {
        fprintf(stderr, "Error creando la pila par...\n");
        stack_free(ps);
        exit(EXIT_FAILURE);
    }
    ps_impar = stack_ini();
    if (!ps_impar) {
        fprintf(stderr, "Error creando la pila impar...\n");
        stack_free(ps);
        stack_free(ps_par);
        exit(EXIT_FAILURE);
    }

    /* Inserccion de elementos en la pila par e impar */
    do {
        e = stack_pop(ps);
        if (!e) {
            fprintf(stderr, "Error obteniendo los elementos de la pila...\n");
            stack_free(ps);
            stack_free(ps_par);
            stack_free(ps_impar);
            exit(EXIT_FAILURE);
        }
        info = (int*)element_getInfo(e);
        if (!info) {
            fprintf(stderr,
                    "Error obteniendo la informacion del elemento...\n");
            element_free(e);
            stack_free(ps);
            stack_free(ps_par);
            stack_free(ps_impar);
            exit(EXIT_FAILURE);
        }
        if (*info % 2 == 0) {
            if (stack_push(ps_par, e) == ERR) {
                fprintf(stderr,
                        "Error introduciendo el elemento en la pila par...\n");
                free(info);
                element_free(e);
                stack_free(ps);
                stack_free(ps_par);
                stack_free(ps_impar);
                exit(EXIT_FAILURE);
            }
        } else {
            if (stack_push(ps_impar, e) == ERR) {
                fprintf(
                  stderr,
                  "Error introduciendo el elemento en la pila impar...\n");
                free(info);
                element_free(e);
                stack_free(ps);
                stack_free(ps_par);
                stack_free(ps_impar);
                exit(EXIT_FAILURE);
            }
        }
        free(info);
        element_free(e);
    } while (!stack_isEmpty(ps));

    fprintf(stdout, "Imprimiendo la pila con numeros pares...\n");
    if (stack_print(stdout, ps_par) < 0) {
        fprintf(stderr, "Error imprimiendo la pila...\n");
        stack_free(ps);
        stack_free(ps_par);
        stack_free(ps_impar);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Imprimiendo la pila con numeros impares...\n");
    if (stack_print(stdout, ps_impar) < 0) {
        fprintf(stderr, "Error imprimiendo la pila...\n");
        stack_free(ps);
        stack_free(ps_par);
        stack_free(ps_impar);
        exit(EXIT_FAILURE);
    }

    if (stack_print(stdout, ps) < 0) {
        fprintf(stderr, "Error imprimiendo la pila...\n");
        stack_free(ps);
        stack_free(ps_par);
        stack_free(ps_impar);
        exit(EXIT_FAILURE);
    }

    stack_free(ps);
    stack_free(ps_par);
    stack_free(ps_impar);

    exit(EXIT_SUCCESS);
}
