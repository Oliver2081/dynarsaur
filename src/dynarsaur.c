#include "dynarsaur.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool DA_FindNextPower2(const size_t x, size_t* result) {
    size_t currentValue = 1;

    if (x == 0 || result == NULL) {
        return false;
    }

    while (x > currentValue) {
        if (currentValue > SIZE_MAX / 2) {
            return false;
        }
        currentValue *= 2;
    }

    *result = currentValue;
    return true;
}

int DA_CompareIntsA(const void* a, const void* b) {
    const int x = *(const int*)a;
    const int y = *(const int*)b;

    return (x > y) - (y > x);
}

int DA_CompareIntsD(const void* a, const void* b) {
    return -DA_CompareIntsA(a, b);
}

bool DA_InitI(IntArr** array, const size_t initialSize) {
    if (array == NULL) {
        return false;
    }

    *array = malloc(sizeof(IntArr));
    if (*array == NULL) {
        return false;
    }

    IntArr* arr = *array;

    // Set initial capacity and store in array->capacity
    if (!DA_FindNextPower2(initialSize, &arr->capacity)) {
        return false;
    }

    arr->data = malloc(arr->capacity * sizeof(int));
    if (arr->data == NULL) {
        free(*array);
        *array = NULL;
        return false;
    }

    arr->size = initialSize;
    return true;
}

bool DA_DestroyI(IntArr** array) {
    if (array != NULL && *array != NULL) {
        IntArr* arr = *array;

        if (arr->data != NULL) {
            free(arr->data);
            arr->data = NULL;
        }

        free(*array);
        *array = NULL;
    }

    return true;
}


bool DA_ResizeI(IntArr* array, const size_t newSize) {

    if (newSize > array->capacity) {
        size_t newCapacity;
        void* newPtr;

        if (!DA_FindNextPower2(newSize, &newCapacity)) {
            return false;
        }

        if (newCapacity > SIZE_MAX / sizeof(int)) {
            return false;
        }

        newPtr = realloc(array->data, (newCapacity) * sizeof(int));

        if (newPtr == NULL) {
            return false;
        }

        array->data = newPtr;
        array->capacity = newCapacity;

    }

    else if (newSize <= array->capacity / 2) {
        size_t newCapacity;
        void* newPtr;

        if (newSize == 0) {
            newCapacity = 1;
            return false;
        }

        else if (!DA_FindNextPower2(newSize, &newCapacity)) {
            return false;
        }

        newPtr = realloc(array->data, newCapacity * sizeof(int));

        if (newPtr == NULL) {
            return false;
        }

        array->data = newPtr;
        array->capacity = newCapacity;
    }

    array->size = newSize;
    return true;
}

bool DA_AppendI(IntArr* array, const int value) {
    if (!DA_ResizeI(array, array->size + 1)) {
        return false;
    }

    array->data[array->size - 1] = value;
    return true;
}

bool DA_PopI(IntArr* array, const size_t index) {
     if (index >= array->size) {
        return false;
     }

    for (size_t idx = index; idx < (array->size - 1); idx += 1) {
        array->data[idx] = array->data[idx + 1];
    }

    DA_ResizeI(array, array->size - 1);

    return true;
}

bool DA_InsertI(IntArr* array, const int value, const size_t index) {
    if (index > array->size || array->size == SIZE_MAX) {
        return false;
    }

    if (!DA_ResizeI(array, array->size + 1)) {
        return false;
    }

    for (size_t idx = (array->size - 1); idx > index; idx--) {
        array->data[idx] = array->data[idx - 1];
    }

    array->data[index] = value;

    return true;
}

bool DA_SortAscendingI(IntArr* array) {
    qsort(array->data, array->size, sizeof(int), DA_CompareIntsA);
    return true;
}

bool DA_SortDescendingI(IntArr* array) {
    qsort(array->data, array->size, sizeof(int), DA_CompareIntsD);
    return true;
}

bool DA_FindI(IntArr* array, const int value, size_t* index) {
    for (size_t idx = 0; idx < array->size; idx++) {
        if (array->data[idx] == value) {
            *index = idx;
            return true;
        }
    }
    return false;
}

bool DA_GetI(IntArr* array, const size_t index, int* value) {
    if (index >= array->size) {
        return false;
    }
    *value = array->data[index];
    return true;
}

bool DA_SetI(IntArr* array, const size_t index, const int value) {
    if (index >= array->size) {
        return false;
    }
    array->data[index] = value;
    return true;
}
