#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 60

/* _________________________________________________________________________________________________
  |This file containitng the libraries and steady variables needed for the program to run:          |
  |            				★The libraries are:★                                                            |
  |▸<stdio.h> - for input and output commandes, such as: scanf, printf.                             |
  |▸<ctype.h> - in order to input characters.                                                       |
  |▸<stdlib.h> - for commands to resize the memory block to 60 lines, and for a pointer.            |
  |▸<string.h> - for a string of members, each member is steady size depending on the input.        |
  |                                    ★the steady variables are:★                                                   |
  |▸line_size - the size of each line (definded for this task as 60 each characters each line).     |
  |This program is written by Eyal Haimov, I.D - 316316868                                          |
  |_________________________________________________________________________________________________|
*/

/*
defining a structure for list: using a parameter to define the size of lines, and pointing the next list.
▸(char)buf - defining line size.
*/
typedef struct list_node{
	char buf[LINE_SIZE+1]; 
	struct list_node *next; /*pointing to the next structure*/
} list;

/* declarations for the fuctions in order to avoid using them again in the file - Mytext.c*/
void printText(int method, char * buffer, list * head);
int readText(int method, char * buffer, list * head);
