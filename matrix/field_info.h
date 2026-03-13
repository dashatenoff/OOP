
#ifndef UNTITLED2_FIELD_INFO_H
#define UNTITLED2_FIELD_INFO_H

#include <stddef.h>

typedef struct {
    size_t size;
    void (*add)(const void* a, const void* b, void* result);
    void (*mul)(const void* a, const void* b, void* result);
    void (*print)(const void* a);
} FieldInfo;

const FieldInfo* GetIntFieldInfo();
const FieldInfo* GetDoubleFieldInfo();
#endif //UNTITLED2_FIELD_INFO_H
