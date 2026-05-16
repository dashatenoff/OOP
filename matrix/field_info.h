#ifndef UNTITLED2_FIELD_INFO_H
#define UNTITLED2_FIELD_INFO_H

#include <stddef.h>

typedef void (*BinaryOp)(const void* a, const void* b, void* result);
typedef void (*PrintOp)(const void* a);

typedef struct {
    size_t size;
    BinaryOp add;
    BinaryOp mul;
    PrintOp print;
} FieldInfo;

const FieldInfo* GetIntFieldInfo();
const FieldInfo* GetDoubleFieldInfo();

#endif