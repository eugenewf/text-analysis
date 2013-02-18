/* include statements (libraries) format: #include <target.h> */
/* include statements (local file) format: include "target.h" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function definitions format: type name(args); */
int getfilesize(FILE* thefile);
char* copyfile(FILE* thefile);

/* define statements format: */



/* global variable declarations format: type name= initial_value; */



/* description of main */
/* Get a file, print it back to screen. */

/* Begin main */
int main (int argc, char **argv)
{
/* Declare main function variables format: type name= initial_value; */
FILE* thefile = fopen(argv[1],"r");
char* document = 0;
int i = 0;



	if (argc != 2) 
	{
		fprintf (stdout, "The wrong number of arguments were entered. Please try again.\n");
		return 0;
	}

	
	if (thefile == NULL)
	{
		fprintf (stdout, "The file could not be opened. Please check the file name and try again.\n");
		return 0;
	}
	
	/* copy file to document string so the file can be closed */
	document = copyfile(thefile); /* MALLOC */ 

	
	/* print the file */ 
	while (document[i]!= '\0')
	{
		fprintf (stdout, "%c", document[i]);
	}
	fprintf(stdout, "\n");
	
	
	
	

free(document);
/* NOTE: check to make sure you've freed all you heap memory */
return 0;
}




/* 
Returns the size of the input file. 
NOTE: 
 Any file with more than zero characters will include an extra character(presumably for the EOF (EndOfFile) character).
*/
int getfilesize(FILE* thefile)
{
int error=0;
int filesize=0;
	error = fseek(thefile, 0, SEEK_END);
	if (error != 0)
	{
		fprintf (stdout, "The end of the file could not be found. I don't know what you should do if this happens.\n");
		return 0;
	}
	
	filesize = ftell(thefile);
	if (filesize == -1)
	{
		fprintf (stdout, "The size of the file could not be found. I don't know what you should do if this happens.\n");
		return 0;		
	}
	
	error = fseek(thefile, 0, SEEK_SET);
	if (error != 0)
	{
		fprintf (stdout, "The beginning of the file could not be found. I don't know what you should do if this happens.\n");
		return 0;
	}
return filesize;

}


/* copy file to document string so the file can be closed */
char* copyfile(FILE* thefile) /* MALLOC */
{
int filesize;
int i;
int error;

	filesize = getfilesize(thefile);
	char* document = (char *)malloc(sizeof(char) * filesize);
	while(thefile[i]!=EOF)
	{
		document[i]=thefile[i];
		i++;
	}
	document[i] = '\0';
	error = fclose(thefile);
	if (error != 0)
	{
		fprintf (stdout, "The file could not be closed. I don't know what you should do if this happens.\n");
		return 0;
	}
return document;
}














