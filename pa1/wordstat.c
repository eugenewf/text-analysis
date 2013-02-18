
#include "wordstat.h"



int main (int argc, char **argv)
{
/* Declare main function variables */

struct charnode* head;
FILE* thefile;
char c; /* active character*/
struct wordnode* pointer; /*where you are in the word (long words require more than one node)*/ 
struct wordnode* word; /*current word*/
struct charnode* pos; /*position in tree*/
struct varnode* test; /* for testing new words against existing variation*/
struct varnode* lag; /*lags test by one position to allow insertion at end of linked list*/
int i; /* counter variable for iterators*/
	


	if (argc != 2) 
	{
		fprintf (stderr, "The wrong number of arguments were entered. Please try again.\n");
		return 0;
	}
	
	

	
	if (strcmp(argv[1], "-h") == 0)
	{
		fprintf (stdout, "\n\nWordstat has the following usage interface: wordstat <argument>;\n\nwhere <argument> is either the name of the file that wordstat should process,\n\nor -h, which means that wordstat should print this help menu.\n\nWhen invoked with a valid file name, wordstat should find and output \n\nall the unique words in the file in lexicographical order,\n\nalong with the total number of times each word appears (case-insensitive) \n\nand a count of different case-sensitive versions of the word.\n\n");
		return 0;
	}





	thefile = fopen(argv[1],"r");
	if (thefile == NULL)
	{
		fprintf (stderr, "File could not be opened. Please check the file name and try again.\n");
		fprintf (stderr, "%s\n", argv[1]);
		return 0;
	}


	
	head=newcharnode();
	c=fgetc(thefile);

	/* read in file*/
	while (c != EOF)
	{
		/*get the word*/
		if (isalpha(c)!=0)
		{
			word = newwordnode();
			pointer=word;
			i=0;
			while(isalnum(c)!=0)
			{
				if(i==39)
				{
					pointer->next = newwordnode();
				}
				if(i==40)
				{
					pointer=pointer->next;	
					i=0;
				}
									
					pointer->word[i]=c;
					i++;
				
				
				c=fgetc(thefile);
			}
			


			/*put the word in the tree*/
			c=word->word[0];
			pointer=word;
			pos=head;
			i=0;
			while (c!='\0')
			{
				if (pos->next==NULL)
				{
					pos->next=newnextarray();
				}
				if (isalpha(c)!=0)
				{
					if(pos->next->next[tolower(c)-'a']==NULL)
					{
						pos->next->next[tolower(c)-'a']=newcharnode();
					}
					pos = pos->next->next[tolower(c)-'a'];
				}
				if (isdigit(c)!=0)
				{
					if(pos->next->next[tolower(c)-'0'+26]==NULL)
					{
						pos->next->next[tolower(c)-'0'+26]=newcharnode();
					}
					pos = pos->next->next[tolower(c)-'0'+26];
				}
				i++;
				if(i==40)
				{
					i=0;
					pointer=pointer->next;	
				}
				c=pointer->word[i];
			}
			pos->occurcount++;
			
			/* scan variations */
			/* write this method*/
			if(pos->variations==NULL)
			{
				pos->variations=newvarnode();
				pos->variations->thisvar=word;
				pos->varcount++;

			}else
			{
				test=pos->variations;
				i=0; /*using i for a boolean here*/
				while(test != NULL)
				{
					lag=test;
					pointer=test->thisvar;
					if(compare(pointer,word)==1)
					{
						i=1;
						freewordnode(word);
						break;
					}
					test=test->next;
				}
				if(i==0)
				{
					lag->next=newvarnode();
					lag->next->thisvar=word;
					pos->varcount++;
				}
			}
		}
		c=fgetc(thefile);
	}
	/*end file read in*/
	i=fclose(thefile);
	if (i!=0)
	{
		fprintf(stderr, "the file failed to close");
	}


	/*print and free*/
	print(head);
	freecharnode(head);

return 0;
}


/*checks for equality of words*/
int compare(struct wordnode* a, struct wordnode* b)
{
int i;
struct wordnode* pointera;
struct wordnode* pointerb;
i=0;
pointera=a;
pointerb=b;

	while( pointera->word[i] != '\0' || pointerb->word[i] != '\0')
	{
		if(i==40)
		{
			i=0;
			pointera=pointera->next;
			pointerb=pointerb->next;
		}
		if (pointera->word[i] != pointerb->word[i])
		{
			return 0;
		}
		i++;
	}
return 1;
}


/*recursively prints out the tree*/
void print(struct charnode* head)
{
char c;
int i;
int f;
struct wordnode* pointer;

	if(head==NULL)
	{
		return;
	}
	if(head->occurcount!=0)
	{
		pointer=head->variations->thisvar;
		c=pointer->word[0];
		i=0;
		while (c!='\0')
		{
			fprintf(stdout, "%c" , tolower(c));
			i++;
			if(i==40)
			{
				i=0;
				pointer=pointer->next;	
			}
			c=pointer->word[i];
		}
	fprintf (stdout, "\t\t%d\t%d\n", head->occurcount, head->varcount);
	}
	if (head->next != NULL)
	{
		for (i=0;i<36;i++)
		{
			f=i+26;
			if(f>35)
			{			
				f=f-36;
			} /* when I defined the nextarray I put letters first,
 				but it looks like ansi chars has numbers first,
				so this is a workaround to start with 0,1,2,3,.. 
				I'll fix it if I have time. sorry */ 
			if(head->next->next[f] != NULL)
			{
				print (head->next->next[f]);
			}
		}
	}

}






/* each node in the tree contains a character and a count depicting how
many times the word represented as a concatenation of the chars from 
head to the node occurs*/

struct charnode* newcharnode(){
	struct charnode* node = (struct charnode*)malloc(sizeof(struct charnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct charnode));

	node->occurcount=0;
	node->varcount=0;
	node->variations=NULL;
	node->next=NULL;

return node;
}

/*stores the variations on each word in wordnodes*/
struct varnode* newvarnode(){
	struct varnode* node = (struct varnode*)malloc(sizeof(struct varnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct varnode));

	node->thisvar=NULL;
	node->next=NULL;

return node;
}

/*array of next pointers fo charnodes*/
struct nextarray* newnextarray(){
int count;
	struct nextarray* array = (struct nextarray*)malloc(sizeof(struct nextarray));
	if (array ==NULL)
	{
		fprintf (stderr, "out of memory");

	}
	memset(array, 0, sizeof(struct nextarray));

	for(count=0;count<36;count++)
	{
		array->next[count]=NULL;
	}
return array;
}

/*stores individual words, extends the list if the word is too long*/
struct wordnode* newwordnode(){
int count;
	struct wordnode* node = (struct wordnode*)malloc(sizeof(struct wordnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct wordnode));

	node->next=NULL;
	for (count=0;count<40;count++)
	{
		node->word[count]='\0';
	}

return node;
}
/*free charnodes*/
void freecharnode(struct charnode* current){
	if (current->variations != NULL)
	{
		freevarnode(current->variations);
	}
	if(current->next !=NULL)
	{
		freenextarray(current->next);
	}
free(current);
}
/*free varnodes*/
void freevarnode(struct varnode* current){
	if(current->thisvar !=NULL)
	{
		freewordnode(current->thisvar);
	}
	if(current->next != NULL)
	{
		freevarnode(current->next);
	}
free (current);
}
/*free wordnodes*/
void freewordnode(struct wordnode* current){
	if(current->next!=NULL)
	{
		freewordnode(current->next);
	}
free (current);
}
/*free next arrays*/
void freenextarray(struct nextarray* current){
int i;
	if(current->next != NULL)
	{
		for(i=0;i<36;i++)
		{
			if(current->next[i]!=NULL)
			{
				freecharnode(current->next[i]);
			}
		}
	}
free(current);
}
