#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {

    bool res = false;

    if (abb_is_empty(tree))
    {
        res = (tree == NULL);
    } else {

        bool res_left = true;
        bool res_right = true;

        if (tree->left != NULL)
        {
            res_left = elem_less(abb_max(tree->left), tree->elem);
        }
            
        if (tree->right != NULL)
        {
            res_right = elem_less(tree->elem, abb_min(tree->right));
        }

        res = res_left && res_right;
    }   

    return res;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (abb_is_empty(tree))
    {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else {
        if (elem_less(e, tree->elem))
        {
            tree->left = abb_add(tree->left, e);
        } else if (elem_less(tree->elem, e)) {
            tree->right = abb_add(tree->right, e);
        }
    }
    
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty = (tree == NULL);
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));

    if (elem_eq(e, tree->elem))
    {
        exists = true;
    } else if (elem_less(e, tree->elem) && tree->left != NULL) 
    {
        exists = abb_exists(tree->left, e);
    } else if (elem_less(tree->elem, e) && tree->right != NULL) 
    {
        exists = abb_exists(tree->right, e);
    }


    assert(abb_length(tree)!=0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    
    if (!abb_is_empty(tree))
    {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    
    
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree == NULL) {
        return NULL;
    }

    if (elem_less(e, tree->elem)) {
        tree->left = abb_remove(tree->left, e);
    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_remove(tree->right, e);
    } else {
        abb aux = tree;

        if (tree->left == NULL) {
            tree = tree->right;
            free(aux);
        } else if (tree->right == NULL) {
            tree = tree->left;
            free(aux);
        } else { 
            abb min_right = tree->right;
            while (min_right->left != NULL) {
                min_right = min_right->left;
            }

            tree->elem = min_right->elem;
            tree->right = abb_remove(tree->right, min_right->elem);
        }
    }

    assert(invrep(tree));
    return tree;
}



abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while (aux->right != NULL)
    {
        aux = aux->right;
    }

    max_e = aux->elem;
    
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while (aux->left != NULL)
    {
        aux = aux->left;
    }

    min_e = aux->elem;
    
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));

    if (tree != NULL) {
        if (ord == ABB_PRE_ORDER) {
            printf("%d ", tree->elem);
        }

        abb_dump(tree->left, ord);
        
        if (ord == ABB_IN_ORDER) {
            printf("%d ", tree->elem);
        }

        abb_dump(tree->right, ord);

        if (ord == ABB_POST_ORDER) {
            printf("%d ", tree->elem);
        }
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (tree != NULL) {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

