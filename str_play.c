/*Eric Willoughby
Professor Hunchuck
Strings
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define pause system("pause")
#define cls system("cls")

void display();
int stringLength(char word[]);
char triWord(char word[]);
char vertical(char word[]);

int main() {
    char word[100];
    int length;
    char reverse;
    char answer;

    printf("give me a word: ");
    scanf(" %s", word);
    cls;

    while(answer != 'Q') {
        display();
        scanf(" %c", &answer);
        answer = toupper(answer);
        cls;

        if (answer == 'A')
        {
            printf("your word is %s \n", word);
            pause;
            cls;
        }
        else if (answer == 'B')
        {
            strrev(word);
            printf("your word is %s \n", word);
            strrev(word);
            pause;
            cls;
        }
        else if (answer == 'C')
        {
            printf("Length of word: %d \n", stringLength(word));
            pause;
            cls;
        }
        else if (answer == 'D')
        {
            vertical(word);
            pause;
            cls;
        }
        else if (answer == 'E')
        {
            triWord(word);
            pause;
            cls;
        }
        else if (answer == 'F')
        {
            return main();
        }
    }puts("well i guess this is goodbye.... bye!\n\n\n\n");

    return 0;
}

void display() {
    printf("A) display string \n");
    printf("B) Reverse that there string!\n");
    printf("C) display the string length\n");
    printf("D) Show it vertically\n");
    printf("E) display string as triangle\n");
    printf("F) Do it again\n");
    printf("Q) Get out!\n");
}//end of display

int stringLength(char word[]) {
   int c = 0;

   while(*(word+c))
      c++;

   return c;
}

//makes a triangle out of word
char triWord(char word[]) {
    int i;
    for(i=0; word[i] != NULL; i++) {
        printf("%.*s\n",i,word);
    }
}

//displays the word vertically
char vertical(char word[]) {
    char vertWord;
    int i;

    for(i=0; word[i] != NULL; i++) {
        vertWord = printf(" %c\n", word[i]);
    }

    return vertWord;
}
