/* For copyright information, see olden_v1.0/COPYRIGHT */

/* =============== NODE STRUCTURE =================== */

#include "safe_mm_checked.h"

typedef struct node HANDLE;

struct node { 
  int value;
  mm_ptr<HANDLE> left;
  mm_ptr<HANDLE> right;
};


typedef struct future_cell_int{
  mm_ptr<HANDLE> value;
} future_cell_int;

extern void *malloc(unsigned);

#if 0
#define NIL ((HANDLE *) 0)
#endif
#define NIL NULL
