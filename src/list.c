/**
 * @file list.c
 * @brief Implementacion de la interfaz publica del TAD List.
 * @author Javier Mateos
 *
 * @date 10/02/2021
 */

#include <stdlib.h>

#include "list.h"

typedef struct _Node {
    void* item;
    struct _Node* next;
} Node;

struct _List {
    Node* first;
    free_element_function_type free_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;
};

Node* node_ini()
{
    Node* pn = NULL;

    pn = (Node*)malloc(sizeof(Node));
    if (!pn) {
        return NULL;
    }

    pn->item = NULL;
    pn->next = NULL;

    return pn;
}

void node_free(List* pl, Node* pn)
{
    if (!pn) {
        return;
    }
    
    if (pn->item) {
        pl->free_element_function(pn->item);
    }
    free(pn);
}

List* list_ini(free_element_function_type f1,
               copy_element_function_type f2,
               print_element_function_type f3,
               cmp_element_function_type f4)
{
    List* pl = NULL;

    pl = (List*)malloc(sizeof(List));
    if (!pl) {
        return NULL;
    }

    pl->first = NULL;
    pl->free_element_function = f1;
    pl->copy_element_function = f2;
    pl->print_element_function = f3;
    pl->cmp_element_function = f4;

    return pl;
}

void list_free(List* pl)
{
    Node* pn = NULL;

    if (!pl) {
        return;
    }

    while (pl->first) {
        pn = pl->first;
        pl->first = pl->first->next;
        node_free(pl, pn);
    }

    free(pl);
}

Status list_insertFirst(List* pl, const void* e)
{
    Node* pn = NULL;

    if (!pl || !e) {
        return ERR;
    }

    pn = node_ini();
    if (!pn) {
        return ERR;
    }

    pn->item = pl->copy_element_function(e);
    if (!pn->item) {
        node_free(pl, pn);
        return ERR;
    }

    pn->next = pl->first;
    pl->first = pn;

    return OK;
}

Status list_insertLast(List* pl, const void* e)
{
    Node* pn = NULL;
    Node* pn_aux = NULL;

    if (!pl || !e) {
        return ERR;
    }

    pn = node_ini();
    if (!pn) {
        return ERR;
    }

    pn->item = pl->copy_element_function(e);
    if (!pn->item) {
        node_free(pl, pn);
        return ERR;
    }

    if (list_isEmpty(pl)) {
        pl->first = pn;
    } else {
        pn_aux = pl->first;
        while (pn_aux->next) {
            pn_aux = pn_aux->next;
        }
        pn_aux->next = pn;
    }

    return OK;
}

Status list_insertInOrder(List* pl, const void* e)
{
    Node* pn = NULL;
    Node* pn_aux = NULL;

    if (!pl || !e) {
        return ERR;
    }

    pn = node_ini();
    if (!pn) {
        return ERR;
    }

    pn->item = pl->copy_element_function(e);
    if (!pn->item) {
        node_free(pl, pn);
        return ERR;
    }

    if (list_isEmpty(pl)) {
        pl->first = pn;
    } else {
        pn_aux = pl->first;
        if (pl->cmp_element_function(pn->item, pn_aux->item) <= 0) {
            pn->next = pn_aux;
            pl->first = pn;
        } else {
            while (pn_aux->next &&
                   pl->cmp_element_function(pn->item, pn_aux->next->item) > 0) {
                pn_aux = pn_aux->next;
            }
            pn->next = pn_aux->next;
            pn_aux->next = pn;
        }
    }

    return OK;
}

void* list_extractFirst(List* pl)
{
    Node* pn = NULL;
    void* e = NULL;

    if (!pl) {
        return NULL;
    }

    if (list_isEmpty(pl)) {
        return NULL;
    }

    pn = pl->first;

    e = pl->copy_element_function(pn->item);
    if (!e) {
        return NULL;
    }

    pl->first = pn->next;
    node_free(pl, pn);

    return e;
}

void* list_extractLast(List* pl)
{
    void* e = NULL;
    Node* pn = NULL;

    if (!pl) {
        return NULL;
    }

    if (list_isEmpty(pl)) {
        return NULL;
    }

    if (!pl->first->next) {
        e = pl->copy_element_function(pl->first->item);
        if (!e) {
            return NULL;
        }
        node_free(pl, pl->first);
        pl->first = NULL;
    } else {
        pn = pl->first;
        while (pn->next->next) {
            pn = pn->next;
        }
        e = pl->copy_element_function(pn->next->item);
        if (!e) {
            return NULL;
        }
        node_free(pl, pn->next);
        pn->next = NULL;
    }

    return e;
}

Bool list_isEmpty(const List* pl)
{
    if (!pl) {
        return FALSE;
    }

    if (pl->first) {
        return FALSE;
    }

    return TRUE;
}

const void* list_get(const List* pl, int i)
{
    int counter = 0;
    Node* pn = NULL;

    if (!pl || i < 1) {
        return NULL;
    }

    pn = pl->first;
    while (counter < i && pn->next) {
        counter++;
        pn = pn->next;
    }

    return pn->item;
}

int list_size(const List* pl)
{
    int counter = 1;
    Node* pn = NULL;

    if (!pl) {
        return -1;
    }

    if (list_isEmpty(pl)) {
        return 0;
    }

    pn = pl->first;
    while (pn->next) {
        pn = pn->next;
        counter++;
    }

    return counter;
}

int list_print(FILE* pf, const List* pl)
{
    int counter = 0;
    Node* pn = NULL;

    if (!pf || !pl) {
        return -1;
    }

    if (list_isEmpty(pl)) {
        fprintf(pf, "List vacia\n");
    } else {
        fprintf(pf, "List con %d elementos\n", list_size(pl));
        pn = pl->first;
        while (pn->next != NULL) {
            pl->print_element_function(pf, pn->item);
            pn = pn->next;
            counter++;
        }
        pl->print_element_function(pf, pn->item);
        counter++;
    }

    return counter;
}
