/* For copyright information, see olden_v1.0/COPYRIGHT */

/* tree-alloc.c
 */

#ifndef TORONTO
#include "mem-ref.h"
#include "future-cell.h"
#endif

#include "tree.h"
#if 0
extern void *malloc(unsigned);
#endif

tree_p TreeAlloc (int level, int lo, int proc) {
  if (level == 0)
    return NULL;
  else {
    mm_ptr<tree_t> new = NULL, right = NULL, left = NULL;
    new = mm_alloc<tree_t>(sizeof(tree_t));
    left = TreeAlloc(level -1, lo+proc/2, proc/2);
    right=TreeAlloc(level-1,lo,proc/2);
    new->val = 1;
    new->left =  left;
    new->right = right;
    return new;
  }
}
