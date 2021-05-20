/***************************************************
     -  Author: Eric Willoughby
     -  NID:    er052156
     -  Date:   Oct 16, 2017
     -  Mission: ListyString
     -  Due:    Oct 25 by 11:59pm
****************************************************/
#include "ListyString.h"
#include <stdio.h>
#include <stdlib.h>
#define null NULL

int main(int argc, char **argv) {
    int i = 0;

    // First element is the .exe name, so i is set to 1
    for (i = 1; i < argc; i++)
        processInputFile(argv[i]);

    return 0;
}

int processInputFile(char *filename) {
    FILE *file;

    file = calloc((int)filename, sizeof(FILE));
    file = fopen(filename, "r");

    fclose(file);

    return (filename == null) ? 1 : 0;
}

ListyString *createListyString(char *str) {
    ListyString *list;

    if(str == null) {
        list->head = null;
        list->length = 0;

        return list;
    }

    list = calloc((int)str, sizeof(ListyString));
    list->length = (int)str;//strlen(str);
    list->head->data = (int)str;
    list->head->next = null;

    return list;
}

ListyString *destroyListyString(ListyString *listy) {
    if(listy == null || listy->head == null)
        return null;

    free(listy->head);
    free(listy);

    return null;
}

ListyString *cloneListyString(ListyString *listy) {
    ListyString *clonedList;
    char *str = null;

    if(listy == null || listy->head == null) {
        clonedList = createListyString(str);
        return null;
    }

    clonedList = createListyString((int)listy->head->data);

    return clonedList;
}

void replaceChar(ListyString *listy, char key, char *str) {
    int i = 0;
    char *replaced = listy->head->data;

    for(i = 0; i < replaced; i++) {
        if(replaced[i] == key) {
            replaced[i] = str;
        }
    }
}

void reverseListyString(ListyString *listy) {
    if(listy->head->data != null) {
        strrev(listy->head->data);
    }
}

ListyString *listyCat(ListyString *listy, char *str) {
    char myStr = null;

    if(listy == null || listy->head == null) {
        return null;
    }

    myStr = strcat(listy->head->data, str);
    listy->head->data = myStr;

    return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2) {
    if(listy1 == null || listy2 == null) {
        return null;
    }

    if(strcmp(listy1->head->data, listy2->head->data))
        return 1;

    return 0;
}


int listyLength(ListyString *listy) {
    if(listy == null)
        return -1;

    if(listy->head == null)
        return 0;

    return listy->length;
}

void printListyString(ListyString *listy) {
    if(listy == null || listy->head == null)
        printf("(empty string)\n");

    do {
        printf("%c\n", listy->head->data);
        listy->head = listy->head->next;
    }while(listy->head->next != null);
}

double difficultyRating(void) {
    return 9; // really it's over 9000!
}

double hoursSpent(void) {
    return 15;
}
