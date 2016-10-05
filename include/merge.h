#pragma once
#include <stdlib.h>
void merge_sort(void* array,size_t n,size_t elem_size,int (*cmp)(const void*,const void*));
int cmpa(const void *p1,const void *p2);
int cmpb(const void *p1,const void *p2);
int cmpc(const void *p1,const void *p2);
void super_copy(char *p1,char *p2,size_t elem_size);
void array_copy(void *arr1,void *arr2,size_t m,size_t elem_size);
void unite_arrays(void* array,void *a1,size_t n1,void *a2,size_t n2,size_t elem_size,int (*cmp)(const void*,const void*));
