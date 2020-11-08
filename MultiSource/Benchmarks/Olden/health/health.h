/* For copyright information, see olden_v1.0/COPYRIGHT */

/****************************************************************
 * health.h: header file for health.c                           *
 ****************************************************************/


#ifndef _HEALTH
#define _HEALTH

#include <stdio.h>
#include <stdlib.h>

#include "safe_mm_checked.h"

#define chatting printf

#define IA 16807
#define IM 2147483647
#define AM (1.0 / IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

extern int  max_level;
extern long max_time;
extern long long seed;

struct Results {
  float                   total_patients;
  float                   total_time;
  float                   total_hosps; 
};

struct Patient {
  int                    hosps_visited;
  int                    time;
  int                    time_left;
  mm_ptr<struct Village> home_village;
};

struct List {
  mm_ptr<struct List>    forward;
  mm_ptr<struct Patient> patient;
  mm_ptr<struct List>    back;
};

struct Hosp {
#if 1
  int                    personnel; 
  int                    free_personnel; 
  int                    num_waiting_patients; 
  struct List            waiting; 
  struct List            assess; 
  struct List            inside;
  struct List            up;
#else
  int                    free_personnel; 
  struct List            waiting;
  struct List            assess;
  struct List            inside;
  struct List            up;
  int                    personnel; 
  int                    num_waiting_patients; 
#endif
};
 
struct Village {
#if 1
  mm_ptr<struct Village> forward[4];
  mm_ptr<struct Village> back;
  struct List            returned;
  struct Hosp            hosp;   
  int                    label;
  long long              seed;
#else
  struct Hosp            hosp;   
  long                   seed;
  mm_ptr<struct Village> forward[4];
  int                    label;
  struct List            returned;
  mm_ptr<struct Village> back;
#endif
};

typedef mm_ptr<struct List> mm_ptr_List;
typedef mm_ptr<struct Village> mm_ptr_Village;
typedef mm_ptr<struct Patient> mm_ptr_Patient;
typedef mm_ptr<struct Hosp> mm_ptr_Hosp;

mm_ptr<struct Village>
alloc_tree(int level, int label, mm_ptr<struct Village> back);
void dealwithargs(int argc, char *argv[]);
float my_rand(long long idum);
mm_ptr<struct Patient> generate_patient(mm_ptr<struct Village> village);
void put_in_hosp(mm_ptr_Hosp hosp, mm_ptr<struct Patient> patient);
void addList(mm_ptr_List list, mm_ptr<struct Patient> patient);
void removeList(mm_ptr_List list, mm_ptr<struct Patient> patient);
mm_ptr_List sim(mm_ptr<struct Village> village);
void check_patients_inside(mm_ptr<struct Village> village, mm_ptr_List list);
mm_ptr_List check_patients_assess(mm_ptr<struct Village> village,
                                  mm_ptr_List list);
void check_patients_waiting(mm_ptr<struct Village> village, mm_ptr_List list);
float get_num_people(mm_ptr<struct Village> village);
float get_total_time(mm_ptr<struct Village> village);
float get_total_hosps(mm_ptr<struct Village> village);
struct Results get_results(mm_ptr<struct Village> village);

#endif

