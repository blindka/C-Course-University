#include "set.h"
set a, b, c, d, e, f;
struct {
	char *name; /*string*/      
	void (*fpointer)(char*); /*pointing at fuction - inputting the user data - {set "name", "numbers"} */ 
} command[]={	{"read_set",helper_read_set}, /* creating an array (matrix) of the fuction names, and their values*/
	{"print_set",helper_print_set},
	{"union_set",helper_three_operator},
	{"intersect_set",helper_three_operator},
	{"sub_set",helper_three_operator},
	{"symdiff_set",helper_three_operator},
	{"stop",helper_stop},
	{"",NULL} 
};
/* _________________________________________________________________________________________________
  |This fuction is inputting the text and choosing which command to run.                            |
  |We read each char until the EOF - and we input each char to the string.                          |
  |The options are: read,print,union,intersect,sub,symdiff or to stop.                              |
  |First we reset the entire sets - make sure the entire value of memebrs is 0.                     |
  |The for loop go throught 7 times: for each command - and the user chooses one.                   |
  |If the commands doesn't exist it prints an error.                                                |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                         |
  |▸(int) i - using as indicates for the index in the array - first loop of for.                    |
  |▸(int) read_char - using to indicates which char we are on right now.                                 |
  |▸(char) user - the user input.                                                                   |
  |_________________________________________________________________________________________________|
*/
int main()
{
	int i = 0;
	int read_char;
	char user[80];	
	printf(" __________________________________________________\n");
	printf("|Please enter a commands accordingly:              |\n");
	printf("|Each commands will execute after typed separately |\n");
	printf("|             ✯ The commands are:✯                 |\n");
	printf("|->read_set                                        |\n");
	printf("|->print_set                                       |\n");
	printf("|->union_set                                       |\n");
	printf("|->intersect_set                                   |\n");
	printf("|->sub_set                                         |\n");
	printf("|->symdiff_set                                     |\n");
	printf("|->stop                                            |\n");
	printf("|__________________________________________________|\n");
	/*reset the sets*/	
	reset(&a);
	reset(&b);
	reset(&c);
	reset(&d);
	reset(&e);
	reset(&f);
	while(1) /* 1!=0 - so the while will continue, until the user will type the fuction stop*/
	{
		printf("\n\nplease enter command:\n");
		if(scanf("%s",user)==1)
		{
			for(i=0;command[i].fpointer!=NULL;i++)
			{
			if(strcmp(user,command[i].name)==0) /*if it found the name of fuction - calls it*/
				break;
			}
		if(command[i].fpointer==NULL)
		{	
		printf("\nThis command doesn't exist!\n");
		while ((read_char = getchar()) != '\n');
		continue;
		}else{
		(*(command[i].fpointer))(user);
		}
		}else{
			printf("\nend of file before stop command.\n");
			exit(0);
		}
		 /*end of else*/
	} /*end of while*/
} /*end of main*/
/* _________________________________________________________________________________________________
  |This fuction is helper to sort the user input: the name of each set and numbers.                 |
  |The input comes from the fuction: getSets.                                                       |
  |We seperate the char in the string by {set,name set, number, comma etc}.                         |
  |We seperate by using strtok to seperate the string by make a condition if there is comma a new   |
  |line will seperate it the rest of the string, creating: SET A,                                   |
  |                                                             1,                                  |
  |                                                             2,                                  |
  |                                                             -1                                  |
  |The fuction checks by using if: the input is SET X (X - group name: a,b,c,d,e,f).                |
  |Afterwards commas seperating between each set: SET A,SET B.                                      |
  |We make sure to go over each wrongs case:                                                        |
  |If there is comma in illegal space it will print error outout.                                   |
  |If there is text after we used the command propely and added uncessary text it will print error. |
  |If the set isn't a correct one not: a,b,c,d,e,f it will print error.                             |
  |If the value of interger is above 128 or less than 0, it will print error: out of range.         |
  |If the name of set memebers isn't integer it will prints an error.                               |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                         |
  |▸(int) comma - counter for each comma in the user input.                                         |
  |▸(int) i - counter for the for loop.                                                             |
  |▸(int) j - counter for the array.                                                                |
  |▸(int) k - index for token ("new text after changes")                                            |
  |▸(int) s - reducing space.                                                                       |
  |▸(char)* str - gets the set name for the fuction: getsets.                                       |
  |▸(char)* strings - contain the entire string.                                                    |
  |▸(char) s[2] - check if there is a comma to seperate the text, after each set there is comma.    |
  |▸(char) token - gets the first token = the first comma.                                          |
  |▸(set)* p - containt each set.                                                                   |
  |_________________________________________________________________________________________________|
*/
void helper_read_set(char* cmd)
{		
	int i = 0, j = 0, storage = 0, k = 0, s = 0;
	int arr[128];	
	char strings[4];/*max number have 3 digits, and we have \0 at the end - so 4*/
    char cut[MAX_SIZE] = "";
   	char *token; /* get the first token */	
	set *p;
	char str[MAX_SIZE] = "";
    fgets(str, MAX_SIZE, stdin); 
    printf("\nenterd command:\n%s%s",cmd,str);
	for(i=0;i<strlen(str);i++)
	{
		if(str[i] == ',' && str[i-1] == ',') /*checking if there is two commas in a row*/
		{
		printf("\nMultiple consecutive commas\n");
		return;
		}
	}
	i = 0; /*to reset the i before checking the sets and commas*/
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	}
	if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='A'))
		p=&a;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='B'))
		p=&b;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='C'))
		p=&c;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='D'))
		p=&d;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='E'))
		p=&e;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='F'))
		p=&f;
	else{
	printf("\nUndefined set name\n");
	return;
	}
	i+=4;
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	}
	if(str[i]!=',')
	{
	printf("\nMissing Comma\n");
	return;
	}
	i++;
	for(k=i,s=0;k<strlen(str);k++)/* 5 = 4(SETX)+1(,)*/
	{
		if (!isspace(str[k])) /*reducing space*/
		{
		cut[s]=str[k];
		s++;
		}
	}
	str[s] = '\0';
	token = strtok(cut, ","); /*we seperate the input to different parts*/
	j=0;
	while(token!=NULL)
	{	
		storage = atoi(token);
		sprintf(strings,"%d",storage);	
		if(strcmp(token,strings) != 0) /*taking the number from a string -> string and token are different*/
		{
			printf("\nInvalid set member - not an integer\n");
			return;
		}
		if((storage>127 || storage<0) && storage!=-1) /*checking if the members is out of the range: 0-128*/
		{
		printf("\nInvalid set member - value out of range\n");	
		return;
		}
		arr[j] = storage;
		if(arr[j]==-1)
			break;
		j++;
		token = strtok(NULL, ",");
	}
	if(arr[j]!=-1)
	{
		printf("Missing last member -1");
		return;
	}
	k=2;
	while(isspace(token[k])) /*checking after the -1, k=2, 0=-, 1=1*/
	{
		k++;
	}
	if(token[k]!='\0')
	{
		printf("\nExtraneous text after end of command\n");
		return;
	}
	if(p==NULL)
	{
		printf("\nMissing parameter\n");
		return;
	}
	read_set(p,arr,j);
}
/* _________________________________________________________________________________________________
  |This fuction is prints the set the user inputs.                                                  |
  |The input comes from the fuction: getSets.                                                       |
  |the foor loop goes over the entire text to see if there is two commas, if so prints error.       |
  |The while loop make sure there isn't any empty spaces in the text.                               |
  |The fuction checks by using if: the input is SET X (X - group name: a,b,c,d,e,f).                |
  |Afterwards commas seperating between each set: SET A,SET B.                                      |
  |We make sure to go over each wrongs case:                                                        |
  |If there is comma in illegal space it will print error outout.                                   |
  |If there is text after we used the command propely and added uncessary text it will print error. |
  |If the set isn't a correct one not: a,b,c,d,e,f it will print error.                             |
  |Then we check for each single error:                                                             |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                               |
  |▸(int) i - counter for the for loop.                                                             |
  |▸(char)* str - gets the set name for the fuction: getsets.                                       |
  |▸(set)* p - containt each set.                                                                   |
  |_________________________________________________________________________________________________|
*/
void helper_print_set(char* cmd)
{
	int i = 0;
	set *p;
	char str[MAX_SIZE] = "";
    fgets(str, MAX_SIZE, stdin);
    printf("\nenterd command:\n%s%s",cmd,str); 
	for(i=0;i<=strlen(str);i++)
	{
		if((str[i]==',')&&str[i-1]==',') /*checking if there is two commas in rows*/
		{
		printf("\nMultiple consecutive commas.\n");
		return;
		}
	}
	i = 0; /*to reset the i before checking the sets and commas*/
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	}
	if(str[i]==',')
	{
		printf("\nillegal comma\n");
		return;
	}
	if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='A'))
		p=&a;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='B'))
		p=&b;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='C'))
		p=&c;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='D'))
		p=&d;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='E'))
		p=&e;
	else if((str[i]=='S') && (str[i+1]=='E') && (str[i+2]=='T') && (str[i+3]=='F'))
		p=&f;
	else{
	printf("\nUndefined set name\n");
	return;
	}
	i+=4;
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	} /*end of while*/				
	if(str[i]!='\0')
	{
		printf("\nExtraneous text after end of command\n");
		return;
	}
	if(p==NULL)
	{
		printf("\nMissing parameter\n");
		return;
	}
	print_set(p);
}
/* _________________________________________________________________________________________________
  |This fuction is unifed two group and output to the other(to c).                                  |
  |The input comes from the fuction: getSets.                                                       |
  |the foor loop goes over the entire text to see if there is two commas, if so prints error.       |
  |The while loop make sure there isn't any empty spaces in the text.                               |
  |The fuction checks by using if: the input is SET X (X - group name: a,b,c,d,e,f).                |
  |Afterwards commas seperating between each set: SET A,SET B.                                      |
  |We make sure to go over each wrongs case:                                                        |
  |If there is comma in illegal space it will print error outout.                                   |
  |If there is text after we used the command properly and added uncessary text it will print error.|
  |If the set isn't a correct one not: a,b,c,d,e,f it will print error.                             |
  |Then we check for each single error:                                                             |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                               |
  |▸(int) i - counter for the for loop.                                                             |
  |▸(int) j - counter in order to get the value of each set separately.                             |
  |▸(char)* str - gets the set name for the fuction: getsets.                                       |
  |▸(set)* pointer - containt each set.                                                             |
  |_________________________________________________________________________________________________|
*/
void helper_three_operator(char* cmd)
{
	int i = 0, j = 0;
	set *pointer[3];
	char str[MAX_SIZE+1] = "";
    	fgets(str, MAX_SIZE, stdin); 
    	printf("\nenterd command:\n%s%s",cmd,str);
	for(i=0;i<=strlen(str);i++)
	{
		if((str[i]==',')&&str[i-1]==',') /*checking if there is two commas in rows*/
		{
		printf("\nMultiple consecutive commas\n");
		return;
		}
	}
	i = 0; /*to reset the i before checking the sets and commas*/
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	}
	if(str[i]==',')
	{
		printf("\nillegal comma\n");
		return;
	}
	for(j=0;j<=2;j++)
	{	
		if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='A'))
			pointer[j]=&a;
		else if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='B'))
			pointer[j]=&b;
		else if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='C'))
			pointer[j]=&c;
		else if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='D'))
			pointer[j]=&d;
		else if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='E'))
			pointer[j]=&e;
		else if((str[i]=='S')&&(str[i+1]=='E')&&(str[i+2]=='T')&&(str[i+3]=='F'))
			pointer[j]=&f;
		else{			
			printf("\nUndefined set name\n");
			return;
		}
		i+=4;
		while(isspace(str[i]))
		{
			i++; /* skipping the uncessary chars*/
	   	} /*end of while*/	
		if(j!=2 && str[i]!=',')
			printf("\nMissing Comma\n");
		i++;
		while(isspace(str[i]))
		{
			i++; /* skipping the uncessary chars*/
	   	} /*end of while*/				
	} /*end of for*/
	if(str[i]!='\0')
	{
		printf("\nExtraneous text after end of command\n");
		return;
	}
	if(pointer[0]==NULL||pointer[1]==NULL||pointer[2]==NULL)
	{
		printf("\nMissing parameter\n");
		return;
	}
	
	if(strcmp(cmd,"union_set")==0)
		union_set(pointer[0],pointer[1], pointer[2]);
	else if(strcmp(cmd,"intersect_set")==0)
		intersect_set(pointer[0],pointer[1], pointer[2]);
	else if(strcmp(cmd,"sub_set")==0)
		sub_set(pointer[0],pointer[1], pointer[2]);
	else
		symdiff_set(pointer[0],pointer[1], pointer[2]);
}
/* _________________________________________________________________________________________________
  |This fuction is stop and doesn't print anything.                                                 |
  |The input comes from the fuction: getSets.                                                       |
  |We make sure to go over each wrongs case:                                                        |
  |If there is text after we used the command properly and added uncessary text it will print error.|
  |Then we check for each single error:                                                             |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                               |
  |▸(int) i - counter for the for loop.                                                             |
  |▸(char)* str - gets the set name for the fuction: getsets.                                       |
  |_________________________________________________________________________________________________|
*/
void helper_stop(char* cmd)
{
	int i = 0;
	char str[MAX_SIZE] = "";
    fgets(str, MAX_SIZE, stdin);
    printf("\nenterd command:\n%s%s",cmd,str); 
	while(isspace(str[i]))
	{
		i++; /* skipping the uncessary chars*/
   	}
	if(str[i]!='\0')
	{
		printf("\nExtraneous text after end of command\n");
		return;
	}
	stop();
}
