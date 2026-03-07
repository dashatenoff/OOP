
#ifndef UNTITLED2_FIELD_INFO_H
#define UNTITLED2_FIELD_INFO_H

#include <stddef.h>

typedef struct {
    size_t size;
    void (*add)(void*, void*, void*);
    void (*mul)(void*, void*, void*);
    void (*print)(void*);
} FieldInfo;

FieldInfo* GetIntFieldInfo();
FieldInfo* GetDoubleFieldInfo();
#endif //UNTITLED2_FIELD_INFO_H
