#include "dynarr.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int DA_FindNextPower2(const size_t x, size_t* result) {
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

int DA_CompareInts(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;

    if (x > y) {
        return 1;
    }
    if (y > x) {
        return -1;
    }

    return 0;
}

int DA_InitI(IntArr* array, const size_t initialSize) {
    // Set initial capacity and store in array->capacity
    if (!DA_FindNextPower2(initialSize, &array->capacity)) {
        return false;
    }

    array->data = malloc(initialSize * sizeof(int));

    if (array->data == NULL) {
        return false;
    }

    array->size = initialSize;

    return true;
}

void DA_DestroyI(IntArr* array) {
    free(array->data);
    array->data = NULL;
}


int DA_ResizeI(IntArr* array, const size_t newSize) {

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

        if (newSize <= 0) {
            return false;
        }

        if (!DA_FindNextPower2(newSize, &newCapacity)) {
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

int DA_AppendI(IntArr* array, const int value) {
    if (!DA_ResizeI(array, array->size + 1)) {
        return false;
    }

    array->data[array->size - 1] = value;
    return true;
}

int DA_PopI(IntArr* array, const size_t index) {
     if (index >= array->size || index < 0) {
        return false;
     }

    for (size_t idx = index; idx < array->size; idx += 1) {
        array->data[idx] = array->data[idx + 1];
    }

    array->size -= 1;

    return true;
}

int DA_InsertI(IntArr* array, const int value, const size_t index) {
    if (index > array->size || index < 0 || array->size == SIZE_MAX) {
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

int DA_SortAscendingI(IntArr* array) {
    qsort(array->data, array->size, sizeof(int), DA_CompareInts);

    return true;
}

int DA_FindI(IntArr* array, const int value, size_t* index) {
    int* sorted = malloc(array->size * sizeof(int));

    if (sorted == NULL) {
        return false;
    }


    free(sorted);
    return true;
}

