#include "field_info.h"
#include <stdio.h>
#include <stdlib.h>

void int_add(void* a, void* b, void* result){
    *(int*)result = *(int*)a + *(int*)b;
}

void int_mul(void* a, void* b, void* result){
    *(int*)result = *(int*)a * *(int*)b;
}

void int_print(void* a){
    printf("%d " , *(int*)a);
}

FieldInfo* GetIntFieldInfo() {
    static FieldInfo* info = NULL;

    if (info == NULL){
        info = (FieldInfo*)malloc(sizeof(FieldInfo));
        info->size = sizeof(int);
        info->add = int_add;
        info->mul = int_mul;
        info->print = int_print;
    }
    return info;
}

void double_add(void* a, void* b, void* result){
    *(double*)result = *(double*)a + *(double*)b;
}

void double_mul(void* a, void* b, void* result){
    *(double*)result = *(double*)a * *(double*)b;
}

void double_print(void* a){
    printf("%f " , *(double*)a);
}

FieldInfo* GetDoubleFieldInfo() {
    static FieldInfo* info = NULL;

    if (info == NULL){
        info = (FieldInfo*)malloc(sizeof(FieldInfo));
        if (info == NULL){
            printf("Memory allocation error\n");
            return NULL;
        }

        info->size = sizeof(double);
        info->add = double_add;
        info->mul = double_mul;
        info->print = double_print;
    }
    return info;
}