#include <stdlib.h>
#include <stdio.h>
#include "intarray.h"
#include "tools.h"
#include "jstl.h"



int main(int argc, char** argv){
    // get the string from the argv starting from 1
    // get the length of the all the elements
   // ********************EXERCICE 0*************************
    //my version
    // jstl tab = standard_empty_jstl_create();
    // jstl_concatenation_argvs(tab, argv,argc);
    // jstl_debug(tab);
    //correction verions
    // for(int i=1;i<argc;i++){
    //     jstl subTab = regstr_to_jstl(argv[i]);
    //     D_jstl_concat(tab,subTab);
    //     jstl_destroy(subTab);
    // }
    // jstl_debug(tab);
    //********************EXERCICE 1*************************
    // my version
    // jstl tab1 = regstr_to_jstl("le soleil brille.");
    // jstl tab2 = regstr_to_jstl("sole");
    // int start1=3;
    // int end1=6;
    // int start2=0;
    // int numb = jstl_equal_substr(tab1,start1,end1,tab2,start2);
    // // jstl word = jstl_substr(tab2,0,3);
    // // printf("word : \"%s\"",jstl_to_regstr(word) );
    // if(numb==1){
    //     printf("The selection match word 1: %s and word 2:%s\n",jstl_to_regstr(jstl_substr(tab1,start1,end1)),jstl_to_regstr(jstl_substr(tab2,start2,tab2->len-1)));
    // }else{
    //     printf("The selection doesnt match match word 1: %s and word 2:%s\n",jstl_to_regstr(jstl_substr(tab1,start1,end1)),jstl_to_regstr(jstl_substr(tab2,start2,tab2->len-1)));
    // }
    // correction version
    // jstl tab1 = regstr_to_jstl("le soleil brille.");
    // jstl tab2 = regstr_to_jstl("sole");
    // if(jstl_equal_substr(tab1,3,6,tab2,0)){
    //     printf("Oui");
    // }else{
    //     printf("Non");
    // }
    // jstl_destroy(tab1);
    // jstl_destroy(tab2);

    //********************EXERCICE 2*************************
    // my version
    // jstl tab = regstr_to_jstl("Mariouma");
    // jstl tab1 = regstr_to_jstl("Mariouma");

    // int flag =  jstl_equal (tab1,tab);
    // if(flag == 0)
    //     printf("The words are diffrent");
    // else
    //     printf("The words are same");
    //correction verions
    // jstl tab1 = regstr_to_jstl("soleil.");
    // jstl tab2 = regstr_to_jstl("soleil.");
    // if(jstl_equal(tab1,tab2)){
    //     printf("Oui");
    // }else{
    //     printf("Non");
    // }
    // jstl_destroy(tab1);
    // jstl_destroy(tab2);
    

    //********************EXERCICE 3*************************
    // my version
    // jstl tab = regstr_to_jstl("totovaatotortoetolecoleto");
    // jstl tab1 = regstr_to_jstl("toto");
    // intarray indices = jstl_find_substr_indices(tab,tab1);
    // intarray_debug(indices);
    //correction verions
    // jstl tab1 = regstr_to_jstl("tototo titititototo");
    // jstl tab2 = regstr_to_jstl("toto");
    // intarray ar = jstl_find_substr_indices(tab1,tab2);
    // intarray_debug(ar);
    // intarray_destroy(ar);
    // jstl_destroy(tab1);
    // jstl_destroy(tab2);
    
    //********************EXERCICE 4*************************
    // my version
    // jstl tab = regstr_to_jstl("totototovaatotolecoletot");
    // jstl tab1 = regstr_to_jstl("toto");
    // intarray indices = jstl_find_proper_substr_indices(tab,tab1);
    // intarray_debug(indices);
    //correction verions
    // jstl tab1 = regstr_to_jstl("tototo titititototo");
    // jstl tab2 = regstr_to_jstl("toto");
    // intarray ar = jstl_find_proper_substr_indices(tab1,tab2);
    // intarray_debug(ar);
    // intarray_destroy(ar);
    // jstl_destroy(tab1);
    // jstl_destroy(tab2);
    // correction verions
    
    //********************EXERCICE 5*************************
    // my version
    // jstl tab = regstr_to_jstl("toti");
    // jstl lab = regstr_to_jstl("totia");
    // int result = jstr_compare(tab,lab);
    // if(result==0){
    //     printf("%s == %s",jstl_to_regstr(tab),jstl_to_regstr(lab));
    // }else if(result==1){
    //     printf("%s > %s",jstl_to_regstr(tab),jstl_to_regstr(lab));
    // }else if(result == -1){
    //     printf("%s < %s",jstl_to_regstr(tab),jstl_to_regstr(lab));
    // }
    //correction verions
}