/*
 Programmer: Eric Willoughby
 Professor: Hunchuck
 C programming
 COP 2220
 EXAM 2
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char c1 = '';
    char c2 = '';
    int currLetter = 0, i = 0;
    int wordCounter = 0;
    char word[20];
    char wordChecks[50][20] = {{0}};
    int numWord = 0;
    int flag = 1;
    FILE *file1 = fopen("./Resume_Words.txt", "r");
    FILE *file2 = fopen("./Dummy_Resume.txt", "r");

    if(file1 == NULL || file2 == NULL) {
        puts("Error: File is missing...");
        exit(0);
    }

    while(c1 != EOF) {
        c1 = fgetc(file1);
        if(c1 != ' ' && c1 != '.' && c1 != ':' && c1 != ',') {
            wordChecks[wordCounter][i++] = c1;
        }
        else {
            wordCounter++;
            i = 0;
        }
    }
    fclose(file1);

    i=0;

    do {
        c2 = fgetc(file2);
        if(c2 != ' ' && c2 != '.' && c2 != ':' && c2 != ',')
        {
            word[i++] = c2;
        }
        else
        {

            for (i = 0 ; i < 20; i++)
            {
                word[i] = '\0';
            }

            i = 0;
            printf("%s ", word);


            for(wordCounter = 0; wordCounter < 20; wordCounter++)
            {
                for(currLetter = 0; currLetter < 20-1 && flag; currLetter++)
                {
                    if(wordChecks[wordCounter][currLetter + 1] != '"')
                    {
                        if(word[currLetter] != wordChecks[wordCounter][currLetter + 1])
                        {
                            flag = 0;
                        }
                    }
                    else
                        break;
                }
                if(flag)
                {
                    numWord++;
                }
                    flag = 1;
            }
        }
    }while(c2 != EOF);

    fclose(file2);

    printf("\n\nThere are %i words in your file\n", numWord);
    system ("pause");

    return 0;
}//end of main
