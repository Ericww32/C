/*
    Created by Eric Willoughby
    Pointer swapping
*/

#include <iostream>
using namespace std;

void pointerSwap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main(void) {
    int r;
    int *p = &r;
    int **q = &p;

    printf("r = %d\np = %d\nq = %d", r, p, q);

    **q = 32;

    printf("r = %d\np = %d\nq = %d", r, p, q);
    print("\n************************************");

    int i = 56, j = 10087;

    printf("Original: i = %d, j = %d\n", i, j);
    pointerSwap(&i, &j);

    // Now verify that your swap function worked.
    printf("Swapped:  i = %d, j = %d\n", i, j);
    print("\n************************************");

    return 0;
}
