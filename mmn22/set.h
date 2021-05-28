/* _________________________________________________________________________________________________
  |This file containitng the libraries and steady variables needed for the program to run:          |
  |_________________________________________________________________________________________________|
  |            				★The libraries are:★                                                            |
  |▸<stdio.h> - for input and output commandes, such as: scanf, printf.                             |
  |▸<stdlib.h> - for a pointer.                                                                     |
  |▸<string.h> - for a string of members, each member is steady size depending on the input.        |
  |▸<ctype.h> - for a char.                                                                         |
  |            				★Parameters:★                                                                       |
  |▸MAX_SIZE - max size of char.                                                                    |
  |This program is written by Eyal Haimov, I.D - 316316868                                          |
  |_________________________________________________________________________________________________|
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 80
/* _________________________________________________________________________________________________
  |Struct for set: for each group for the fuction (a,b,c,d,e,f) - each group.                       |
  |_________________________________________________________________________________________________|
  |            				★Parameters:★                                                                       |
  |▸(int) arr - array for the numbers.                                                              |
  |▸(int) sum - summary in order to see if the array is empty                                       |
  |_________________________________________________________________________________________________|
*/
typedef struct set{
	int arr[128]; /*0-127 cells*/
	int sum;
} set;
/* _________________________________________________________________________________________________
  |Struct for string: for the commands: read_set, calls the method and their helper fuction.        |
  |This struct creating an array of the fuctions names and their values.                            |
  |_________________________________________________________________________________________________|
  |            				★Parameters:★                                                                       |
  |▸(char) *name - string: the name of the fuction.                                                 |
  |▸(void) *fpointer - inputting the user data: fuction names, an array of numbers.                 |
  |_________________________________________________________________________________________________|
*/
/*declaration for the helper and the regular fuctions*/
void helper_read_set(char*);
void helper_print_set(char*);
void helper_three_operator(char*);
void helper_stop(char*);
void reset(set *x);
void read_set(set *p,int arr[], int amount);
void print_set(set *x);
void union_set(set *a,set *b, set *c);
void intersect_set(set *a,set *b, set *c);
void sub_set(set *a,set *b, set *c);
void symdiff_set(set *a,set *b, set *c);
void stop(void);
