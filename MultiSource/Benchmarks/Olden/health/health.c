/* For copyright information, see olden_v1.0/COPYRIGHT */

/******************************************************************* 
 *  Health.c : Model of the Columbian Health Care System           *
 *******************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "health.h"
#include <assert.h>

int  max_level;
long max_time;
long long seed;

mm_ptr<struct Village>
alloc_tree(int level, int label, mm_ptr<struct Village> back) {
  if (level == 0)
    return NULL;
  else {
    int i;
    mm_ptr<struct Village> new = NULL;
    mm_ptr<struct Village> fval[4] = {NULL};

    new = mm_alloc<struct Village>(sizeof(struct Village));

    for (i = 3; i >= 0; i--)
      fval[i] = alloc_tree(level - 1, label*4 + i + 1, new); 

    new->back = back;
    new->label = label;
    new->seed = label * (IQ + seed); 
    new->hosp.personnel = (int)pow(2, level - 1);
    new->hosp.free_personnel = new->hosp.personnel;
    new->hosp.num_waiting_patients = 0;
    new->hosp.assess.forward = NULL;
    new->hosp.assess.back = NULL;
    new->hosp.assess.patient = NULL;  /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->hosp.waiting.forward = NULL;
    new->hosp.waiting.back = NULL;
    new->hosp.waiting.patient = NULL; /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->hosp.inside.forward = NULL;
    new->hosp.inside.back = NULL;
    new->hosp.inside.patient = NULL;  /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->hosp.up.forward = NULL;      /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->hosp.up.back = NULL;         /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->hosp.up.patient = NULL;      /* ADDED FOR LLVM [OLDEN BUGS!] */
    new->returned.back = NULL;
    new->returned.forward = NULL;

    for (i = 0; i < 4; i++)
      new->forward[i] = fval[i];

    return new;
  }
}


struct Results get_results(mm_ptr<struct Village> village) {
  int                    i;
  mm_ptr_List            list = NULL;
  mm_ptr<struct Patient> p = NULL;
  struct Results         fval[4];
  struct Results         r1;

  r1.total_hosps = 0.0;
  r1.total_patients = 0.0;
  r1.total_time = 0.0;

  if (village == NULL) return r1;

  for (i = 3; i > 0; i--) {
    mm_ptr<struct Village> V = village->forward[i];
    fval[i] = get_results(V);
  }

  fval[0] = get_results(village->forward[0]);

  for (i = 3; i >= 0; i--) {
    r1.total_hosps    += fval[i].total_hosps;
    r1.total_patients += fval[i].total_patients;
    r1.total_time     += fval[i].total_time;
  }

  list = village->returned.forward;
  while (list != NULL) {
    p = list->patient;
    r1.total_hosps += (float)(p->hosps_visited);
    r1.total_time += (float)(p->time); 
    r1.total_patients += 1.0;
    list = list->forward;
  }

  return r1; 
}

void check_patients_inside(mm_ptr_Village village, mm_ptr_List list)
{
  mm_ptr_List l = NULL;
  mm_ptr<struct Patient> p = NULL;
  int                    t;
  
  while (list != NULL) {
    p = list->patient;
    t = p->time_left;
    p->time_left = t - 1;
    if (p->time_left == 0) {
      t = village->hosp.free_personnel;
      village->hosp.free_personnel = t+1;
      l = &(village->hosp.inside);
      removeList(l, p); 
      l = &(village->returned);
      addList(l, p); }    
    list = list->forward;       /* :) adt_pf detected */
  } 
}

mm_ptr_List check_patients_assess(mm_ptr<struct Village> village,
                                  mm_ptr_List list) {
  float rand;
  mm_ptr<struct Patient> p = NULL;
  mm_ptr_List up = NULL;
  long long s;
  int label, t;

  while (list != NULL) {
    p = list->patient;
    t = p->time_left;
    p->time_left = t - 1;
    label = village->label;
    if (p->time_left == 0) { 
      s = village->seed;
      rand = my_rand(s);
      village->seed = (long long)(rand * IM);
      label = village->label;
      if (rand > 0.1 || label == 0) {
        removeList(&village->hosp.assess, p);
        addList(&village->hosp.inside, p);
        p->time_left = 10;
        t = p->time;
        p->time = t + 10; 
      } else {
        t = village->hosp.free_personnel;
        village->hosp.free_personnel = t+1;
        
        removeList(&village->hosp.assess, p);
        up = &village->hosp.up;
        addList(up, p);
      }
    }
    
    list = list->forward;             /* :) adt_pf detected */
  }
  return up;
}

void check_patients_waiting(mm_ptr<struct Village> village, mm_ptr_List list) {
  int i, t;
  mm_ptr<struct Patient> p = NULL;
  
  while (list != NULL) {
    i = village->hosp.free_personnel;
    p = list->patient;
    if (i > 0) {
      t = village->hosp.free_personnel;
      village->hosp.free_personnel = t-1;
      p->time_left = 3;
      t = p->time;
      p->time = t + 3;

      removeList(&village->hosp.waiting, p);
      addList(&village->hosp.assess, p); }
    else {
      t = p->time;
      p->time = t + 1; }
    list = list->forward; }         /* :) adt_pf detected */
}


void put_in_hosp(mm_ptr_Hosp hosp, mm_ptr<struct Patient> patient) {
  int t = patient->hosps_visited;

  patient->hosps_visited = t + 1;
  if (hosp->free_personnel > 0) {
    t = hosp->free_personnel;
    hosp->free_personnel = t-1;
    addList(&hosp->assess, patient); 
    patient->time_left = 3;
    t = patient->time;
    patient->time = t + 3; 
  } else {
    addList(&hosp->waiting, patient); 
  }
}

mm_ptr<struct Patient> generate_patient(mm_ptr<struct Village> village)
{
  long long       s,newseed;
  mm_ptr<struct Patient> patient = NULL;
  float rand;
  int label;
  
  s = village->seed;
  rand = my_rand(s);
  village->seed = (long long)(rand * IM);
  newseed = village->seed;
  label = village->label;
  if (rand > 0.666) {
    patient = mm_alloc<struct Patient>(sizeof(struct Patient));
    patient->hosps_visited = 0;
    patient->time = 0;
    patient->time_left = 0;
    patient->home_village = village; 
    return patient;
  }
  /* sz: Temporary walk around for return NULL */
  return patient;
#if 0
  return NULL
#endif
}

int main(int argc, char *argv[]) 
{ 
  struct Results         results;
  mm_ptr<struct Village> top = NULL;
  int                    i;
  float total_time, total_patients, total_hosps;  
  
  dealwithargs(argc, argv);
  top = alloc_tree(max_level, 0, top);
  
  chatting("\n\n    Columbian Health Care Simulator\n\n");
  chatting("Working...\n");
  
  for (i = 0; i < max_time; i++) {
    if ((i % 50) == 0) chatting("%d\n", i);
    sim(top);
  }                          /* :) adt_pf detected */
  
  printf("Getting Results\n");
  results = get_results(top);              /* :) adt_pf detected */
  total_patients = results.total_patients;
  total_time = results.total_time;
  total_hosps = results.total_hosps;

  chatting("Done.\n\n");
  chatting("# of people treated:              %f people\n",
	   total_patients);
  chatting("Average length of stay:           %0.2f time units\n", 
	   total_time / total_patients);
  chatting("Average # of hospitals visited:   %f hospitals\n\n",
	   total_hosps / total_patients);

  return 0;
}


mm_ptr_List sim(mm_ptr<struct Village> village)
{
  int                    i;
  mm_ptr<struct Patient> patient = NULL;
  mm_ptr_List            l = NULL, up = NULL;
  mm_ptr_Hosp            h = NULL;
  mm_ptr_List            val[4] = { NULL };
  
  int label;
  if (village == NULL) return NULL;
 
  label = village->label;

  for (i = 3; i > 0; i--) {
    mm_ptr<struct Village> V = village->forward[i];
    mm_ptr_List L = sim(V);
    val[i] = L;
  }

  val[0] = sim(village->forward[0]);
  h = &village->hosp;

  for (i = 3; i >= 0; i--) {
    mm_ptr_List valI = l = val[i];
    if (l != NULL) {
      l = l->forward;
      while (l != NULL) {
	put_in_hosp(h, l->patient);
	removeList(valI, l->patient);
        l = l->forward;
      }
    }
  }

  check_patients_inside(village, village->hosp.inside.forward);
  up = check_patients_assess(village, village->hosp.assess.forward);
  check_patients_waiting(village, village->hosp.waiting.forward);
  
  /*** Generate new patients ***/  
  if ((patient = generate_patient(village)) != NULL) {  
    label = village->label;
    put_in_hosp(&village->hosp, patient);
  }

  return up;
}
