#include <stdlib.h>
#include <stdio.h>
#include "intarray.h"
#include "tools.h"
#include "jstl.h"
#include "stringarray.h"



int main(int argc, char** argv){
    tools_memory_init();{
    stringarray A = standard_empty_stringarray_create();
    jstl j = regstr_to_jstl("Banane.");
    stringarray_add(A,j);
    j = regstr_to_jstl("Orange.");
    stringarray_add(A,j);
    j = regstr_to_jstl("Framboise.");
    stringarray_add(A,j);
    j = regstr_to_jstl("Figue.");
    stringarray_add(A,j);
    // jstl min = stringarray_get_min(A);
    // stringarray_debug(A);
    // jstl_debug(min);
    // stringarray B = stringarray_clone_using_jstl_clone(A);
    stringarray B = stringarray_sort1(A);
    printf("\n\n");
    stringarray_debug(B);
    stringarray_destroy_using_jstl_destroy(A);
    stringarray_destroy_using_jstl_destroy(B);
    tools_memory_check_at_end_of_app();
    }

}