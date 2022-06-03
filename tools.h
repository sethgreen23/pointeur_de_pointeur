#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void interchange_values(int* p, int* c);
void character_interchange_values(char* p, char* c);
int string_to_int(char* str);
int safe_string_to_int(char* str, int* ok);

#endif