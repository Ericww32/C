/*
 Author:    Eric Willoughby
 Mission:   SmartArray.c
 Due:       9/24/17
 NID:       er052156
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"
#define null NULL
int getCap(SmartArray *smarty);

SmartArray *createSmartArray(int length) {
    SmartArray *result = malloc(sizeof(SmartArray));
    
    // Check if current SmartArray is null
    if(result == null)
        return null;

    length = (length > DEFAULT_INIT_LEN) ? length : DEFAULT_INIT_LEN;
    result->array = malloc(sizeof(char*) * length);
        
    if(result == null)
        return null;
    
    result->capacity = length;
    result->size = 0;
    return result;
}

SmartArray *destroySmartArray(SmartArray *smarty) {
//    int i;
    
    // Check if current SmartArray is null
    if(smarty == null)
        return null;
    
//    for(i = 0; i <= getSize(smarty); i++) {
//        if(smarty->array[i] == null) {
//            return null;
//        }
//        free(smarty->array[i]);
//    }
    
    free(smarty->array);
    free(smarty);
    
    return smarty;
}

SmartArray *expandSmartArray(SmartArray *smarty, int length) {
    length = (length > DEFAULT_INIT_LEN) ? length : DEFAULT_INIT_LEN;
    
    // Check if current SmartArray is null
    if(smarty == null || length <= getCap(smarty)) {
        return null;
    } else {
            smarty->capacity = length;

            return smarty;
        }
}

SmartArray *trimSmartArray(SmartArray *smarty) {
    // Check if current SmartArray is null
    if (smarty == null)
        return null;

    if (getCap(smarty) > getSize(smarty))
            smarty->capacity = getSize(smarty);

    return smarty;
}

char *put(SmartArray *smarty, char *str) {
    int strLen, index, newCap;
    char *strInsert;
    
    // Check if current SmartArray and String is null
    if (smarty == null || str == null)
        return null;
    
    if (getSize(smarty) >= getCap(smarty)) {
        newCap = (smarty->capacity * 2) + 1;
        smarty = expandSmartArray(smarty, newCap);
    }
    
    strLen = (int)strlen(str);
    strInsert = malloc((sizeof(char) * strLen) + 1);
    
    if (strInsert == null)
        return null;
    
    strcpy(strInsert, str); // Copied
    index = getSize(smarty);
    smarty->array[index] = strInsert; // Paste
    smarty->size += 1;
    
    return smarty->array[index];
}

char *get(SmartArray *smarty, int index) {
    if(smarty == null)
        return null;

    return smarty->array[index];
}

char *set(SmartArray *smarty, int index, char *str) {
    // Check if current SmartArray is null
    if(smarty == null || str == null || smarty->array[index] == null)
        return null;

    if((getSize(smarty) + 1) >= getCap(smarty))
        smarty = expandSmartArray(smarty, (smarty->capacity * 2) + 1);

    strcpy(smarty->array[index], str);

    return smarty->array[index];
}

char *insertElement(SmartArray *smarty, int index, char *str) {
    int i;
    
    // Check if current SmartArray is null
    if(smarty == null || str == null || smarty->array[index] == null)
        return null;
    
    if((smarty->size + 1) > smarty->capacity)
        smarty = expandSmartArray(smarty, (smarty->capacity * 2) + 1);
    
    for (i = smarty->size; i >= index; i--)
        if(smarty->array[i + 1] != null)
            strcpy(smarty->array[i+1], smarty->array[i]);
    
    set(smarty, index, str);
    smarty->size = smarty->size + 1;
    free(smarty->array[index]);
    trimSmartArray(smarty);
    
    return smarty->array[index];
}

int removeElement(SmartArray *smarty, int index) {
    int result = 1, i;

    if(smarty == null)
        return 0;

    free(smarty->array[index]);
    
    for (i = index; i <= getSize(smarty); i++)
        if(smarty->array[i + 1] != null)
            strcpy(smarty->array[i], smarty->array[i + 1]);
    
    free(smarty->array[getSize(smarty)]);
    trimSmartArray(smarty);

    return (smarty->array[index] == null) ? result : 0;
}

int getSize(SmartArray *smarty) {
    if(smarty == null)
        return 0;
    return smarty->size;
}

int getCap(SmartArray *smarty) {
    if(smarty == null)
        return 0;
    return smarty->capacity;
}

void printSmartArray(SmartArray *smarty) {
    int i;

    if(smarty == null)
        return;
    
    for (i = 0; i < getSize(smarty); i++)
        printf("%s\n", smarty->array[i]);
}

double difficultyRating(void) {
    return 8.5;
}

double hoursSpent(void) {
    return 10;
}
