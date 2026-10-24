#ifndef DYNARSAUR_H
#define DYNARSAUR_H

#include <stddef.h>
#include <stdbool.h>


typedef enum DA_Error {
    DA_SUCCESS = 0,
    DA_ALLOCATION_ERROR,
    DA_INDEX_ERROR,
} DA_Error;

typedef enum DA_ArrayType {
    DA_IntArray,
} DA_ArrayType;

typedef struct IntArr {
    size_t size;
    size_t capacity;
    int* data;
} IntArr;

extern DA_Error DA_LastError;

bool DA_InitArray(IntArr** array, size_t initialSize);
bool DA_DestroyI(IntArr** array);
bool DA_ResizeI(IntArr* array, size_t newSize);

bool DA_AppendI(IntArr* array, int value);
bool DA_PopI(IntArr* array, size_t index);
bool DA_InsertI(IntArr* array, int value, size_t index);

bool DA_SortAscendingI(IntArr* array);
bool DA_SortDescendingI(IntArr* array);

bool DA_FindI(IntArr* array, int value, size_t* index);

bool DA_GetI(IntArr* array, size_t index, int* value);

// Sets array[index] to value
bool DA_SetI(IntArr* array, size_t index, int value);

#endif //DYNARSAUR_H
