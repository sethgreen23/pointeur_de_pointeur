#include <stdlib.h>
#include <stdio.h>
#include "intarray.h"
#include "tools.h"
//Note!! the arrays wont be with size 0
//create and empty intarray with both len and alloc set to the parameter len
intarray intarray_create(int len){
  if(len<=0){
    printf("intarray_create: Length cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    len = STANDARD_TAB_LENGTH;
  }
  intarray p = malloc(sizeof(struct _intarray));
  p->len=len;
  p->alloc=len;
  p->data = malloc(sizeof(int)*len);
  int i;
  for(int i=0;i<len;i++){
    p->data[i]=0;
  }
  // printf("empty_intarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
// display the array
void intarray_debug(intarray tab){
  int i;
  printf("intarray_debug: Length %d, Alloc %d.\n",tab->len,tab->alloc);
  printf("[ ");
  for(i=0;i<tab->len;i++){
    if(i!=tab->len-1)
      printf("%d, ",tab->data[i]);
    else
      printf("%d",tab->data[i]);
  }
  printf(" ]");
}
// create an empty intarray with alloc set to the parameter value and as len=0
intarray empty_intarray_create(int alloc){
  if(alloc<=0){
    printf("empty_intarray_create: Alloc cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    alloc = STANDARD_TAB_ALLOC;
  }
  intarray p = malloc(sizeof(struct _intarray));
  p->len=0;
  p->alloc=alloc;
  p->data = malloc(sizeof(int)*alloc);
  int i;
  for(int i=0;i<alloc;i++){
    p->data[i]=0;
  }
  // printf("empty_intarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
//create an empty intarray with alloc equal to 0 it is like that
intarray standard_empty_intarray_create(void){
  intarray p = empty_intarray_create(STANDARD_TAB_ALLOC);
  // printf("empty_intarray_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
// free the memory allocated for both the intarray and data array
void intarray_destroy(intarray tab){
  free(tab->data);
  free(tab);
}
// get the element in the data array at the position index
int intarray_get(intarray tab, int index){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    printf("You will get the index 0\n");
    return 0;
  }
  return tab->data[index];
}
// set the value in the data array at position index
// the index need to be less then the lenth
void intarray_set(intarray tab, int index, int value){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    return;
  }
  tab->data[index]=value;
}
// same as the legacy intarray_set 
// the difference is that you can place the value 
// in any position you wouldlike because the array is resizable
void ext_intarray_set(intarray tab, int index, int value){
  if(index<0){
    printf("The index %d cant be negative\n",index);
    return;
  }
  if(index<tab->len){
    tab->data[index]=value;
    return;
  }
  if(index>=tab->alloc)
    intarray_resise(tab,2*tab->alloc+1);
  for(int i=tab->len;i<tab->alloc;i++){
    tab->data[i]=0;
  }
  tab->data[index]=value;
  if(index>=tab->len)
    tab->len++;
}
// add the element at the end of the array
void intarray_add(intarray tab, int value){
  ext_intarray_set(tab,tab->len,value);
}
// resize the  array with 2*old_alloc+1
void intarray_resise(intarray tab, int new_alloc){
  int* new_data = malloc(sizeof(int)*new_alloc);
  for(int i=0;i<tab->len;i++){
    new_data[i]=tab->data[i];
  }
  tab->alloc=new_alloc;
  free(tab->data);
  tab->data = new_data;

}
// return the length of the array
int intarray_len(intarray tab){
  return tab->len;
}
// print the positive values in the array
void intarray_print_positive_values(intarray tab){
  printf("[ ");
  for(int i=0;i<tab->len;i++){
    if(tab->data[i]>0){
      int count = intarray_count_positive_numbers(tab,i+1);
      if(count>0){
        printf("%d, ",tab->data[i]);
      }else{
        printf("%d",tab->data[i]);
      }
    }
  }
  printf(" ]");
}
// search the value in the array
int intarray_search(intarray tab, int n){
  int i;
  for(i =0;i<tab->len;i++){
    if(tab->data[i]==n)
      return i;
  }
  printf("The element %d doenst exist in the array you get the index 0\n",n);
  return 0;
}
// search the occurence of the value in the array
int intarray_nb_occurences(intarray tab, int n){
  int count=0,i;
  for(i =0 ;i<tab->len;i++){
    if(tab->data[i]==n)
      count++;
  }
  return count;
}
// sort the array
intarray intarray_sort1(intarray tab){
  intarray clone = intarray_clone(tab);
  for(int i=0;i<clone->len-1;i++){
    int index = intarray_get_index_of_min_from(clone,i);
    interchange_values(clone->data+index,clone->data+i);//&clone->data[i]
  }
  return clone;
}
// clone the array
intarray intarray_clone(intarray tab){
  intarray clone = empty_intarray_create(tab->alloc);
  intarray_clone_tables(tab,clone);
  return clone;
}
// sum the element in the array
int intarray_sum(intarray tab){
  int sum=0;
  for(int i=0;i<tab->len;i++){
    sum+=tab->data[i];
  }
  return sum;
}
// calculate the average of the values in the array
float intarray_average(intarray tab){
  return intarray_sum(tab)/(tab->len*1.0);
}
// calculate the median value of the array
float intarray_median(intarray tab){
  intarray clone = intarray_sort1(tab);
  int middle_index = clone->len/2;
  
  if(clone->len%2==1){ 
    return clone->data[middle_index]/2.0;
  }else{
    return (clone->data[middle_index]+clone->data[middle_index-1])/2.0;
  }
}
// concatenate two inarray
intarray intarray_concat (intarray T1, intarray T2){
  intarray tab = empty_intarray_create(2*(T1->alloc+T2->alloc));
  int i,j,k;
  for(i=0;i<T1->len;i++){
    intarray_add(tab,T1->data[i]);
  }
  for(j=0;j<T2->len;j++){
    intarray_add(tab,T2->data[j]);
  }
  return tab;
}
// return the min value in the array
int intarray_get_min(intarray tab){
  return tab->data[intarray_get_index_of_min(tab)];
}
// get the index of the min in the intarray
int intarray_get_index_of_min(intarray tab){
  return intarray_get_index_of_min_from(tab,0);
}
// get the index of the min in the array starting from a certain position
int intarray_get_index_of_min_from(intarray tab, int n){
  int min=tab->data[n];
  int index=n;
  for(int i=n+1;i<tab->len;i++){
    if(tab->data[i]<min){
      min = tab->data[i];
      index=i;
    }
  }
  return index;
}
// count the number of the positive numbers starting from a certain position
int intarray_count_positive_numbers(intarray tab, int start){
  int count =0;
  for(int i=start;i<tab->len;i++){
    if(tab->data[i]>0)
      count++;
  }
  return count;
}
// clone the table values
void intarray_clone_tables(intarray tab, intarray copy){
  int i;
  for(i=0;i<tab->len;i++){
    intarray_add(copy,tab->data[i]);
  }
}
// delete the element in the array and keep the order
void intarray_delete(intarray tab, int index){
  if(index < 0){
    printf("The index cant be negative.\n");
    return;
  }
  if(index>=tab->len){
    printf("The index need to be between the 0 and %d\n",tab->len-1);
    return;
  }
  int i;
  for(i = index+1;i<tab->len;i++){
    tab->data[i-1]=tab->data[i];
  }
  tab->len--;
}
// delete the element in the array 
void UNSORTED_intarray_delete(intarray tab, int index){
  if(index < 0){
    printf("The index cant be negative.\n");
    return;
  }
  if(index>=tab->len){
    printf("The index need to be between the 0 and %d\n",tab->len-1);
    return;
  }
  tab->data[index]=tab->data[tab->len-1];
  tab->len--;
}
void from_char_intarray(intarray tab, char** charTab, int length){
  for(int i=1,j=0;i<length;i++){
    int* ok = malloc(sizeof(int));
    int integer = safe_string_to_int(charTab[i],ok);
    if(*ok==1){
      intarray_add(tab,integer);
    }
    free(ok);
  }
}