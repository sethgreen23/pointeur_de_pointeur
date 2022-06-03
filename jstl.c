#include <stdlib.h>
#include <stdio.h>
#include "jstl.h"
#include "intarray.h"
#include "tools.h"
//Note!! the arrays wont be with size 0
//create and empty jstl with both len and alloc set to the parameter len
jstl jstl_create(int len){
  if(len<=0){
    printf("jstl_create: Length cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    len = STANDARD_TAB_LENGTH;
  }
  jstl p = malloc(sizeof(struct _jstl));
  p->len=len;
  p->alloc=len;
  p->data = malloc(sizeof(char)*len);
  int i;
  for(int i=0;i<len;i++){
    p->data[i]=0;
  }
  // printf("empty_jstl_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
// display the array
void jstl_debug(jstl tab){
  int i;
  // printf("jstl_debug: Length %d, Alloc %d.\n",tab->len,tab->alloc);
  for(i=0;i<tab->len;i++){
      printf("%c",tab->data[i]);
  }
}
// create an empty jstl with alloc set to the parameter value and as len=0
jstl empty_jstl_create(int alloc){
  if(alloc<=0){
    printf("empty_jstl_create: Alloc cant be null or negative.\n");
    printf("We create an array with %d length.\n",STANDARD_TAB_LENGTH);
    alloc = STANDARD_TAB_ALLOC;
  }
  jstl p = malloc(sizeof(struct _jstl));
  p->len=0;
  p->alloc=alloc;
  p->data = malloc(sizeof(char)*alloc);
  int i;
  for(int i=0;i<alloc;i++){
    p->data[i]=0;
  }
  // printf("empty_jstl_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
//create an empty jstl with alloc equal to 0 it is like that
jstl standard_empty_jstl_create(void){
  jstl p = empty_jstl_create(STANDARD_TAB_ALLOC);
  // printf("empty_jstl_create: len->%d and alloc->%d\n",p->len,p->alloc);
  return p;
}
// free the memory allocated for both the jstl and data array
void jstl_destroy(jstl tab){
  free(tab->data);
  free(tab);
}
// get the element in the data array at the position index
int jstl_get(jstl tab, int index){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    printf("You will get the index 0\n");
    return 0;
  }
  return tab->data[index];
}
// set the value in the data array at position index
// the index need to be less then the lenth
void jstl_set(jstl tab, int index, char value){
  if(index>tab->len || index<0){
    printf("The index %d is not between 0 and %d.\n",index, tab->len-1);
    return;
  }
  tab->data[index]=value;
}
// same as the legacy jstl_set 
// the difference is that you can place the value 
// in any position you wouldlike because the array is resizable
void ext_jstl_set(jstl tab, int index, char value){
  if(index<0){
    printf("The index %d cant be negative\n",index);
    return;
  }
  if(index<tab->len){
    tab->data[index]=value;
    return;
  }
  if(index>=tab->alloc)
    jstl_resise(tab,2*tab->alloc+1);
  for(int i=tab->len;i<tab->alloc;i++){
    tab->data[i]=0;
  }
  tab->data[index]=value;
  if(index>=tab->len)
    tab->len++;
}
// add the element at the end of the array
void jstl_add(jstl tab, char value){
  ext_jstl_set(tab,tab->len,value);
}
// resize the  array with 2*old_alloc+1
void jstl_resise(jstl tab, int new_alloc){
  char* new_data = malloc(sizeof(char)*new_alloc);
  for(int i=0;i<tab->len;i++){
    new_data[i]=tab->data[i];
  }
  tab->alloc=new_alloc;
  free(tab->data);
  tab->data = new_data;

}
// return the length of the array
int jstl_len(jstl tab){
  return tab->len;
}
// print the positive values in the array
void jstl_print_positive_values(jstl tab){
  printf("[ ");
  for(int i=0;i<tab->len;i++){
    if(((int)tab->data[i])>0){
      int count = jstl_count_positive_numbers(tab,i+1);
      if(count>0){
        printf("%c, ",tab->data[i]);
      }else{
        printf("%c",tab->data[i]);
      }
    }
  }
  printf(" ]");
}
// search the value in the array
int jstl_search(jstl tab, char n){
  int i;
  for(i =0;i<tab->len;i++){
    if(tab->data[i]==n)
      return i;
  }
  printf("The element %d doenst exist in the array you get the index 0\n",n);
  return 0;
}
// search the occurence of the value in the array
int jstl_nb_occurences(jstl tab, char n){
  int count=0,i;
  for(i =0 ;i<tab->len;i++){
    if(tab->data[i]==n)
      count++;
  }
  return count;
}
// sort the array
jstl jstl_sort1(jstl tab){
  jstl clone = jstl_clone(tab);
  for(int i=0;i<clone->len-1;i++){
    int index = jstl_get_index_of_min_from(clone,i);
    character_interchange_values(clone->data+index,clone->data+i);//&clone->data[i]
  }
  return clone;
}
// clone the array
jstl jstl_clone(jstl tab){
  jstl clone = empty_jstl_create(tab->alloc);
  jstl_clone_tables(tab,clone);
  return clone;
}
// sum the element in the array
int jstl_sum(jstl tab){
  int sum=0;
  for(int i=0;i<tab->len;i++){
    sum+=(int)tab->data[i];
  }
  return sum;
}
// calculate the average of the values in the array
float jstl_average(jstl tab){
  return jstl_sum(tab)/(tab->len*1.0);
}
// calculate the median value of the array
float jstl_median(jstl tab){
  jstl clone = jstl_sort1(tab);
  int middle_index = clone->len/2;
  
  if(clone->len%2==1){ 
    return (int)clone->data[middle_index]/2.0;
  }else{
    return (((int)clone->data[middle_index])+((int)clone->data[middle_index-1]))/2.0;
  }
}
// concatenate two inarray
jstl jstl_concat (jstl T1, jstl T2){
  jstl tab = empty_jstl_create(2*(T1->alloc+T2->alloc));
  int i,j,k;
  for(i=0;i<T1->len;i++){
    jstl_add(tab,T1->data[i]);
  }
  for(j=0;j<T2->len;j++){
    jstl_add(tab,T2->data[j]);
  }
  return tab;
}
// return the min value in the array
int jstl_get_min(jstl tab){
  return tab->data[jstl_get_index_of_min(tab)];
}
// get the index of the min in the jstl
int jstl_get_index_of_min(jstl tab){
  return jstl_get_index_of_min_from(tab,0);
}
// get the index of the min in the array starting from a certain position
int jstl_get_index_of_min_from(jstl tab, int n){
  int min=(int)tab->data[n];
  int index=n;
  for(int i=n+1;i<tab->len;i++){
    if(tab->data[i]<min){
      min = (int)tab->data[i];
      index=i;
    }
  }
  return index;
}
// count the number of the positive numbers starting from a certain position
int jstl_count_positive_numbers(jstl tab, int start){
  int count =0;
  for(int i=start;i<tab->len;i++){
    if(tab->data[i]>0)
      count++;
  }
  return count;
}
// clone the table values
void jstl_clone_tables(jstl tab, jstl copy){
  int i;
  for(i=0;i<tab->len;i++){
    jstl_add(copy,tab->data[i]);
  }
}
// delete the element in the array and keep the order
void jstl_delete(jstl tab, int index){
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
void UNSORTED_jstl_delete(jstl tab, int index){
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
void from_char_jstl(jstl tab, char** charTab, int length){
  for(int i=1,j=0;i<length;i++){
    int* ok = malloc(sizeof(int));
    int integer = safe_string_to_int(charTab[i],ok);
    if(*ok==1){
      jstl_add(tab,integer);
    }
    free(ok);
  }
}
// from regst to jstl
jstl regstr_to_jstl(regstr str){
  int len = strlen(str);
  jstl tab = empty_jstl_create(len);
  for(int i=0;str[i]!='\0';i++){
    jstl_add(tab,str[i]);
  }
  return tab;
}
regstr jstl_to_regstr(jstl tab){
  regstr word = malloc(sizeof(char)*tab->len+1);
  int i;
  for(i=0;i<tab->len;i++){
    word[i]=tab->data[i];
  }
  word[i]='\0';
  return word;
}
//correction de l'instructeur
// exercice 0
void D_jstl_concat(jstl t,jstl s){
  for(int i=0;i<s->len;i++)
    jstl_add(t,s->data[i]);
  
}
// exercice 1
int jstl_equal_substr(jstl j1,int s1, int e1,jstl j2, int s2){
  // find length
  int len = e1 - s1 + 1;
  int e2 = len + s2 -1;
  if(s1>e1){
    printf("jstl_equal_substr: s1 is always less the e1. exchange them.\n");
    interchange_values(&s1,&e1);
  }
  if((s1<0) || (s2<0) || (e1>=j1->len) || (s1>=j1->len) || (s2>=j2->len)){
    printf("jstl_equal_substr: out of bounds.s1: %d ; e1: %d\n",s1,e1);
    printf("jstl_equal_substr: out of bounds.s2: %d .\n",s2);
    return 0;
  }
  // if the motif j1 is bigger to be contained in j2
  if(e2>=j2->len){
    return 0;
  }

  for(int i=0;i<len;i++){
    // at any motment we have a difference between the two variables
    if(j1->data[i+s1]!=j2->data[i+s2])
      return 0;
  }
  return 1;
}
// exercice 2
int jstl_equal (jstl j1,jstl j2){
  if(j1->len!=j2->len)
    return 0;
  else
    return jstl_equal_substr(j1,0, j1->len-1,j2, 0);
}
/*
// exercice 3
intarray jstl_find_substr_indices(jstl tab, jstl sub){
  intarray A = standard_empty_intarray_create();
  for(int i=0;i<=tab->len-sub->len;i++){
    if(jstl_equal_substr(tab,i,i+sub->len-1,sub,0))
      intarray_add(A,i);
  }
  return A;
}
// exercice 4
intarray jstl_find_proper_substr_indices(jstl tab, jstl sub){
  intarray A = standard_empty_intarray_create();
  for(int i=0;i<=tab->len-sub->len;){
    if(jstl_equal_substr(tab,i,i+sub->len-1,sub,0)){
      intarray_add(A,i);
      i+=sub->len;
    }else{
      i++;
    }
  }
  return A;
}
*/

/*Refactoring for jstl_find_substr_indices and  jstl_find_proper_substr_indices*/
/*
  Fonction auxiliaire pour jstl_find_substr_indices
  et jstl_find_substr_proper_indice.
  La difference entre les deux est que la valeur ajourtée au compteur i
  est sub->len dans le cas de prper et 1 dans l'autre cas.
*/
intarray jstl_find_substr_indices_aux(jstl tab, jstl sub,int incr_when_occu_found){
  intarray A = standard_empty_intarray_create();
    for(int i=0;i<=tab->len-sub->len;){
      if(jstl_equal_substr(tab,i,i+sub->len-1,sub,0)){
        intarray_add(A,i);
        i+=incr_when_occu_found;
      }else{
        i++;
      }
    }
    return A;
  
}

intarray jstl_find_substr_indices(jstl tab, jstl sub){
  return jstl_find_substr_indices_aux(tab,sub,1);
}
intarray jstl_find_proper_substr_indices(jstl tab, jstl sub){
  return jstl_find_substr_indices_aux(tab,sub,sub->len);
}

// exercice 5
int jstl_compare(jstl j1, jstl j2){
  int minlen = j1->len;
  int i;
  // get the min len
  if(j2->len < minlen)
    minlen = j2->len;
  for(i=0;i<minlen;i++){
    if(j1->data[i]<j2->data[i])
      return -1;
    else if(j1->data[i]>j2->data[i])
      return 1;
  }

  // celle qui est la plus grande longueur est la plus grande
  if(j1->len > j2->len)
    return 1;
  else if(j1->len < j2->len)
    return -1;
  else // j1->len == j2->len tous les caracteres identique
    return 0;
}


/* My own implementation of the exercices*/
/*Excercice 0*/
void MY_jstl_concatenation_argvs(jstl tab, char** values, int length){
    int i;
    for(i=1;i<length;i++){
        regstr string = values[i];
        for(int j=0;string[j]!='\0';j++){
            jstl_add(tab,string[j]);
        }
    }
}

/*Excercice 1*/
int MY_jstl_equal_substr(jstl j1,int s1, int e1,jstl j2, int s2){
  // treating the overloading cases
    int ok;
    MY_jstl_equal_substr_errors(j1,s1,e1,j2,s2,&ok);
    // in case we have a mistaked the input we get out of the function with missmatch
    if(ok=0)
      return 0;
    //get the two substrings
    jstl substring1 = MY_jstl_substr(j1,s1,e1) ;
    jstl substring2= MY_jstl_substr(j2,s2,j2->len-1);
    // if the length of the two substrings doesnt match then we go out from the function
    if(substring1->len!=substring2->len)
      return 0;
    // if at any moment the two substrings deffers from each other we return a miss match
    for(int i=0;i<substring1->len;i++){
      if(substring1->data[i]!=substring2->data[i]){
        return 0;
      }
    }
    // we return true if there is a perfect match
    return 1;

}
/*Excercice 2*/
int MY_jstl_equal (jstl j1,jstl j2){
  if(j1->len!=j2->len){
    return 0;
  }
  for(int i=0;i<j1->len;i++){
    if(j1->data[i]!=j2->data[i])
      return 0;
  }
  return 1;
}
/*Excercice 3*/
intarray MY_jstl_find_substr_indices(jstl tab, jstl sub){
  intarray indices = standard_empty_intarray_create();
  for (int i=0;i<tab->len;i++){
    if(tab->data[i]==sub->data[0]){
      int indice = i,flag = 1;
      for(int j=0;j<sub->len;j++,indice++){
        if(sub->data[j]!=tab->data[indice]){
          flag=0;
          break;
        }
      }
      if(flag==1){
        intarray_add(indices,i);
      }
    }
  }
  return indices;
}
/*Excercice 4*/
intarray MY_jstl_find_proper_substr_indices(jstl tab, jstl sub){
  intarray indices = standard_empty_intarray_create();
  //loop throw the word
  for(int i=0;i<tab->len;){
    char start = sub->data[0];
    int len = sub->len;
    //first my flag indicate that i didnt find a word
    int flag = 2;
    //if the element at index i match the first element of the substring
    if(tab->data[i]==start){
      // in need to go throw the word without altering the i position
      int indice = i;
      // declaring the j to loop the substring will help me to figure out if i went throw the 
      // hole substring or not 
      int j=0;
      for(j=0;j<len&&indice<tab->len;indice++,j++){
        // at any momement i find a single no match i break from the loop
        if(sub->data[j]!=tab->data[indice]){
          flag = 0;
          break;
        }
      }
      // here i found a sub word an found a match just if the j collide with the length of the sub string
      if(j==len)
        flag = 1;
    }
    // if i didnt find a match with the first letter of the substring
    // or if i went throw the substring and eventualy i didnt a match while im loop throw the substring
    if(flag==2||flag ==0){
      i++;
    }else if(flag == 1){// i went throw the hole substring and found a real match then need to skip all the letter of the substring
      intarray_add(indices,i);
      i+=len;
    }
  }
  return indices;
}
/*Excercice 5*/
int MY_jstl_compare(jstl tab,jstl lab){
  int len = tab->len;
  if(lab->len>tab->len){
    len = lab->len;
  }
  int i;
  for(i=0;i<len;i++){
      if(tab->data[i]>lab->data[i])
        return 1;
      if(tab->data[i]<lab->data[i])
        return -1;
  }
  if(lab->len==tab->len){
    return 0;
  }else if(lab->len > tab->len){
    return -1;
  }else{
    return 1;
  }
}
/*Helper functions*/
jstl MY_jstl_substr(jstl tab, int s1, int e1){
  int ok;
  MY_jstl_substr_errors(tab,s1, e1,&ok);
  if(ok==0){
    return standard_empty_jstl_create();
  }
  jstl word = standard_empty_jstl_create();
  for(int j=s1;j<=e1;j++)
    jstl_add(word,tab->data[j]);
  // printf("Length %d \n",word->len);
  return word;
}
void MY_jstl_equal_substr_errors(jstl j1,int s1, int e1,jstl j2, int s2,int* ok){
  *ok=1;
    if(s1<0 || s2<0 || e1 < 0){
      if(s1<0)
        printf("The starting index of the word \"%s\" must be great then 0\n",jstl_to_regstr(j1));
      if(s2<0)  
        printf("The starting index of the word \"%s\" must be great then 0\n",jstl_to_regstr(j2));
      if(e1<0)  
        printf("The ending index of the word \"%s\" must be great then 0\n",jstl_to_regstr(j1));
        
      *ok=0;
    }
    if(s1>e1){
        printf("The starting index: %d must be always less then the ending index %d\n",s1,e1);
        *ok=0;
    }
    if(e1>=j1->len || s2>=j2->len){
        if(e1>=j1->len){
            printf("The ending index %d must be always less then the length of the first word %s \n",e1,jstl_to_regstr(j1));
        }else{
            printf("The starting index %d must be always less then the length of the second word %s\n ",s2,jstl_to_regstr(j2));
        }
        *ok=0;
    }
}

void MY_jstl_substr_errors(jstl j1,int s1, int e1,int* ok){
  *ok=1;
    if(s1<0 ||  e1 < 0){
      if(s1<0)
        printf("The starting index of the word \"%s\" must be great then 0\n",jstl_to_regstr(j1));
      if(e1<0)  
        printf("The ending index of the word \"%s\" must be great then 0\n",jstl_to_regstr(j1));
        
      *ok=0;
    }
    if(s1>e1){
        printf("The starting index: %d must be always less then the ending index %d\n",s1,e1);
        *ok=0;
    }
    if(e1>=j1->len){
        printf("The ending index %d must be always less then the length of the first word %s \n",e1,jstl_to_regstr(j1));
        *ok=0;
    }
}

