/*
  Created by Eric Willoughby

  Author Sean Szumlanski
  Lightning Review from class today.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // This is where the getcwd() function resides.
#define DEBUG 1 // Debug verbosity. Higher level prints more messages.
using namespace std;

// ===============================
// 1. Fix the errors in this code:
// ===============================

struct T
{
    int gl;
    char name[6];
};
// One problem is that we don't have a semicolon at the end of the struct
// definition (after the closing curly brace).

int playingWStruct(void)
{
    // T isn't a valid datatype. It's "struct T", unless I use a typedef to
    // make T and alias for struct T.
    struct T data;

    data.gl = 597;
    strcpy(data.name, "Vince");
    // data->name = "Vince";
    // ^ Everything is wrong with this line. It should be a dot (.) operator,
    // not an arrow (->) operator, because 'data' isn't a pointer. Also, we
    // should use strcpy(data.name, "Vince") in order to copy that name over
    // correctly. And finally, "Vince" is too long to copy into the 'name'
    // array, because there's no room for the null sentinel ('\0'). That null
    // sentinel is being written out of bounds of the 'name' array, corrupting
    // who-knows-what in memory.

    printf("%s (%d)\n", data.name, data.gl);
    // ^ Again, this line should use data.name, not data->name.

    // Note: If we had a pointer to a struct, recall that we could access
    // its fields in two ways:
    //
    // struct T *struct_ptr = &data;
    //
    // struct_ptr->gl = 597;
    // (*struct_ptr).gl = 597;
    //
    // ^ Both of those expressions are semantically equivalent.

    return 0;
}


// ===========================================================================
// 2. Write a function called swap() that takes two integer pointers and swaps
//    the values they point to.
// ===========================================================================
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ===========================================================================
// 3. Dynamically allocate an array of n integers. Properly declare the array
//    variable, as well. (Note: We covered this at 9:30 AM, but not 12:30 PM.)
// ===========================================================================

// ==========================================================================
// 3. Dynamically allocate a string that can hold a name that has 10 letters.
//    Give the appropriate declaration for the variable holding the string.
//    (Note: We covered this at 9:30 AM, but not 12:30 PM.)
// ==========================================================================

void arrayStuff(){
    int n = 10;
    int *array;
    char *str;

// Presumably, we would read a value for n here, but to save time,
// n is already given a value.

// Recall that arrays are contiguous in memory. We're setting aside one big
// chunk of memory that is large enough to hold n integers.
    array = (int *)malloc(sizeof(int) * n);

// Don't forget the extra space for the null terminator, '\0'.
    str = (char *)malloc(sizeof(char) * (n + 1));

    free(array);
    free(str);
}
// ==========================================================================
// Side note: The following is TERRIBLE. Don't return the address of a
// statically allocated variable. Statically allocated variables DIE as the
// function returns, so it's dangerous to keep a pointer to them. That memory
// could be reclaimed, repurposed, and reused at any moment.
//
// (Note: We covered this at 12:30 PM, but not 9:30 AM.)
// ==========================================================================

struct T *create_a_struct(void) {
    struct T t;
    return &t;  // :(
}

/****************************************************************************************************/
// String Buffer
/****************************************************************************************************/
// Sean Szumlanski
// COP 3502, Fall 2017

// string-buffer-basic.c
// =====================
// This includes some basic file I/O. For more, see file-read.c, attached as a
// supplement to today's notes.
//
// This code demonstrates how to read from a file until you hit the end of that
// file (EOF), and how to use strlen() in conjunction with malloc() to dynamically
// allocate space for strings. It also has a comment on how to squash what would
// have been a nasty memory leak in the while-loop.
//
// Not all of this was covered in class in detail, but the code is here for you
// if you want to learn from it.

int strBuffer(void) {
    int i;
    char filename[21]; // I'll restrict my filenames to 20 characters.
    char buffer[801]; // I'll restrict the strings in my input file to 800 characters.
    char *word; // I'll use this to hold strings in dynamically allocated space.
    FILE *myFile = NULL;

    // Side Note: In C, assignment statements evaluate to the value being
    // assigned. This will print out 17.
    printf("%d\n", i = 17);

    // Using a variable to store the name of your input file will enable you to
    // print useful error messages about that file in the event that if fails to open.
    strcpy(filename, "input.txt");

    // fopen() returns NULL if it fails to open the file. If that's the case,
    // then the assignment (ifp = fopen(...)) will evaluate to NULL, and the
    // comparison will evaluate to true.
    if ((myFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Could not open %s in main()!\n", filename);
        exit(0);
    }

    // fscanf() returns EOF when it hits the end of a file. Let's keep reading
    // until we hit the end of that file.
    while (fscanf(myFile, "%s", buffer) != EOF) {
        // Create exactly enough space to hold this string elsewhere in memory.
        // strlen() returns the number of characters in a string, and does NOT
        // account for the null terminator, so you still need to +1.
        word = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));

        // Copy the buffer's contents into the newly allocated space.
        strcpy(word, buffer);

        // If you encounter trouble with file I/O, one of the first things you
        // should do is print everything that you're reading, just to make sure
        // your scanf() is working properly. (Here, you could also print the
        // contents of 'buffer' if you're having trouble debugging your code.)
        printf("(read string) %s\n", word);

        // Check your understanding: Do you see why this code has a nasty memory
        // leak if you eliminate this free() statement?
        free(word);
    }
    // There's no need to set word = NULL inside the while-loop, because we'll
    // just overwrite it in the next iteration of the loop. However, when we
    // break out of the loop, we know word points nowhere useful. It's good
    // practice to set it to NULL, accordingly.
    word = NULL;

    // It's good practice to close files when you're finished with them and then
    // set their file pointers to NULL. (This isn't so important when you're
    // about to exit the program, but in case you ever want to re-purpose this
    // main() function for something else, it would be nice to know that it's
    // free of memory leaks.)
    fclose(myFile);
    myFile = NULL;

    return 0;
}

/****************************************************************************************************/
// String Read
/****************************************************************************************************/

// Sean Szumlanski
// COP 3502, Fall 2017

// file-read.c
// ===========
// I don't know if I'll have time to cover this in depth in class this week, but
// here are some intro notes on file I/O in C.
//
// First, I want you to know that if fopen() fails to open a file, it returns
// a NULL pointer. Dereferencing that pointer will cause a segfault, and it is
// one of the most sneaky causes of segfaults in C (because we never expect it
// to happen)!
//
// In this program, we check our file pointer before reading from the file. We
// also print the current working directory so we can check the path where the
// file we're trying to read should be stored. For some reason, that's a big
// deal on Macs; in certain IDEs, the working directory where you need your
// input files ends up being something unexpected (not the directory where your
// program is compiled).
//
// We also see once again in this program that quoted strings are treated like
// memory addresses in C. (Also, recall that string literals are read-only.) For
// example, the panic() function requires a (char *) as its argument, which is a
// memory address. In main(), I call panic() with a quoted string as its
// argument. And it works. This implies that a quoted string evaluates to a
// memory address in C.

// This function is a bit tongue-in-cheek.
void panic(const char *s)
{
    // Print to stderr, just in case normal output is being redirected to a file.
    fprintf(stderr, "%s", s);

    // Exit with a non-normal return value.
    exit(1);
}

// This function should print the current working directory to the screen. You
// need to include unistd.h in order to call the getcwd() function.
void pwd(void) {
    char cwd[1024];

    // getcwd() returns NULL if it can't stat the current working directory
    if (getcwd(cwd, 1024) == NULL)
        fprintf(stderr, "Working directory: (unknown)\n");
    else
        fprintf(stderr, "Working directory: %s\n", cwd);
}

int fileReader(void) {
    char buffer[100];
    FILE *myFile = fopen("input.txt", "r");

    // Print the current working directory. Try this out at home.
    pwd();

    // Check whether your file opened successfully. It's so easy to assume a file
    // opened successfully and then spend an hour trying to figure out why your
    // code is segfaulting!
    if (myFile == NULL)
        panic("ERROR: could not open file in main()\n");

    // Read strings into the buffer until we hit the end of the file. Notice that
    // fscanf() returns the value EOF if it hits the end of a file! (EOF is
    // defined in stdio.h.) So, this loop keeps going until you hit the end of a file.
    while (fscanf(myFile, "%s", buffer) != EOF) {
        if (strcmp(buffer, "Szumlanski"))
            printf("************** Found the name I wanted!\n");

        printf("Reading string: %s\n", buffer);
    }

    // It's good practice close files when you're finished with them.
    fclose(myFile);

    return 0;
}

// Print debug message, as long as its priority meets or exceeds
// the current level of DEBUG verbosity defined above.
void debug(const char *debug_msg, int priority) {
    printf("activated debug\n");

    if (DEBUG >= priority) {
        fprintf(stderr, "%s", debug_msg);
        fflush(stderr);
    }
}

// Print debug message and exit program with error status (non-zero
// return value).
void panic2(const char *err_msg) {
    printf("activated panic2()\n");
    debug(err_msg, 0);
    exit(1);
}

int strPrinter(void) {
    char err_msg[1024], filename[20];
    FILE *ifp = NULL;
    strcpy(filename, "input.txt");

    printf("made it to the top of strPrinter()\n");

    if ((ifp = fopen(filename, "r")) == NULL) {
        sprintf(err_msg, "Attempted to open file: %s\n", filename);
        debug(err_msg, 1);
        panic2("Failed to read input file in main()!\n");
    }
    // Read file.
    // ...
    // Clean up after yourself.
    fclose(ifp);

    printf("ended strPrinter()\n");
    return 0;
}

int main(int argc, const char * argv[]) {
   playingWStruct();
   strBuffer();
   fileReader();
   strPrinter();

   return 0;
}
