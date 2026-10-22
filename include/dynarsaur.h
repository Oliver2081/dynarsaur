#ifndef DYNARSAUR_H
#define DYNARSAUR_H

#include <stddef.h>
#include <stdbool.h>


typedef struct IntArr {
    size_t size;
    size_t capacity;
    int* data;
} IntArr;


bool DA_InitI(IntArr** array, size_t initialSize);
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
