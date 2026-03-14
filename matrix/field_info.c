#include "field_info.h"
#include <stdio.h>

static void int_add(const void* a, const void* b, void* result){
    *(int*)result = *(const int*)a + *(const int*)b;
}

static void int_mul(const void* a, const void* b, void* result){
    *(int*)result = *(const int*)a * *(const int*)b;
}

static void int_print(const void* a){
    printf("%d ", *(const int*)a);
}

const FieldInfo* GetIntFieldInfo()
{
    static const FieldInfo info = {
            sizeof(int),
            int_add,
            int_mul,
            int_print
    };

    return &info;
}

static void double_add(const void* a, const void* b, void* result){
    *(double*)result = *(const double*)a + *(const double*)b;
}

static void double_mul(const void* a, const void* b, void* result){
    *(double*)result = *(const double*)a * *(const double*)b;
}

static void double_print(const void* a){
    printf("%f ", *(const double*)a);
}

const FieldInfo* GetDoubleFieldInfo()
{
    static const FieldInfo info = {
            sizeof(double),
            double_add,
            double_mul,
            double_print
    };

    return &info;
}