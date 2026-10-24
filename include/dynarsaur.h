#ifndef DYNARSAUR_H
#define DYNARSAUR_H

#include <stddef.h>
#include <stdbool.h>


typedef enum DA_Error {
    DA_NO_ERROR = 0,
    DA_ALLOCATION_ERROR,
    DA_INDEX_ERROR,
} DA_Error;

typedef struct DA_Array {
    size_t size;
    size_t capacity;
    size_t elementSize;
    void* data;
} DA_Array;

typedef int (*DA_CompareFunc)(const void*, const void*);

extern DA_Error DA_LastError;

bool DA_InitArray(DA_Array** array, size_t elementSize, size_t initialSize);
bool DA_DestroyArray(DA_Array** array);

bool DA_Resize(DA_Array* array, size_t newSize);

bool DA_Append(DA_Array* array, const void* value);
bool DA_AppendI(DA_Array* array, const int value);
bool DA_AppendF(DA_Array* array, const float value);
bool DA_AppendD(DA_Array* array, const double value);
bool DA_AppendC(DA_Array* array, const char value);

bool DA_Pop(DA_Array* array, size_t index);
bool DA_Insert(DA_Array* array, const void* value, const size_t index);

bool DA_Sort(DA_Array* array, DA_CompareFunc compare);

bool DA_FindI(DA_Array* array, int value, size_t* index);

bool DA_GetI(DA_Array* array, size_t index, int* value);
bool DA_SetI(DA_Array* array, size_t index, int value);

#endif //DYNARSAUR_H
