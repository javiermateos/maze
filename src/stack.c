/**
 * @file stack_element.c
 * @brief Implementacion del TAD Stack.
 * @author Javier Mateos
 *
 * @date 05/02/2020
 */

#include <stdlib.h>

#include "stack.h"

struct _Stack {
    int top;              /**< Indice del top de la pila */
    void* item[MAXSTACK]; /**< Representacion de la pila */
    free_element_function_type free_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

Stack* stack_ini(free_element_function_type f1,
                 copy_element_function_type f2,
                 print_element_function_type f3)
{
    int i;
    Stack* ps = NULL;

    ps = (Stack*)malloc(sizeof(Stack));
    if (!ps) {
        return NULL;
    }

    for (i = 0; i < MAXSTACK; i++) {
        ps->item[i] = NULL;
    }

    ps->top = -1;
    ps->free_element_function = f1;
    ps->copy_element_function = f2;
    ps->print_element_function = f3;

    return ps;
}

void stack_free(Stack* ps)
{
    int i;

    if (!ps) {
        return;
    }

    for (i = 0; i <= ps->top; i++) {
        ps->free_element_function(ps->item[i]);
        ps->item[i] = NULL;
    }
    free(ps);
}

Bool stack_isEmpty(const Stack* ps)
{
    if (!ps) {
        return FALSE;
    }

    if (ps->top == -1) {
        return TRUE;
    }

    return FALSE;
}

Bool stack_isFull(const Stack* ps)
{
    if (!ps) {
        return FALSE;
    }

    if (ps->top == MAXSTACK - 1) {
        return TRUE;
    }

    return FALSE;
}

Status stack_push(Stack* ps, const void* e)
{
    if (!ps || !e) {
        return ERR;
    }

    if (stack_isFull(ps)) {
        return ERR;
    }

    ps->top++;

    ps->item[ps->top] = ps->copy_element_function(e);
    if (!ps->item[ps->top]) {
        return ERR;
    }

    return OK;
}

void* stack_pop(Stack* ps)
{
    void* e = NULL;

    if (!ps) {
        return NULL;
    }

    if (stack_isEmpty(ps)) {
        return NULL;
    }

    e = ps->item[ps->top];
    ps->item[ps->top] = NULL;

    ps->top--;

    return e;
}

void* stack_top(Stack* ps)
{
    void* e = NULL;

    if (!ps) {
        return NULL;
    }

    if (stack_isEmpty(ps)) {
        return NULL;
    }

    e = ps->copy_element_function(ps->item[ps->top]);
    if (!e) {
        return NULL;
    }

    return e;
}

int stack_print(FILE* pf, const Stack* ps)
{
    int i;
    int counter = 0;

    if (!ps || !ps) {
        return -1;
    }

    counter += fprintf(pf, "Pila total ");
    if (stack_isFull(ps)) {
        counter += fprintf(pf, "(llena, ");
    } else {
        counter += fprintf(pf, "(no llena, ");
    }

    if (stack_isEmpty(ps)) {
        counter += fprintf(pf, "vacia):\n");
    } else {
        counter += fprintf(pf, "no vacia):\n");
    }

    for (i = ps->top; i >= 0; i--) {
        counter += ps->print_element_function(pf, ps->item[i]);
    }

    return counter;
}
