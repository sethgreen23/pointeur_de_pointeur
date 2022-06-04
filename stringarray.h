#ifndef __stringarray_H__
#define __stringarray_H__


#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "jstl.h"
#include "intarray.h"
typedef char* regstr;
typedef struct _stringarray* stringarray;
typedef struct _stringarray S_stringarray;

struct _stringarray{
  jstl* data;
  int alloc;
  int len;
};
#define STANDARD_TAB_ALLOC 8
#define STANDARD_TAB_LENGTH 8

/*prototypes des fonction de manipulation des stringarrays*/

stringarray stringarray_create(int len);
void stringarray_debug_with_delimiter(stringarray tab, char* delimiter);
void stringarray_debug(stringarray tab);
stringarray empty_stringarray_create(int allow);
stringarray standard_empty_stringarray_create(void);
/* desalloue la struct _stringarray et le tableau de jstl */
void stringarray_destroy(stringarray tab);
/*desalloue les jstl de tab en plus de la struct et du tableau de stringarrayl*/
void stringarray_destroy_using_jstl_destroy(stringarray tab);
jstl stringarray_get(stringarray tab, int index);
void stringarray_set(stringarray tab, int index, jstl value);
void ext_stringarray_set(stringarray tab, int index, jstl value);
void stringarray_add(stringarray tab, jstl value);
void stringarray_resise(stringarray tab, int new_alloc);
int stringarray_len(stringarray tab);
/*
retourne lindex de la premiere occurence dans le tab
dune jstl qui est equl a value
*/
int stringarray_search(stringarray tab, jstl value);
int stringarray_nb_occurences(stringarray tab, jstl value);
stringarray stringarray_sort1(stringarray tab);
stringarray stringarray_clone_aux(stringarray tab,int clone);
stringarray stringarray_clone(stringarray tab);
stringarray stringarray_clone_using_jstl_clone(stringarray tab);

stringarray stringarray_concat_aux(stringarray T1, stringarray T2, int clone);
/*
returne le resultat de la concatenatin 
de T1 et T2 les jstl de T1 et T2 clonnée
*/
stringarray stringarray_concat (stringarray T1, stringarray T2);
stringarray stringarray_concat_using_jstl_clone(stringarray T1, stringarray T2);
jstl stringarray_get_min(stringarray tab);
int stringarray_get_index_of_min(stringarray tab);
int stringarray_get_index_of_min_from(stringarray tab, int n);

void stringarray_delete(stringarray tab, int index);
void UNSORTED_stringarray_delete(stringarray tab, int index);
void D_stringarray_concat(stringarray t,stringarray s);
int stringarray_equal (stringarray j1,stringarray j2);





#endif