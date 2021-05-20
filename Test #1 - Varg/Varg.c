/*
 Varg.c
 Test #1 - Varg
 Created by Eric Willoughby on 7/3/18.
*/

#include "Varg.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void errorMsg(char *msg) {
    fprintf(stderr, "%s", msg);
}

char mostFrequentChar(int n, ...){
    int myArr[25], subScriptNum = 0, p, i, max = 0, j;
    
    if(n <= 0) {
        errorMsg("mostFrequentChar() needs to have a number greater than zero to work!\n");
        n = '\0';
        return n;
    }
    
    va_list myList;
    va_start(myList, n);
    
    for (i = 0; i < n; i++) {
        p = va_arg(myList, int);
        
        if(p < 'a' || p > 'z') {
            errorMsg("mostFrequentChar() needs to have a char between lowercase a-z to work!\n");
            return 0;
        }
        
        subScriptNum = p - 'a';
        myArr[subScriptNum]++;
        
        for(j = 0; j <= sizeof(myArr); j++) {
            if(myArr[j] > max)
                max = myArr[j];
        }
    }
    
    va_end(myList);
    
    return (char)max;
}

char fancyMostFrequentChar(char c, ...){
    char result = ' ';
    int myArr[26], subScriptNum = 0, p, n[26], i;
    
    if(c < 'a' || c > 'z') {
        errorMsg("fancyMostFrequentChar() needs to have a char between lowercase a-z to work!\n");
        return 0;
    }
    
    va_list argp;
    va_start(argp, c);
    
    for (i = 0; i < sizeof(n); i++) {
        p = va_arg(argp, int);
        subScriptNum = p - 'a';
        myArr[subScriptNum]++;
    }
    
    va_end(argp);
    p = 0;  // I will now use p as my biggest number finder by
            // comparing it to the previous number
    for(i = 0; i <= sizeof(myArr); i++) {
        if(myArr[i] > p)
            p = myArr[i];
    }

    return result;
}

double difficultyRating(void){
    return 5.0;
}

double hoursSpent(void){
    return 2.0;
}

int main() {
//    mostFrequentChar(0, 'm', 'n', 'm', 's');
    mostFrequentChar(4, 'a', 'a', 't', 't');
    mostFrequentChar(5, 'a', 'b', 'b', 'a', 'c');
    
    // fancyMostFrequentChar('a', 'b', 'b', 'a', 'c');
    
    return 0;
}

/*****************************************
 
 char getMaxOccuringChar(char* str) {
    // Create array to keep the count of individual
    // characters and initialize the array as 0.
    // Initialize max count and result and then construct
    // character count array from the input string.
    int count[256] = {0}, max = -1, len = strlen(str);
    char result; 
 
    for (int i=0; i<len; i++)
        count[str[i]]++;
 
    // Traversing through the string and maintaining
    // the count of each character
    for (int i = 0; i < len; i++) {
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }
 
    return result;
 }
 
 ****************************************/
