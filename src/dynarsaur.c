#include "dynarsaur.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

DA_Error DA_LastError = DA_NO_ERROR;

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

bool DA_InitArray(DA_Array** array, const size_t elementSize, const size_t elementAmount) {
    if (array == NULL) {
        return false;
    }

    *array = malloc(sizeof(DA_Array));
    if (*array == NULL) {
        return false;
    }

    DA_Array* arr = *array;

    // Set initial capacity and store in array->capacity
    if (!DA_FindNextPower2(elementAmount, &arr->capacity)) {
        return false;
    }

    arr->data = malloc(arr->capacity * elementSize);
    if (arr->data == NULL) {
        free(*array);
        *array = NULL;
        DA_LastError = DA_ALLOCATION_ERROR;
        return false;
    }

    arr->elementSize = elementSize;
    arr->size = elementAmount;

    DA_LastError = DA_NO_ERROR;
    return true;
}

bool DA_DestroyArray(DA_Array** array) {
    if (array != NULL && *array != NULL) {
        DA_Array* arr = *array;

        if (arr->data != NULL) {
            free(arr->data);
            arr->data = NULL;
        }

        free(*array);
        *array = NULL;
    }

    return true;
}


bool DA_Resize(DA_Array* array, const size_t newSize) {

    if (newSize > array->capacity) {
        size_t newCapacity;
        void* newPtr;

        if (!DA_FindNextPower2(newSize, &newCapacity)) {
            return false;
        }

        if (newCapacity > SIZE_MAX / sizeof(int)) {
            return false;
        }

        newPtr = realloc(array->data, newCapacity * array->elementSize);

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

        newPtr = realloc(array->data, newCapacity * array->elementSize);

        if (newPtr == NULL) {
            return false;
        }

        array->data = newPtr;
        array->capacity = newCapacity;
    }

    array->size = newSize;
    return true;
}

/* Appending */
bool DA_Append(DA_Array* array, const void* value) {
    if (!DA_Resize(array, array->size + 1)) {
        return false;
    }

    size_t offset = (array->size - 1) * array->elementSize;

    memcpy((char*)array->data + offset, value, array->elementSize);

    return true;
}

bool DA_AppendI(DA_Array* array, const int value) {return DA_Append(array, &value);}
bool DA_AppendF(DA_Array* array, const float value) {return DA_Append(array, &value);}
bool DA_AppendD(DA_Array* array, const double value) {return DA_Append(array, &value);}
bool DA_AppendC(DA_Array* array, const char value) {return DA_Append(array, &value);}

/* Popping */
bool DA_Pop(DA_Array* array, const size_t index) {
    if (index >= array->size) {
        DA_LastError = DA_INDEX_ERROR;
        return false;
    }

    char* dest = (char*)array->data + (array->elementSize * index);
    char* src = (char*)array->data + (array->elementSize * (index + 1));
    size_t byteAmount = (array->size - index - 1) * array->elementSize;

    memmove(dest, src, byteAmount);

    if (!DA_Resize(array, array->size - 1)) {
        return false;
    }
    
    return true;
}

/* Inserting */
bool DA_Insert(DA_Array* array, const void* value, const size_t index) {
    if (index > array->size || array->size == SIZE_MAX) {
        return false;
    }

    size_t oldSize = array->size;
    void* tempValue = malloc(array->elementSize);

    if (tempValue == NULL) {
        return false;
    }

    memcpy(tempValue, value, array->elementSize);

    if (!DA_Resize(array, array->size + 1)) {
        free(tempValue);
        return false;
    }

    char* dest = (char*)array->data + (array->elementSize * index);
    char* src = (char*)array->data + (array->elementSize * (index + 1));
    size_t byteAmount = (oldSize - index) * array->elementSize;

    memmove(src, dest, byteAmount);
    memcpy(dest, tempValue, array->elementSize);

    free(tempValue);
    return true;
}

bool DA_Sort(DA_Array* array, DA_CompareFunc compare) {
    if (array == NULL || compare == NULL) {
        return false;
    }

    if (array->size < 2) {
        return true;
    }

    if (array->data == NULL || array->elementSize == 0) {
        return false;
    }

    qsort(array->data, array->size, array->elementSize, compare);

    return true;
}

bool DA_Find(IntArr* array, const int value, size_t* index) {
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
