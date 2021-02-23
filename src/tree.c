/**
 * @file tree.c
 * @brief Implementacion de la interfaz publica del TAD Tree.
 * @author Javier Mateos
 *
 * @date 13/02/2021
 */

#include <stdlib.h>

#include "tree.h"

typedef struct _NodeBT {
    void* info;
    struct _NodeBT* left;
    struct _NodeBT* right;
} NodeBT;

struct _Tree {
    NodeBT* root;
    free_element_function_type free_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;
};

/** Funciones privadas **/
static NodeBT* node_ini();
static void node_free(Tree* pa, NodeBT* pn);
void tree_free_rec(Tree* pa, NodeBT** ppn);
Status tree_insert_rec(Tree* pa, NodeBT** ppn, const void* e);
Bool tree_find_rec(Tree* pa, NodeBT** ppn, const void* e);
int maximo(int a, int b);
int tree_depth_rec(const Tree* pa, NodeBT* const* ppn);
int tree_numNodes_rec(const Tree* pa, NodeBT* const* ppn);
Status tree_preOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn);
Status tree_inOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn);
Status tree_postOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn);
/************************/

static NodeBT* node_ini()
{
    NodeBT* pn = NULL;

    pn = (NodeBT*)malloc(sizeof(NodeBT));
    if (!pn) {
        return NULL;
    }

    pn->info = NULL;
    pn->left = NULL;
    pn->right = NULL;

    return pn;
}

static void node_free(Tree* pa, NodeBT* pn)
{
    if (!pn) {
        return;
    }

    if (pn->info) {
        pa->free_element_function(pn->info);
    }

    free(pn);
}

Tree* tree_ini(free_element_function_type f1,
               copy_element_function_type f2,
               print_element_function_type f3,
               cmp_element_function_type f4)
{
    Tree* pa = NULL;

    pa = (Tree*)malloc(sizeof(Tree));
    if (!pa) {
        return NULL;
    }

    pa->root = NULL;
    pa->free_element_function = f1;
    pa->copy_element_function = f2;
    pa->print_element_function = f3;
    pa->cmp_element_function = f4;

    return pa;
}

void tree_free(Tree* pa)
{
    if (!pa) {
        return;
    }

    tree_free_rec(pa, &(pa->root));

    free(pa);
}

void tree_free_rec(Tree* pa, NodeBT** ppn)
{
    if (!ppn) {
        return;
    }

    if ((*ppn)->left) {
        tree_free_rec(pa, &(*ppn)->left);
    }
    if ((*ppn)->right) {
        tree_free_rec(pa, &(*ppn)->right);
    }
    node_free(pa, *ppn);
}

Status tree_insert(Tree* pa, const void* e)
{
    if (!pa || !e) {
        return ERR;
    }

    return tree_insert_rec(pa, &(pa->root), e);
}

Status tree_insert_rec(Tree* pa, NodeBT** ppn, const void* e)
{
    int cmp;

    /** Caso base **/
    if (!*ppn) {
        *ppn = node_ini();
        if (!*ppn) {
            return ERR;
        }
        (*ppn)->info = pa->copy_element_function(e);
        if (!(*ppn)->info) {
            node_free(pa, *ppn);
            return ERR;
        }
        return OK;
    }

    /** Recursividad **/
    cmp = pa->cmp_element_function(e, (*ppn)->info);
    if (cmp < 0) {
        return tree_insert_rec(pa, &((*ppn)->left), e);
    } else if (cmp > 0) {
        return tree_insert_rec(pa, &((*ppn)->right), e);
    }

    /** El elemento se encuentra en el arbol **/
    return OK;
}

Bool tree_find(Tree* pa, const void* e)
{
    if (!pa || !e) {
        return FALSE;
    }

    if (tree_isEmpty(pa)) {
        return FALSE;
    }

     return tree_find_rec(pa, &(pa->root), e);
}

Bool tree_find_rec(Tree* pa, NodeBT** ppn, const void* e)
{
    int cmp;

    /** Caso base **/
    if (!*ppn) {
        return FALSE;
    }

    /** Recursividad **/
    cmp = pa->cmp_element_function(e, (*ppn)->info);
    if (cmp < 0) {
        return tree_find_rec(pa, &((*ppn)->left), e);
    } else if (cmp > 0) {
        return tree_find_rec(pa, &((*ppn)->right), e);
    }

    return TRUE;
}

Bool tree_isEmpty(const Tree* pa)
{
    if (!pa) {
        return TRUE;
    }

    if (!pa->root) {
        return TRUE;
    }

    return FALSE;
}

int tree_depth(const Tree* pa)
{
    if (!pa) {
        return -2;
    }

    if (tree_isEmpty(pa)) {
        return -1;
    }

    return tree_depth_rec(pa, &(pa->root));
}

int tree_depth_rec(const Tree* pa, NodeBT* const* ppn)
{
    int left_depth;
    int right_depth;

    /** Caso base **/
    if (!*ppn) {
        return -1;
    }

    /** Recursividad **/
    left_depth = tree_depth_rec(pa, &((*ppn)->left));
    right_depth = tree_depth_rec(pa, &((*ppn)->right));

    return maximo(left_depth, right_depth) + 1;
}

int maximo(int a, int b)
{
    if (a > b) {
        return a;
    }
    
    return b;
}

int tree_numNodes(const Tree* pa)
{
    if (!pa) {
        return -1;
    }

    if (tree_isEmpty(pa)) {
        return 0;
    }

    return tree_numNodes_rec(pa, &(pa->root));
}

int tree_numNodes_rec(const Tree* pa, NodeBT* const* ppn)
{
    int left_numNodes;
    int right_numNodes;

    /** Caso base **/
    if (!*ppn) {
        return 0;
    }

    left_numNodes = tree_numNodes_rec(pa, &((*ppn)->left));
    right_numNodes = tree_numNodes_rec(pa, &((*ppn)->right));

    return left_numNodes + right_numNodes + 1;
}

Status tree_preOrder(FILE* pf, const Tree* pa)
{
    if (!pf || !pa) {
        return ERR;
    }

    if (tree_isEmpty(pa)) {
        return ERR;
    }

    return tree_preOrder_rec(pf, pa, &(pa->root));
}

Status tree_preOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn)
{
    /** Caso base **/
    if (!*ppn) {
        return OK;
    }

    /** Recursividad */
    pa->print_element_function(pf, (*ppn)->info);
    if ((*ppn)->left) {
        tree_preOrder_rec(pf, pa, &((*ppn)->left));
    }
    if ((*ppn)->right) {
        tree_preOrder_rec(pf, pa, &((*ppn)->right));
    }

    return OK;
}

Status tree_inOrder(FILE* pf, const Tree* pa)
{
    if (!pf || !pa) {
        return ERR;
    }

    if (tree_isEmpty(pa)) {
        return ERR;
    }

    return tree_inOrder_rec(pf, pa, &(pa->root));
}

Status tree_inOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn)
{
    /** Caso base **/
    if (!*ppn) {
        return OK;
    }

    /** Recursividad **/
    if ((*ppn)->left) {
        tree_preOrder_rec(pf, pa, &((*ppn)->left));
    }
    pa->print_element_function(pf, (*ppn)->info);
    if ((*ppn)->right) {
        tree_preOrder_rec(pf, pa, &((*ppn)->right));
    }

    return OK;
}

Status tree_postOrder(FILE* pf, const Tree* pa)
{
    if (!pf || !pa) {
        return ERR;
    }

    if (tree_isEmpty(pa)) {
        return ERR;
    }

    return tree_postOrder_rec(pf, pa, &(pa->root));
}

Status tree_postOrder_rec(FILE* pf, const Tree* pa, NodeBT* const* ppn)
{
    if (!*ppn) {
        return OK;
    }

    /** Recursividad **/
    if ((*ppn)->left) {
        tree_preOrder_rec(pf, pa, &((*ppn)->left));
    }
    if ((*ppn)->right) {
        tree_preOrder_rec(pf, pa, &((*ppn)->right));
    }
    pa->print_element_function(pf, (*ppn)->info);

    return OK;
}
