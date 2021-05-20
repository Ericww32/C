/*
 Author:    Eric Willoughby
 Mission:   SmartArray
 File:      main.c
 Date:      9/20/17.
 NID:       er052156
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"
#define null NULL

int main(void)
{
    int i; char buffer[32];
    
    SmartArray *smarty1 = createSmartArray(-1);
    SmartArray *smarty2 = createSmartArray(-1);
    
    FILE *ifp = fopen("names.txt", "rb");
    
    // Read all names from the file and add them to smarty1.
    while (fscanf(ifp, "%s", buffer) != EOF)
        put(smarty1, buffer);
    
    // Add the names to smarty2 in reverse order.
    for (i = getSize(smarty1) - 1; i >= 0; i--)
        put(smarty2, get(smarty1, i));
    
    // Print the contents of smarty1.
    printf("\n-- SMART ARRAY 1: --\n");
    printSmartArray(smarty1);
    
    // Print the contents of smarty2.
    printf("\n-- SMART ARRAY 2 (First Names): --\n");
    printSmartArray(smarty2);
    
    // Swap last names with first names in smarty2.
    for (i = 0; i < getSize(smarty2); i++)
    {
        if (strcmp(get(smarty2, i), "Daniel") == 0)
            set(smarty2, i, "Mandragona");
        else if (strcmp(get(smarty2, i), "Kristjan") == 0)
            set(smarty2, i, "Arumae");
        else if (strcmp(get(smarty2, i), "Karan") == 0)
            set(smarty2, i, "Daei-Mojdehi");
        else if (strcmp(get(smarty2, i), "Shahidul") == 0)
            set(smarty2, i, "Islam");
        else if (strcmp(get(smarty2, i), "Fereshteh") == 0)
            set(smarty2, i, "Jafariakinabad");
        else if (strcmp(get(smarty2, i), "Pierre") == 0)
            set(smarty2, i, "LaBorde");
        else if (strcmp(get(smarty2, i), "Rachael") == 0)
            set(smarty2, i, "Sera");
        else if (strcmp(get(smarty2, i), "Richie") == 0)
            set(smarty2, i, "Wales");
    }
    
    // Print the contents of smarty2.
    printf("\n-- SMART ARRAY 2 (Last Names): --\n");
    printSmartArray(smarty2);
    
    // Print smarty1 (in reverse order) and smarty2, to match up first and last
    // names.
    printf("\n-- COMBINED ARRAYS (First and Last Names): --\n");
    for (i = 0; i < getSize(smarty2); i++)
        printf("%s %s\n", get(smarty1, getSize(smarty1) - 1 - i), get(smarty2, i));
    
    // Add elements from smarty1 to the end of smarty1 (in reverse order).
    printf("\n");
    for (i = getSize(smarty1) - 1; i >= 0; i--)
        printf("Adding %s to smarty1 ...\n", put(smarty1, get(smarty1, i)));
    
    // Print the contents of smarty1.
    printf("\n-- SMART ARRAY 1: --\n");
    printSmartArray(smarty1);
    
    // Insert a string at the beginning of array smarty1.
    insertElement(smarty1, 0, "List of Names:");
    
    // Print the contents of smarty1.
    printf("\n-- SMART ARRAY 1: --\n");
    printSmartArray(smarty1);
    
    // Remove all elements from smarty1.
    while (getSize(smarty1))
        removeElement(smarty1, 0);
    
    // Print smarty1, which is now an empty array.
    printf("\n-- SMART ARRAY 1: --\n");
    printSmartArray(smarty1);
    
    // Destroy our smart arrays.
    smarty1 = destroySmartArray(smarty1);
    smarty2 = destroySmartArray(smarty2);
    
    // Make sure smarty1 is good and destroyed (and that destroySmartArray
    // doesn't segfault when passed a NULL pointer).
    smarty1 = destroySmartArray(smarty1);
    
    // Print the empty arrays one last time.
    printf("\n-- SMART ARRAY 1: --\n");
    printSmartArray(smarty1);
    
    printf("\n-- SMART ARRAY 2: --\n");
    printSmartArray(smarty2);
    
    return 0;
}

SmartArray *createSmartArray(int length) {
    SmartArray *result = null;
    
    length = (length > DEFAULT_INIT_LEN) ? length : DEFAULT_INIT_LEN;
    result = malloc(sizeof(SmartArray));
    
    // Check if current SmartArray is null
    if(result == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    result->array = malloc(sizeof(char *) * length);
    result->capacity = length;
    result->size = 0;
    
    return result;
}

SmartArray *destroySmartArray(SmartArray *smarty) {
    int i;
    
    // Check if current SmartArray is null
    if(smarty == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    for (i = 0; i < smarty->size; i++){
        if(smarty->array[i] == null){
            printf("What are you trying to do here? Playing tricks eh?! \nThis time it's in the array while you are trying to delete!");
            return null;
        }
        free(smarty->array[i]);
    }
    
    free(smarty->array);
    free(smarty);
    
    return smarty;
}

SmartArray *expandSmartArray(SmartArray *smarty, int length) {
    SmartArray *result = null;
    int i;
    
    if(smarty == null || length <= smarty->capacity)
        return null;
    
    //Set up new array
    length = (length > DEFAULT_INIT_LEN) ? length : DEFAULT_INIT_LEN;
    result = malloc(sizeof(SmartArray));
    result->array = malloc(sizeof(char *) * length);
    
    // Check if new SmartArray is null
    if(result == null || result->array == null)
        return null;
    
    result->capacity = length;
    result->size = smarty->size;
    
    //Copy contents from old to new
    for(i = 0; i < smarty->size; i++) {
        result->array[i] = malloc(sizeof(char) * strlen(smarty->array[i]));
        //FIXED - changed from assignment, can't be done with strings, to strcpy
        strcpy(result->array[i], smarty->array[i]);
    }
    
    destroySmartArray(smarty);
    
    return result;
}

SmartArray *trimSmartArray(SmartArray *smarty) {
    SmartArray *result = null;
    int i;
    
    // Check if current SmartArray is null
    if(smarty == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    result = createSmartArray(smarty->size);
    
    //Copy contents from old to new
    for(i = 0; i < smarty->size; i++) {
        result->array[i] = malloc(sizeof(char) * strlen(smarty->array[i]));
        result->array[i] = smarty->array[i];
    }
    
    destroySmartArray(smarty);
    
    return result;
}

char *put(SmartArray *smarty, char *str) {
    int i, length = 0;
    char *strCopy = null;
    
    // Check if current SmartArray is null
    if(smarty == null || str == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    length = (int)strlen(str);
    
    //ADDED - strCopy to get around issue where we're put-ing from the array
    // and we have to expand the array, thus losing the string we were working with
    strCopy = malloc(sizeof(char) * length);
    strcpy(strCopy, str);
    
    
    //CHANGED - while to if, can only ever happen once
    //CHANGED - >= to >
    if((smarty->size + 1) > smarty->capacity)
        smarty = expandSmartArray(smarty, (smarty->capacity * 2) + 1);
    
    //FIXED - Removed '+1's from indexes
    smarty->array[smarty->size] = malloc(sizeof(char) * length);
    strcpy(smarty->array[smarty->size], strCopy);
    
    //FIXED - Added increment of smarty->size that was missing
    smarty->size = smarty->size + 1;
    
    //FIXED - Added -1 to offset the above increment
    return smarty->array[smarty->size-1];
}

char *get(SmartArray *smarty, int index) {
    if(smarty == null){
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    return smarty->array[index];
}

char *set(SmartArray *smarty, int index, char *str) {
    int i;
    int length = 0;
    
    // Check if current SmartArray is null
    if(smarty == null || str == null || smarty->array[index] == null)
        return null;
    
    free(smarty->array[index]);
    
    length = (int)strlen(str);
    
    //CHANGED - >= to >, only expand if necessary, if there's room let it ride
    if((smarty->size + 1) > smarty->capacity)
        smarty = expandSmartArray(smarty, (smarty->capacity * 2) + 1);
    
    //FIXED - added malloc to create space for name
    smarty->array[index] = malloc(sizeof(char) * length);
    for(i = 0; i < length; i++)
        //FIXED - changed 1D index to 'index' from size+1
        //Told you to quit just blindly copying...
        smarty->array[index][i] = str[i];
    
    //FIXED - Removed, this is changing a value in place, no incrementation required
    //smarty->size = smarty->size + 1;
    
    return smarty->array[index];
}

char *insertElement(SmartArray *smarty, int index, char *str) {
    int i;
    //int length = 0;
    
    // Check if current SmartArray is null
    if(smarty == null || str == null || smarty->array[index] == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return null;
    }
    
    //CHANGED - >= to >, only expand if necessary, if there's room let it ride
    if((smarty->size + 1) > smarty->capacity)
        smarty = expandSmartArray(smarty, (smarty->capacity * 2) + 1);
    
    for (i = smarty->size; i >= index; i--)
        strcpy(smarty->array[i+1], smarty->array[i]);
    
    set(smarty, index, str);
    //length = (int)strlen(str);
    
    smarty->size = smarty->size + 1;
    
    return smarty->array[index];
}

int removeElement(SmartArray *smarty, int index) {
    int result = 1;
    
    if(smarty == null){
        printf("What are you trying to do here? Playing tricks eh?!");
        return 0;
    }
    
    free(smarty->array[index]);
    smarty->array[index] = null;
    
    //NOT FINISHED - need to fill in the holes left by removeElement
    
    return result;
}

int getSize(SmartArray *smarty) {
    return smarty->size;
}

void printSmartArray(SmartArray *smarty) {
    int i, j;
    
    if(smarty == null) {
        printf("What are you trying to do here? Playing tricks eh?!");
        return;
    }
    
    //FIXED - i <= smarty->size will segfault
    for(i = 0; i < smarty->size; i++) {
        //Changed to print string because gdb gets verbose...
        printf("%s\n", smarty->array[i]);
        //printf("\n");
    }
}

double difficultyRating(void) {
    double result = 8.5;
    return result;
}

double hoursSpent(void) {
    double result = 3.7;
    return result;
}

