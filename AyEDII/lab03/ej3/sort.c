/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool res = true;

    if (x.rank > y.rank)
    {
        res = false;
    }
    
    return res;
}


static void swap(player_t a[], unsigned int i, unsigned int j) {
    player_t tmp= a[j];
    a[j] = a[i];
    a[i] = tmp;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void sort(player_t a[], unsigned int length) {
    for (unsigned int j = 1; j < length; j++)
    {
        unsigned int i = j;

        while (i>0 && goes_before(a[i],a[i-1]))
        {
            swap(a,i,i-1);
            --i;
        }

        assert(array_is_sorted(a,j));
    }
}