#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int GLOBAL_ALLOC_MEMORY;

void tools_memory_init(void);
void* tools_malloc(int alloc);
void tools_free(void* ptr, int alloc);
void tools_memory_check_at_end_of_app(void);
void interchange_values(int* p, int* c);
void character_interchange_values(char* p, char* c);
int string_to_int(char* str);
int safe_string_to_int(char* str, int* ok);

#endif