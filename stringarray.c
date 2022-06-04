#include <stdlib.h>
#include <stdio.h>
#include "stringarray.h"
#include "jstl.h"
#include "tools.h"
#include "intarray.h"
//Note!! the arrays wont be with size 0
//create and empty stringarray with both len and alloc set to the parameter len
stringarray stringarray_create(int len){
  if(len<=0){
    printf("stringarray_create: Length cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    len = STANDARD_TAB_LENGTH;
  }
  stringarray p = tools_malloc(sizeof(struct _stringarray));
  p->len=0;
  p->alloc=len;
  p->data = tools_malloc(sizeof(jstl)*len);
  int i;
  for(int i=0;i<len;i++){
    p->data[i]=NULL;
  }
  // printf("empty_stringarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
void stringarray_debug_with_delimiter(stringarray tab, char* delimiter){
  int i;
  // printf("stringarray_debug: Length %d, Alloc %d.\n",tab->len,tab->alloc);
  for(i=0;i<tab->len;i++){
    jstl_debug(tab->data[i]);
    printf(delimiter);
  }
}
// display the array
void stringarray_debug(stringarray tab){
 stringarray_debug_with_delimiter(tab, "\n");
}
// create an empty stringarray with alloc set to the parameter value and as len=0
stringarray empty_stringarray_create(int alloc){
  if(alloc<=0){
    printf("empty_stringarray_create: Alloc cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    alloc = STANDARD_TAB_ALLOC;
  }
  stringarray p = tools_malloc(sizeof(struct _stringarray));
  p->len=0;
  p->alloc=alloc;
  p->data = tools_malloc(sizeof(jstl)*alloc);
  int i;
  for(int i=0;i<alloc;i++){
    p->data[i]=NULL;
  }
  // printf("empty_stringarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
//create an empty stringarray with alloc equal to 0 it is like that
stringarray standard_empty_stringarray_create(void){
  stringarray p = empty_stringarray_create(STANDARD_TAB_ALLOC);
  // printf("empty_stringarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
// destructeur leger
void stringarray_destroy(stringarray tab){
  tools_free(tab->data,sizeof(jstl)*tab->alloc);
  tools_free(tab,sizeof(struct _stringarray));
}
// destricteur lourd
void stringarray_destroy_using_jstl_destroy(stringarray tab){
  for(int i=0;i<tab->len;i++)
    jstl_destroy(tab->data[i]);
  
  stringarray_destroy(tab);
}
// /*desalloue les jstl de tab en plus de la struct et du tableau de jstrl*/
// void stringarray_destroy_using_jstl_destroy(stringarray tab){
//   tools_free(tab->data);
//   tools_free(tab);
// }
// get the element in the data array at the position index
jstl stringarray_get(stringarray tab, int index){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    printf("You will get the index 0\n");
    return NULL;
  }
  return tab->data[index];
}
// set the value in the data array at position index
// the index need to be less then the lenth
void stringarray_set(stringarray tab, int index, jstl value){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    return;
  }
  if(tab->data[index]!=NULL)
    jstl_destroy(tab->data[index]);
  tab->data[index]=value;
}
// same as the legacy stringarray_set 
// the difference is that you can place the value 
// in any position you wouldlike because the array is resizable
void ext_stringarray_set(stringarray tab, int index, jstl value){
  if(index<0){
    printf("The index %d cant be negative\n",index);
    return;
  }
  if(index<tab->len){
    tab->data[index]=value;
    return;
  }
  if(index>=tab->alloc)
    stringarray_resise(tab,2*tab->alloc+1);
  for(int i=tab->len;i<tab->alloc;i++){
    tab->data[i]=empty_jstl_create(1);
  }
  if(tab->data[index]!=NULL)
    jstl_destroy(tab->data[index]);
  tab->data[index]=value;
  if(index>=tab->len)
    tab->len++;
}
// add the element at the end of the array
void stringarray_add(stringarray tab, jstl value){
  ext_stringarray_set(tab,tab->len,value);
}
// resize the  array with 2*old_alloc+1
void stringarray_resise(stringarray tab, int new_alloc){
  jstl* new_data = tools_malloc(sizeof(jstl)*new_alloc);
  for(int i=0;i<tab->len;i++){
    new_data[i]=tab->data[i];
  }
  
  tools_free(tab->data, sizeof(jstl)*tab->alloc);
  tab->alloc=new_alloc;
  tab->data = new_data;

}
// return the length of the array
int stringarray_len(stringarray tab){
  return tab->len;
}

// search the value in the array
int stringarray_search(stringarray tab, jstl n){
  int i;
  for(i =0;i<tab->len;i++){
    if(jstl_equal(tab->data[i],n))
      return i;
  }
  printf("The element %d doenst exist in the array you get the index 0\n",n);
  return 0;
}
// search the occurence of the value in the array
int stringarray_nb_occurences(stringarray tab, jstl n){
  int count=0,i;
  for(i =0 ;i<tab->len;i++){
    if(jstl_equal(tab->data[i],n) )
      count++;
  }
  return count;
}
// sort the array
stringarray stringarray_sort1(stringarray tab){
  stringarray clone =  stringarray_clone_using_jstl_clone(tab);
  for(int i=0;i<clone->len-1;i++){
    int index = stringarray_get_index_of_min_from(clone,i);
    jstl tmp = clone->data[i];
    clone->data[i]=clone->data[index];
    clone->data[index]=tmp;
  }
  return clone;
}
// clone the array
stringarray stringarray_clone_aux(stringarray tab, int clone){
  stringarray copy = empty_stringarray_create(tab->len);
  int i;
  for(i=0;i<tab->len;i++){
    if(clone)
      stringarray_add(copy,jstl_clone(tab->data[i]));
    else
      copy->data[i]=tab->data[i];
    
  }
  stringarray_debug(copy);
  return copy;
}
stringarray stringarray_clone(stringarray tab){
  return stringarray_clone_aux(tab,0);
}
stringarray stringarray_clone_using_jstl_clone(stringarray tab){
  return stringarray_clone_aux(tab,1);
}
stringarray stringarray_concat_aux(stringarray T1, stringarray T2, int clone){
  stringarray T = stringarray_create(T1->len+T2->len);
  int i, j=0;

  for(i=0;i<T1->len;i++){
    if(clone)
      T->data[j]=jstl_clone(T1->data[i]);
    else
      T->data[j]=T1->data[i];
    j++;
  }
  for(i=0;i<T2->len;i++){
    if(clone)
      T->data[j]=jstl_clone(T2->data[i]);
    else
      T->data[j]=T2->data[i];
    j++;
  }
  return T;
}
stringarray stringarray_concat_using_jstl_clone(stringarray T1,stringarray T2){
  return stringarray_concat_aux(T1,T2,1);
}
// concatenate two inarray
stringarray stringarray_concat (stringarray T1, stringarray T2){
  return stringarray_concat_aux(T1,T2,0);
}
/*Ajoute a la fin de T1 des clone des jstr de T2 en
  respectant l'ordre de ces derniers.
  le contenue de T2 n'est pas modifie
 */
void D_stringarray_concat(stringarray t,stringarray s){
  for(int i=0;i<s->len;i++)
    stringarray_add(t,jstl_clone(s->data[i]));
  
}
jstl stringarray_get_min(stringarray tab){
  return tab->data[stringarray_get_index_of_min(tab)];
}
// get the index of the min in the stringarray
int stringarray_get_index_of_min(stringarray tab){
  return stringarray_get_index_of_min_from(tab,0);
}
// get the index of the min in the array starting from a certain position
int stringarray_get_index_of_min_from(stringarray tab, int n){
  jstl min=tab->data[n];
  int index=n;
  for(int i=n+1;i<tab->len;i++){
    if(jstl_compare(tab->data[i],min)==-1){
      min = tab->data[i];
      index=i;
    }
  }
  return index;
}
// count the number of the positive numbers starting from a certain position


// delete the element in the array and keep the order
void stringarray_delete(stringarray tab, int index){
  if(index < 0){
    printf("The index cant be negative.\n");
    return;
  }
  if(index>=tab->len){
    printf("The index need to be between the 0 and %d\n",tab->len-1);
    return;
  }
  jstl_destroy(tab->data[index]);
  int i;
  for(i = index+1;i<tab->len;i++){
    tab->data[i-1]=tab->data[i];
  }
  tab->len--;
}
// delete the element in the array 
void UNSORTED_stringarray_delete(stringarray tab, int index){
  if(index < 0){
    printf("The index cant be negative.\n");
    return;
  }
  if(index>=tab->len){
    printf("The index need to be between the 0 and %d\n",tab->len-1);
    return;
  }
  jstl_destroy(tab->data[index]);
  tab->data[index]=tab->data[tab->len-1];
  tab->len--;
}

//correction de l'instructeur
// exercice 0

// exercice 2
int stringarray_equal (stringarray j1,stringarray j2){
  if(j1->len!=j2->len)
    return 0;
  
  int i;
  for(i=0;i<j1->len;i++){
    if(jstl_equal(j1->data[i],j2->data[i])==0)
      return 0;
  }
  return 1;
}



