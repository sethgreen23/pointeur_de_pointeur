#ifndef __INTARRAY_H__
#define __INTARRAY_H__

#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
typedef struct _intarray* intarray;
typedef struct _intarray S_intarray;

struct _intarray{
  int* data;
  int alloc;
  int len;
};
#define STANDARD_TAB_ALLOC 8
#define STANDARD_TAB_LENGTH 8
/*prototypes des fonction de manipulation des intarrays*/

intarray intarray_create(int len);
void intarray_debug(intarray tab);
intarray empty_intarray_create(int allow);
intarray standard_empty_intarray_create(void);
void intarray_destroy(intarray tab);
int intarray_get(intarray tab, int index);
void intarray_set(intarray tab, int index, int value);
void ext_intarray_set(intarray tab, int index, int value);
void intarray_add(intarray tab, int value);
void intarray_resise(intarray tab, int new_alloc);
int intarray_len(intarray tab);
void intarray_print_positive_values(intarray tab);
int intarray_search(intarray tab, int n);
int intarray_nb_occurences(intarray tab, int n);
intarray intarray_sort1(intarray tab);
intarray intarray_clone(intarray tab);
int intarray_sum(intarray tab);
float intarray_average(intarray tab);
float intarray_median(intarray tab);
intarray intarray_concat (intarray T1, intarray T2);
int intarray_get_min(intarray tab);
int intarray_get_index_of_min(intarray tab);
int intarray_get_index_of_min_from(intarray tab, int n);
int intarray_count_positive_numbers(intarray tab, int start);
void intarray_clone_tables(intarray tab, intarray copy);
void intarray_delete(intarray tab, int index);
void UNSORTED_intarray_delete(intarray tab, int index);
void from_char_intarray(intarray tab, char** charTab, int length);

#endif