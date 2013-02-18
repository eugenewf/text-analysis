#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* creates a new charnode including malloc and memset*/
struct charnode* newcharnode();

/* creates a new varnode including malloc and memset*/
struct varnode* newvarnode();

/* creates a new nextarray including malloc and memset*/
struct nextarray* newnextarray();

/* creates a new wordnode including malloc and memset*/
struct wordnode* newwordnode();

/*calls a recursive print method on the tree*/
void print(struct charnode* head);

/* determines whether two words are equal*/
int compare(struct wordnode* a, struct wordnode* b);

/*these next 4 recursively free the whole tree if called on the head node*/
void freecharnode(struct charnode* current);
void freevarnode(struct varnode* current);
void freewordnode(struct wordnode* current);
void freenextarray(struct nextarray* current);


/*main structure of the prefix tree, each node represents one character*/
struct charnode{
	int occurcount;
	int varcount;
	struct varnode* variations;
	struct nextarray* next;
};

/*stores the different variations in a list for comparison*/
struct varnode{
	struct wordnode* thisvar;
	struct varnode* next;
};


/*store one word, either for storing a single variation or when reading into 
the tree. Expandable for words longer than 40 characters*/
struct wordnode{
	char word[40];
	struct wordnode* next;

};

/*used to hold all the next pointers so that the whole array doesn't 
need to be declared until there actually is a next character.*/ 
struct nextarray{
	struct charnode* next[36];
};





























