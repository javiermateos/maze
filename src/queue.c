/**
 * @file queue.c
 * @brief Implementacion de la interfaz publica del TAD Queue.
 * @author Javier Mateos
 *
 * @date 09/02/2021
 */

#include <stdlib.h>

#include "queue.h"

struct _Queue {
    void** head; /**< Punto de pop de la cola */
    void** end;  /**< Punto de push de la cola */
    void* item[MAXQUEUE];
    destroy_elementqueue_function_type destroy_element_function;
    copy_elementqueue_function_type copy_element_function;
    print_elementqueue_function_type print_element_function;
};

Queue* queue_ini(destroy_elementqueue_function_type f1,
                 copy_elementqueue_function_type f2,
                 print_elementqueue_function_type f3)
{
    Queue* pq = NULL;

    pq = (Queue*)malloc(sizeof(Queue));
    if (!pq) {
        return NULL;
    }

    pq->head = pq->item;
    pq->end = pq->item;

    pq->destroy_element_function = f1;
    pq->copy_element_function = f2;
    pq->print_element_function = f3;

    return pq;
}

void queue_free(Queue* pq)
{
    if (!pq) {
        return;
    }

    while (pq->head != pq->end) {
        pq->destroy_element_function(*(pq->head));
        if (pq->head != pq->item + MAXQUEUE + 1) {
            pq->head = pq->head + 1;
        } else {
            pq->head = pq->item;
        }
    }

    free(pq);
}

Bool queue_isEmpty(const Queue* pq)
{
    if (!pq) {
        return FALSE;
    }

    if (pq->head != pq->end) {
        return FALSE;
    }

    return TRUE;
}

Bool queue_isFull(const Queue* pq)
{
    void** aux = NULL;

    if (!pq) {
        return FALSE;
    }

    if (pq->end == pq->item + MAXQUEUE - 1) {
        aux = (void**)pq->item;
    } else {
        aux = pq->end + 1;
    }

    if (aux != pq->head) {
        return FALSE;
    }

    return TRUE;
}

Status queue_insert(Queue* pq, const void* e)
{
    if (!pq || !e) {
        return ERR;
    }

    if (queue_isFull(pq)) {
        return ERR;
    }

    *(pq->end) = pq->copy_element_function(e);
    if (!*(pq->end)) {
        return ERR;
    }

    if (pq->end == pq->item + MAXQUEUE + 1) {
        pq->end = pq->item;
    } else {
        pq->end++;
    }

    return OK;
}

void* queue_extract(Queue* pq)
{
    void* e = NULL;

    if (!pq) {
        return NULL;
    }

    if (queue_isEmpty(pq)) {
        return NULL;
    }

    e = *(pq->head);
    *(pq->head) = NULL;

    if (pq->head == pq->item + MAXQUEUE + 1) {
        pq->head = pq->item;
    } else {
        pq->head++;
    }

    return e;
}

int queue_size(const Queue* pq)
{
    if (!pq) {
        return -1;
    }

    /*TODO: Revisar si se puede hacer asi.*/
    return pq->end - pq->head + 1;
}

int queue_print(FILE* pf, const Queue* pq)
{
    int counter = 0;
    void** aux = NULL;

    if (pf == NULL || pq == NULL)
        return -1;

    if (queue_isEmpty(pq)) {
        fprintf(pf, "Cola vacia\n");
    } else {
        fprintf(pf, "Cola con %d elementos de %d\n", queue_size(pq), MAXQUEUE);
        aux = pq->head;
        while (aux != pq->end) {
            pq->print_element_function(pf, *(aux));
            if (aux == pq->item + MAXQUEUE - 1) {
                aux = (void**)pq->item;
            } else {
                aux++;
            }
            counter++;
        }
    }

    return counter;
}
