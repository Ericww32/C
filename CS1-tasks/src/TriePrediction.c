/***************************************************
     -  Author: Eric Willoughby
     -  NID:    er052156
     -  Date:   Oct 16, 2017
     -  Mission:TriePrediction
     -  Due:    19 Nov by 11:59pm
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

#define NULL null

// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// (Credit: Dr. S.)
TrieNode *createTrieNode(void)
{
    int i;
    TrieNode *n = malloc(sizeof(TrieNode));
    n->count = 0;

    for (i = 0; i < 26; i++)
        n->children[i] = NULL;

    return n;
}

// (Credit: Dr. S.)
void insertString(TrieNode *root, char *str)
{
    int i, index, len = strlen(str);
    TrieNode *wizard;

    if (root == NULL)
    root = createTrieNode();
    // As I mentioned in class, the wizard starts at the root node and spells
    // out the string being inserted as he/she jumps from node to node.
    //(The wizard is acting as a temp pointer.)
    wizard = root;

    for (i = 0; i < len; i++){
        if (!isalpha(str[i])) {
            fprintf(stderr, "Error: \"%s\" contains non-alpha characters and will not be inserted.\n", str);
            return NULL;
        }

        index = tolower(str[i]) - 'a';
        // Before the wizard can move forward to the next node, (s)he needs to
        // make sure that node actually exists. If not, create it!

        if (wizard->children[index] == NULL)
            wizard->children[index] = createTrieNode();
            // Now the wizard is able to jump forward.

        wizard = wizard->children[index];
    }
        // When we break out of the for-loop, the wizard should be at the terminal
        // node that represents the string we're trying to insert.
    wizard->count++;

    return root;
}

TrieNode *buildTrie(char *filename)
{
    TrieNode *root = NULL;
    char buffer[MAX_WORD_LENGTH + 1];
    FILE *ifp;

    if ((ifp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
        return NULL;
    }

    // Insert strings one-by-one into the trie.
    while (fscanf(ifp, "%s", buffer) != EOF)
        root = insert(root, buffer);

    return root;
}

int processInputFile(TrieNode *root, char *filename) {
    /*
    Description: This function takes in the root of a trie and the name of an input file,
    and processes that file according to the description above in Section 3.2, "Command File."
    While we will always specify valid filenames as command line arguments, we might pass invalid
    filenames when unit testing. In the event that a bad filename is passed to this function
    (i.e., the specified file does not exist), this function should simply return 1 without producing any output.

    Output: This function should produce output according to the specification described above in
    Section 3.2 ("Command File"). For additional details or clarification on the output, please be
    sure to refer to the input/output files included with this assignment. Note that this function
    should not produce any output if the input file does not exist.

    Returns: If the specified input file does not exist, return 1. Otherwise, return 0.
    */
	return 0;
}

void stripPunctuators(char *str) {
    int i, len = strlen(str);

    for (i = 0; i < len; i++) {
        if (!isalpha(str[i])) {
            str.erase(i--, 1);
            len = str.size();
        }
    }
 }

TrieNode *destroyTrie(TrieNode *root) {
    int i;

    if(root == null)
        return;

    if(root->count > 0)
        destroy(root->subtrie);

    for (i = 0; children[i] != null; i++)
        destroyTrie(root->children[i]);

    free(root);

	return null;
}

TrieNode *getNode(TrieNode *root, char *str) {
    int strNum; // the strings number

	if(str[0] == '\0')
		return (root->count == 0) ? null : root;

	strNum = str[0] - 'a';

	if (root->children[strNum] != null)
		return getNode(root->children[strNum], str + 1);

    return null;
}

void getMostFrequentWord(TrieNode *root, char *str) {

}

int containsWord(TrieNode *root, char *str) {
    int i, index, len = strlen(str);
    TrieNode *n; //node

    (root == null) ? return 0;
    n = root;

    for(i = 0; i < len; i++) {
        (!isalpha(str[i])) ? return null;
        index = tolower(str[i]) - 'a';
        (n->children[index] == null) ? n->children[index] = createTrieNode();
        n = n->children[index];
    }

    n->count++;

    return (root != null);
}

int prefixCount(TrieNode *root, char *str) {

}

double difficultyRating(void) {
	return 9.0;
}

double hoursSpent(void) {
	return 6.0;
}

int main(int argc, char **argv) {
    for(i = 1; i < argc; i++)
        processInputFile(argv[i]);

    for(i = 1; i < argc; i++)
        TrieNode *root[i] = buildTrie(strcat("corpus0", i));

    for(i = 1; i < argc; i++)
        destroyTrie(root[i]);

	return 0;
}
