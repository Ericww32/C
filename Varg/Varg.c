/*
 Mission:   Varg.c
 Author:    Eric Willoughby
 Date:      30 Aug. 2017
 NID:       er052156
*/

#include "Varg.h"
#include <stdio.h>
#include <stdarg.h>

char mostFrequentChar(int n, ...) {
    
    char theBiggy = ' ';
    int lowerAlpha[25] = {0}, max = 0, temp, i;
    
    if(n <= 0) {
        return '\0';
    }
    
    va_list argp;
    va_start(argp, n);
    
    for(i = 0; i <= n; i++){
        if(argp[i] == lowerAlpha[i]){
            if(max < lowerAlpha[i]){
                max = lowerAlpha[i];
            }
        }
    }
    
    theBiggy = max;
    va_end(argp);
    
    return theBiggy;
}// end of mostFrequentChar

char fancyMostFrequentChar(char c, ...) {
    char theBiggy = ' ';
    int lowerAlpha[25] = {0}, max = 0;
    
    if(c == '\0')
        return '\0';
    
    va_list argp;
    va_start(argp, c);
    
    va_end(argp);
    
    return theBiggy;
}// end of fancyMostFrequentChar

double difficultyRating(void) {
    double result = 4.0;
    return result;
}// end of difficultyRating

double hoursSpent(void) {
    double result = 9.5;
    return result;
}// end of hoursSpent
