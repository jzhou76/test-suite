/* For copyright information, see olden_v1.0/COPYRIGHT */
#ifdef TORONTO
extern int NumNodes;
#define chatting      printf
#endif


#ifndef TORONTO
#include <cm/cmmd.h>
#ifdef FUTURES
#include "future-cell.h"
#endif
#include "mem-ref.h"
#endif

#include "safe_mm_checked.h"

typedef enum {black, white, grey} Color;
typedef enum {northwest, northeast, southwest, southeast} ChildType;
typedef enum {north, east, south, west} Direction;


typedef struct quad_struct {
  Color color;
  ChildType childtype;

#ifndef TORONTO
  struct quad_struct *nw {50};
  struct quad_struct *ne {50};
  struct quad_struct *sw {50};
  struct quad_struct *se {50};
  struct quad_struct *parent {50};
#else
  mm_ptr<struct quad_struct> nw;
  mm_ptr<struct quad_struct> ne;
  mm_ptr<struct quad_struct> sw;
  mm_ptr<struct quad_struct> se;
  mm_ptr<struct quad_struct> parent;
#endif

} quad_struct;

typedef mm_ptr<quad_struct> QuadTree;

QuadTree MakeTree(int size, int center_x, int center_y, int lo_proc,
                  int hi_proc, QuadTree parent, ChildType ct, int level);










