#include <stdio.h>
#include "dynarsaur.h"

int main(void) {
    IntArr* array = NULL;

    DA_InitI(&array, 5);

    DA_SetI(array, 0, 64);
    DA_SetI(array, 1, 19);

    DA_AppendI(array, 45);
    DA_AppendI(array, 46);
    DA_AppendI(array, 47);
    DA_AppendI(array, 48);
    DA_AppendI(array, 128);
    DA_AppendI(array, 123456);

    int a, b;
    DA_GetI(array, 1, &a);
    DA_GetI(array, 10, &b);

    size_t c;
    DA_FindI(array, 128, &c);

    DA_InsertI(array, 22, 1);
    DA_PopI(array, 3);
    DA_SortAscendingI(array);
    DA_SortDescendingI(array);

    DA_DestroyI(&array);
    return 0;
}
