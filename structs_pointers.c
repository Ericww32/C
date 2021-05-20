/*
    Created by Eric Willoughby
    Structs with pointers
*/

#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = NULL;

    printf("Attempting Swap: \n");
    printf("First int: %d\nSecont int: %d\n", *a, *b);
    temp = *a;
    *a = *b;
    *b = temp;
    printf("\nCompeted Swap:\n");
    printf("First int: %d\nSecont int: %d\n", *a, *b);
}

typedef struct T {
    int gl;
    char name[5];
} T;

int structInC(void) {
    T data;
    data.gl = 597;
    strcpy(data.name, "Vince");
    printf("Name: %s #%d\n", data.name, data.gl);
    return 0;
}

struct T *create_a_struct(void) {
    struct T t;

    // Initialize 'gl' to zero and 'name' to the empty string.
    t.gl = 12;
    strcpy(t.name, "Bob");
    return &t;
}

int main(int argc, const char * argv[]) {
    int a = 52, b = 23;

    print("***************\n");
    print("** SWAP FUNC **\n");
    print("***************\n");
    swap(&a, &b);

    print("\n***************\n");
    print("* STRUCT IN C *\n");
    print("***************\n");
    structInC();

    print("\n***************\n");
    print("* MAKE-STRUCT *\n");
    print("***************\n");
    T *data2 = create_a_struct();
    printf("Number: %d || Name: %s \n", data2->gl, data2->name);

    return 0;
}
