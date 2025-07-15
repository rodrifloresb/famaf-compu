#include <stdlib.h>
#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool res = (d != NULL);
    return res;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(!invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {

    if (dict == NULL)
    {
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    } else {
        if (key_less(word, dict->key))
        {
            dict->left = dict_add(dict->left, word, def);
        } else if (key_less(dict->key, word)) {
            dict->right = dict_add(dict->right, word, def);
        }
    }

    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def = NULL;

    if (dict_exists(dict, word))
    {
        if (key_eq(word, dict->key))
        {
            def = dict->value;
        } else if (key_less(word, dict->key)) {
            def = dict_search(dict->left, word);
        } else if (key_less(dict->key, word)) {
            def = dict_search(dict->right, word);
        }
    }
    
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool res = false;
    
    if (dict != NULL)
    {
        if (key_eq(word, dict->key))
        {
            res = true;
        } else if (key_less(word, dict->key)) {
            res = dict_exists(dict->left, word);
        } else if (key_less(dict->key, word)) {
            res = dict_exists(dict->right, word);
        }
    }

    return res;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;

    if (dict != NULL)
    {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }

    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    
    if (dict == NULL)
    {
        return NULL;
    }
    
    if (key_less(word, dict->key))
    {
        dict->left = dict_remove(dict->left, word);
    } else if (key_less(dict->key, word)) {
        dict->right = dict_remove(dict->right, word);
    } else {
        dict_t aux = dict;

        if (dict->left == NULL)
        {
            dict = dict->right;
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(aux);

        } else if (dict->right == NULL) {
            dict = dict->left;
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(aux);
        } else {
            dict_t min_right = dict->right;
            while (min_right->left != NULL)
            {
                min_right = min_right->left;
            }
            
            dict->key = min_right->key;
            dict->value = min_right->value;
            dict->right = dict_remove(dict->right, min_right->key);
        }
    }

    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    if (dict == NULL)
    {
        return NULL;
    }
    
    dict->left = dict_remove_all(dict->left);
    dict->right = dict_remove_all(dict->right);


    dict->key = key_destroy(dict->key);
    dict->value = value_destroy(dict->value);
    free(dict);

    dict = NULL;

    return dict;
}

void dict_dump(dict_t dict, FILE *file) {

    if (dict != NULL)
    {
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file,"\n");
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);
    }    
}

dict_t dict_destroy(dict_t dict) {
    dict = dict_remove_all(dict);
    return dict;
}

