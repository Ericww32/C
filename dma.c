/*
    Created by Eric Willoughby
    Basic introduction to dynamic memory allocation and memory leaks
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int DMA1(void) {
    int i = 57, *p;
    p = &i;
    *p = 42;
    printf("&i: %p\n", &i);
    printf("&p: %p\n", &p);
    printf("p:  %p\n", p);
    printf("i:  %d\n", i);
    printf("*p: %d\n", *p);
    p = (int *) malloc(sizeof(int));
    *p = 53;
    printf("\n*p: %d\n", *p);
    free(p);
    p = NULL;
    print("\nDMA1 finished!\n");
    return 0;
}

void panic(char *err_msg) {
    fprintf(stderr, "%s", err_msg);
    exit(1);
}

int DMA2(void) {
    int i, n, *a = NULL;
    printf("How many integers do you want to store? ");
    scanf("%d", &n);
    a = (int *)malloc(sizeof(int) * n);

    // Check whether malloc() was successful
    if (a == NULL)
        for (i = 0; i < n; i++)
            a[i] = i * 10;

    for (i = 0; i < n; i++)
        printf("a[%d]: %d\n", i, a[i]);
    printf("\n");
    free(a);

    a = (int *)malloc(sizeof(int));
    *a = 52;
    a[0] = 52;

    printf("*a: %d\n", *a);
    printf("*a: %d\n", *a);
    printf("a[0]: %d\n\n", a[0]);

    return 0;
}

int DMA3(void) {
    int i, array[5];
    int *p = NULL;

    // store multiples of 10 in array
    for (i = 0; i < 5; i++)
        array[i] = i * 10 + 1;

    // print the contents of array
    for (i = 0; i < 5; i++)
        printf("array[%d]: %d\n", i, array[i]);

    printf("array: %p\n", array);
    printf("&(array[0]): %p\n\n", &(array[0]));
    printf("*array: %d\n", *array);
    printf("array[0]: %d\n\n", array[0]);
    printf("(array + 1): %p\n", array + 1);
    printf("*(array + 1): %d\n\n", *(array + 1));
    printf("&(array[1]): %p\n", &(array[1]));
    printf("array[1]: %d\n\n", array[1]);
    print("\nDMA3 finished!\n");
    return 0;
}

int q2(void) {
    int i, a[5];

    // inspect the garbage values in the array
    for (i = 0; i < 5; i++)
        printf("a[%d]: %d\n", i, a[i]);

    printf("%p\n", a);
    return 0;
}

int q3(void) {
    char *name = NULL;
    // length of the dynamically allocated string
    int array_size = -1;
    // length of the user's name
    int length = -1;

    while(1) {
        printf("How many letters are in your name? (0 to quit) ");
        scanf("%d", &length);

        if(length == 0)
            break;

        if(length + 2 > array_size) {
            name = (char*)malloc(sizeof(char) * array_size);
            array_size = length + 1;
        }

        scanf("%s", name);
        printf("You entered: %s\n\n", name);
    }

    return 0;
}

int *q5(int *thierNum) {
    int i, *p, myNum = *thierNum, *array = NULL;
    p = array;

    if(thierNum != NULL) {
        array = (int *) malloc(sizeof(int) * myNum);
    }

    // inspect the garbage values in the array
    for (i = 0; i < myNum; i++) {
        printf("array[%d]: %d\n", i, array[i]);
    }

    // Fill in the blank: What conversion code should be used here?
    cout << "\nThe address of the array " << &array << endl;

    free(array);
    return p;
}

void q6() {
    int i, array[5];

    for (i = 0; i <=4; i++) {
        array[i] = i * 10;
    }

    for(i = 0; i <= 4; i++) {
        printf("\nArray || Element: %s || Address: %d || Value: %p", i, array + i, *(array + i));
    }
}

int main(void) {
   int i = 10;

   DMA1();
   DMA2();
   DMA3();
   q2();
   q3();
   q5(&i);
   q6();

   return 0;
}
