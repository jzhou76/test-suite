/* For copyright information, see olden_v1.0/COPYRIGHT */

/* tree.h
 */

#ifdef TORONTO
#include <stdio.h>
#define chatting printf
#define PLAIN
#endif

#include "safe_mm_checked.h"

typedef struct tree {
    int		val;
    /* struct tree *left, *right; */
    mm_ptr<struct tree> left;
    mm_ptr<struct tree> right;
} tree_t;

typedef mm_ptr<tree_t> tree_p;

extern tree_p TreeAlloc (int level, int lo, int hi);
int TreeAdd (tree_p t);







