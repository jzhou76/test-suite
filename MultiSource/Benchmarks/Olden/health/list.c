/* For copyright information, see olden_v1.0/COPYRIGHT */

/********************************************************************
 *  List.c:  Handles lists.                                         *
 *           To be used with health.c                               *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "health.h"

void addList(mm_ptr_List list, mm_ptr_Patient patient) {
  mm_ptr_List b = NULL;

  while (list != NULL) {
    b = list;
    list = list->forward; }

  list = mm_alloc<struct List>(sizeof(struct List));
  list->patient = patient;
  list->forward = NULL;
  list->back = b;
  b->forward = list;
}

void removeList(mm_ptr_List list, mm_ptr<struct Patient> patient) {
  mm_ptr_List l1 = NULL, l2 = NULL;
  mm_ptr_Patient p = NULL;

  p = list->patient;
  while(p != patient) {
      list = list->forward;
      p = list->patient;
  }

  l1 = list->back;
  l2 = list->forward;
  l1->forward = l2;
  if (list->forward != NULL) {
    l1 = list->forward;
    l2 = list->back;
    l1->back = l2;
  }
  /*free(list);*/
}
