/*
    Created by Eric Willoughby
    More dynamic memory allocation and utilization of C libraries
*/

#include <iostream>
#include <cstdlib> // need malloc()
#include <cstring> // need for strcmp() and strcpy()
#include <locale>  // tolower
using namespace std;

int dma_2d(void) {
    int i, num_students, num_grades;
    int **array;
    printf("How many students are in the class? ");
    scanf("%d", &num_students);
    array = (int **)malloc(sizeof(int *) * num_students);
    printf("How many grades does each student have? ");
    scanf("%d", &num_grades);

    // Create the individual arrays for storing assignment/exam scores.
    for (i = 0; i < num_students; i++)
        array[i] = (int *)malloc(sizeof(int) * num_grades);

    print("Student number: %i", num_students);
    print("Student grade: %i", num_grades);

    for (i = 0; i < num_students; i++)
        free(array[i]);

    // Free the array that held the pointers to all those other arrays.
    free(array);
    return 0;
}

void letterEx() {
    char letter;
    // Show the ASCII number for every lower case letter
    for (letter = 'a'; letter <= 'z'; letter++)
        printf("The ASCII value of %c is %d.\n", letter, letter);

    // Convert letters 'a', 'b', and 'c' to 0, 1, and 2, respectively.
    for (letter = 'a'; letter <= 'c'; letter++)
        printf("%c -> %d\n", letter, letter - 'a');
}

int strcmp_i(const char *str1, const char *str2) {
    char first[255], second[255];
    int result = NULL, i = 0;

    memset(first, '\0', sizeof(str1));
    strcpy(first, str1);

    memset(second, '\0', sizeof(str2));
    strcpy(second, str2);

    for(i = 0; i < strlen(str1); i++)
        first[i] = tolower(first[i]);

    for(i = 0; i < strlen(str2); i++)
        second[i] = tolower(second[i]);

    printf("Input:  First = %s ---- Second = %s\n", str1, str2);
    printf("Result:  First = %s ---- Second = %s\n", first, second);

    result = strcmp(first, second);

    if(result != 0) {
        printf("\nFail:  \t\t %s and %s do NOT equal each other...\n", first, second);
        print("***********************************\n");
        return -1;
    }

    printf("\nSuccess:  \t %s and %s DO equal each other!!!\n", first, second);
    print("***********************************\n");

    return result;
}

int regStrCmp(const char *str1, const char *str2) {
    int result = strcmp(str1, str2);

    printf("Input:  First = %s ---- Second = %s\n", str1, str2);
    printf("Result:  First = %s ---- Second = %s\n", str1, str2);

    if(result != 0) {
        printf("\nFail:  \t\t %s and %s do NOT equal each other...\n", str1, str2);
        print("***********************************\n");
        return -1;
    }

    printf("\nSuccess:  \t %s and %s DO equal each other!!!\n", str1, str2);
    print("***********************************\n");

    return result;
}

void free_n_pointers(int mySize, void *myPtr, ...) {
    void *ptrRef = myPtr;
    int i = 1;
    va_list list;
    va_start(list, myPtr);

    for(i = 1; i <= mySize; i++) {
        if(ptrRef != NULL) {
            printf("Freeing Pointer #%d at Address: %p\n", i, ptrRef);
            free(ptrRef);
            ptrRef = va_arg(list, void *);
        }
    }

    va_end(list);
}

int main(void) {
    int i = 52, *ip;
    float f = 3.14, *fp;
    char l = 'L', *cp;

    ip = (int *)malloc(sizeof(int) * i);
    fp = (float *)malloc(sizeof(float) * f);
    cp = (char *)malloc(sizeof(char) * l);

    *ip = i;
    *fp = f;
    *cp = l;

    printf("ip:: Value: %d -- Address: %p\n", *ip, ip);
    printf("fp:: Value: %.2f -- Address: %p\n", *fp, fp);
    printf("cp:: Value: %c -- Address: %p\n", *cp, cp);

    letterEx();
    dma_2d();

    print("Attempting Case Adv. Comparison... \n");
    strcmp_i("Butter", "Umbrella");
    print("Attempting Case Adv. Comparison... \n");
    strcmp_i("wOoD", "WoOd");

    print("Attempting Regular Case Comparison... \n");
    regStrCmp("Butter", "Umbrella");
    print("Attempting Regular Case Comparison... \n");
    regStrCmp("wOoD", "WoOd");

    free_n_pointers(3, ip, fp, cp);

    try {
        printf("ip:: Value: %d -- Address: %p\n", *ip, ip);
        printf("fp:: Value: %.2f -- Address: %p\n", *fp, fp);
        printf("cp:: Value: %c -- Address: %p\n", *cp, cp);
    } catch(exception e) {
        printf("We broke it");
    }

    return 0;
}
