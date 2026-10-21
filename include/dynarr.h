#ifndef DYNARR_DYNARR_H
#define DYNARR_DYNARR_H

#include <stddef.h>


typedef struct IntArr {
    size_t size;
    size_t capacity;
    int* data;
} IntArr;

int InitIntArr(IntArr* array, size_t initialSize);
void DestroyIntArray(IntArr* array);

#endif //DYNARR_DYNARR_H
