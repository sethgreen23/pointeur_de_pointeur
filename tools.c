#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
// pour detecter une fuite de memoire
// on compte la quantite de memoire allower
void tools_memory_init(void){
  GLOBAL_ALLOC_MEMORY=0;
}
// compte la quantite de momoire
//void* est un pointeur sur une donnee qu'on ne connait pas le type
void* tools_malloc(int alloc){
  void* ptr = malloc(alloc);
  GLOBAL_ALLOC_MEMORY+=alloc;
  return ptr;
}
void tools_free(void* ptr, int alloc){
  free(ptr);
  GLOBAL_ALLOC_MEMORY-=alloc;
}
void tools_memory_check_at_end_of_app(void){
  if(GLOBAL_ALLOC_MEMORY!=0)
    printf("Ce programme a une ou des fuite de memoire. %d octets n'ont pas ete libere.",GLOBAL_ALLOC_MEMORY);
}
// interchange the values of two variables
void interchange_values(int* p, int* c){
  int interchange;
  interchange=*p;
  *p=*c;
  *c=interchange;
}
// interchange the values of two variables
void character_interchange_values(char* p, char* c){
  char interchange;
  interchange=*p;
  *p=*c;
  *c=interchange;
}
// convert a string to a number
int string_to_int(char* str){
  int* ok = malloc(sizeof(int));
  int number = safe_string_to_int(str,ok);
  if(*ok==1){
    return number;
  }else if(*ok==0){
    printf("%s is not a number.\n",str);
    return -1;
  }
}
// convert a string to number with out value
int safe_string_to_int(char* str, int* ok){
  if(str[0]=='-')
    return - safe_string_to_int(str+1,ok);
  int len = strlen(str);
  *ok=1;
  int i,number=0;
  for(i=0;i<len;i++){
    char c = str[i];
    if(c<'0' || c>'9'){
      *ok=0;
      return -1;
    }
    number*=10;
    number+=c-48;
  }
  return number;
}