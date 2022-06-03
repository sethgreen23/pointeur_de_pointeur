#ifndef __stringarray_H__
#define __stringarray_H__


#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "intarray.h"
typedef char* regstr;
typedef struct _stringarray* stringarray;
typedef struct _stringarray S_stringarray;

struct _stringarray{
  char* data;
  int alloc;
  int len;
};
#define STANDARD_TAB_ALLOC 8
#define STANDARD_TAB_LENGTH 8

/*prototypes des fonction de manipulation des stringarrays*/

stringarray stringarray_create(int len);
void stringarray_debug(stringarray tab);
stringarray empty_stringarray_create(int allow);
stringarray standard_empty_stringarray_create(void);
void stringarray_destroy(stringarray tab);
int stringarray_get(stringarray tab, int index);
void stringarray_set(stringarray tab, int index, char value);
void ext_stringarray_set(stringarray tab, int index, char value);
void stringarray_add(stringarray tab, char value);
void stringarray_resise(stringarray tab, int new_alloc);
int stringarray_len(stringarray tab);
void stringarray_print_positive_values(stringarray tab);
int stringarray_search(stringarray tab, char value);
int stringarray_nb_occurences(stringarray tab, char value);
stringarray stringarray_sort1(stringarray tab);
stringarray stringarray_clone(stringarray tab);
int stringarray_sum(stringarray tab);
float stringarray_average(stringarray tab);
float stringarray_median(stringarray tab);
stringarray stringarray_concat (stringarray T1, stringarray T2);
int stringarray_get_min(stringarray tab);
int stringarray_get_index_of_min(stringarray tab);
int stringarray_get_index_of_min_from(stringarray tab, int n);
int stringarray_count_positive_numbers(stringarray tab, int start);
void stringarray_clone_tables(stringarray tab, stringarray copy);
void stringarray_delete(stringarray tab, int index);
void UNSORTED_stringarray_delete(stringarray tab, int index);
void from_char_stringarray(stringarray tab, char** charTab, int length);
stringarray regstr_to_stringarray(regstr str);
regstr stringarray_to_regstr(stringarray tab);
int stringarray_equal_substr(stringarray j1,int s1, int e1,stringarray j2, int s2);
void stringarray_concatenation_argvs(stringarray tab, char** values, int length);
stringarray stringarray_substr(stringarray tab, int s1, int e1);
/*My implementation for the exercices*/
void MY_stringarray_concatenation_argvs(stringarray tab, char** values, int length);
void D_stringarray_concat(stringarray t,stringarray s);
int stringarray_equal_substr(stringarray j1,int s1, int e1,stringarray j2, int s2);
int stringarray_equal (stringarray j1,stringarray j2);
intarray stringarray_find_substr_indices(stringarray tab, stringarray sub);
intarray stringarray_find_proper_substr_indices(stringarray tab, stringarray sub);
int stringarray_compare(stringarray j1, stringarray j2);


/*MY Emplementation of the funtiontions*/
int MY_stringarray_equal_substr(stringarray j1,int s1, int e1,stringarray j2, int s2);
int MY_stringarray_equal (stringarray j1,stringarray j2);
intarray MY_stringarray_find_substr_indices(stringarray tab, stringarray sub);
intarray MY_stringarray_find_proper_substr_indices(stringarray tab, stringarray sub);
int MY_jstr_compare(stringarray tab,stringarray lab);
/*Helper functions*/
stringarray MY_stringarray_substr(stringarray tab, int s1, int e1);
void MY_stringarray_equal_substr_errors(stringarray j1,int s1, int e1,stringarray j2, int s2,int* ok);
void MY_stringarray_substr_errors(stringarray j1,int s1, int e1,int* ok);
int MY_stringarray_equal (stringarray j1,stringarray j2);
intarray MY_stringarray_find_substr_indices(stringarray tab, stringarray sub);
intarray MY_stringarray_find_proper_substr_indices(stringarray tab, stringarray sub);
int MY_jstr_compare(stringarray j1,stringarray j2);



#endif