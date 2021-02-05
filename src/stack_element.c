/**
 * @file stack_element.c
 * @brief Implementacion del TAD Stack.
 * @author Javier Mateos
 *
 * @date 05/02/2020
 */

#include <stdlib.h>

#include "stack_element.h"

struct _Stack {
    int top; /**< Indice del top de la pila */
    Element* item[MAXSTACK]; /**< Representacion de la pila */
};

Stack* stack_ini()
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

    return ps;
}

void stack_free(Stack* ps)
{
    int i;

    if (!ps) {
        return;
    }
    
    for (i = 0; i <= ps->top; i++) {
        element_free(ps->item[i]);
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

Status stack_push(Stack* ps, const Element* e)
{
    if (!ps || !e) {
        return ERR;
    }
    
    if (stack_isFull(ps)) {
        return ERR;
    }

    ps->top++;

    ps->item[ps->top] = element_copy(e);
    if (!ps->item[ps->top]) {
        return ERR;
    }

    return OK;
}

Element* stack_pop(Stack* ps)
{
    Element* e = NULL;

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

Element* stack_top(Stack* ps)
{
    Element* e = NULL;

    if (!ps) {
        return NULL;
    }

    if (stack_isEmpty(ps)) {
        return NULL;
    }

    e = element_copy(ps->item[ps->top]);
    if (!e) {
        return NULL;
    }

    return e;
}

int stack_print(FILE* pf, const Stack* ps) 
{
    int i;
    int counter = 0;
    int* value;

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

    for (i = 0; i < MAXSTACK && ps->item[i] != NULL; i++) {
        value = (int*)element_getInfo(ps->item[i]);
        counter += fprintf(pf, "[%d]\n", *value);
    }

    return counter;
}
