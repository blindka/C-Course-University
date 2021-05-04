#include "myText.h"
/* _________________________________________________________________________________________________
  |This program inputting from a standart input text containting characters from asci code:         |
  |The amount of characters in the input is unknown and unlimited.                                  |
  |The program must finish reading the input when it idenify in the input state of EOF.             |
  |After reading the entire text (all of the characters), the program will print the text:          |
  |In lines of regular steady size, each line is set to 60 characters.                              |
  |This programs is written by Eyal Haimov, I.D - 316316868                                         |
  |_________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                               |
  |▸(char) buff - using parameter buff to allocations memory for the linked list.                   | 
  |▸(list) head - using parameter head to allocations memory for the buffer.                        |
  |▸(int) method - using integer to select one of two methods (linked list  or buffer).             |
  |_________________________________________________________________________________________________|
  |                                 ★Defining the two fuctions:★                                                      |
  |▸readText with parameter textin - inputting the text, changing the line size accordingly.        |
  |▸printText with parameter textout - output the text (with the size change of lines).             |
  |_________________________________________________________________________________________________|
*/
int main()
{
	char * buff = NULL;
	list * head = NULL;
	int method;
	printf(" __________________________________________________________\n");
	printf("|Please select one of two methods:                         |\n");
	printf("|1. LINKED_LIST                                            |\n");
	printf("|2. BUFFER                                                 |\n");
	printf("|__________________________________________________________|\n");
	scanf("%d",&method);
	/*
	The switch is inputting value of a method (the method the user chooses either linked list or buffer
	After the user selected the method: in each method we using the parameter(buff or head) to allocation the memory
	if the it is null - we will get an error.
	default: if the user inputted other value (not 1 or 2)
	*/
	switch(method)
	{
	case 1: head=(list*)calloc(1,1*sizeof(list));
		if(head==NULL)
		printf("Error: no memory was able to allocation for the linked list");
		break;
	case 2: buff=(char*)calloc(LINE_SIZE+1,1*sizeof(char));
		if(buff==NULL)
		printf("Error: no memory was able to allocation for the buffer");
		break;
	default: printf("Error: Invalid Input!\n");
		exit(0);
	}
	/*
	And then we call for the fuction readtext - we compare it to a random value and then call for the print fuction
	If the value of fuction equals for value ("24" for example) - we will get an error.
	*/
	if(readText(method,buff,head) != 24)
	printText(method,buff,head);
	else
	printf("Error");
	buff ? free(buff) : free(head); /*freeing the parameter buff or head*/
	return 0;
}
/* _______________________________________________________________________________________________________
  |The fuction reads the text and saving in a data structure.                                             |
  |The fuction input parameters as a type of data structure of a string:                                  |
  |and pointing to a data structure - the first allocation will be done first.                            |
  |The fuction increases the data structure as demend while inputting the chara;cters:                    |
  |If we can't accept an extra size increasement by using the fuction calloc/realloc.                     |
  |The fuction stops the input and outputting an error:                                                   |
  |The text that already inputted stays in.                                                               |
  |This fuction doesn't do any output command.                                                            |
  |The size of input is undefined and can use any asci codes except '\0'.                                 |
  |each character in the data structure will be saved besides the character '\n', we need to skip         |
  |him each that he appears and not input him to the data structure.                                      |
  |_______________________________________________________________________________________________________|
  |					★parameters:★                                                                                 |
  |▸(char) temp - the current index we are pointing in the array.                                         |
  |▸(int) i - indicates the current index in each method (list or array).                                 |
  |▸(int) read_char - reading each single char that the user inputs to the program.                       |
  |▸(int) curr_length - using the max size of each line(60) to increase the length of lines accordingly.  |
  |▸(node) newNode - creating new node of a list.                                                         |
  |▸(node) current - indicates the current index in the list.                                             |
  |_______________________________________________________________________________________________________|
*/
int readText(int method, char * buffer, list * head)
{
	char * temp;
	int i = 0, read_char, curr_length = LINE_SIZE;
	list * newNode, *current = head;
	switch(method)
	{
	case 1: while ((read_char = getchar()) != EOF)
		{
		if(read_char=='\n')
			continue;
		else{
			if(i>=LINE_SIZE)
			{
			newNode = (list*)calloc(1,1*sizeof(list));
			if(newNode==NULL)
			printf("Error: no memory was able to allocation for the linked list\n");

			current->next = newNode;
			current = current->next;
			i=0;
			}
			current->buf[i] = read_char;
			i++;
		
		}/*end while*/	
		}
		break;
	case 2: while ((read_char = getchar()) != EOF)
		{
		if(read_char=='\n')
			continue;
		else{
			if(i>curr_length)
			{
			temp = (char*)realloc(buffer,(curr_length+LINE_SIZE)*sizeof(char)+1);
			curr_length += LINE_SIZE;
			if(temp==NULL)
			printf("Error: no memory was able to allocation for the buffer\n");
			buffer = temp;
			}			
			buffer[i] = read_char;
			i++;
		}
		}	
		break;
	default: printf("Error: Invalid Input!");
		exit(0);
	}
	return method;
}
/* _______________________________________________________________________________________________________
  |This fuctions activates after the input is reaching the end (EOF).                                     |
  |The fuction prints the output the text in data structure.                                              |
  |The line of the output will be in constant size of 60 for each line.                                   |
  |The fuction gets the parameters as a type of data structure and pointer to the structure.              |
  |_______________________________________________________________________________________________________|
  |					★parameters:★                                                                                 |
  |▸(int) i - indicates the current index in each method (list or array).                                 |
  |▸(node) current - indicates the current index in the list.                                             |
  |_______________________________________________________________________________________________________|
*/
void printText(int method, char * buffer, list * head)
{
	int i = 0;
	list *current = head;
	/*
	case 1 - using the next index of the list to go over the entire text:
	prints the entire current list, and if there is another one afterwards it will prints it in a new line:
	"s\n", and then the current list will point to the next one, until we reach the end (EOF)
	case 2 - if the parameter i(current index) is smaller then the size of data structure of the method
	then it will print the character and increase the size of the value in parameter i, if the parameter i
	reaches 60, it will devide it by 60, and prints the text afterwards(character 61) in a new line.
	default: if the user inputted other value (not 1 or 2)
	*/
	switch(method)
	{
	case 1: while (current->next != NULL)
		{
		printf("%s\n",current->buf);		
		current=current->next;
		}
		break;
	case 2: while (i<strlen(buffer))
		{
		if(i%LINE_SIZE==0)
			printf("\n");
		printf("%c",buffer[i]);
		i++;
		}
		break;
	default: printf("Error: Invalid Input!\n");
		exit(0);
}
}

