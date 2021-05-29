/* _________________________________________________________________________________________________
  |This program takes the original file (this file) and prints it content.                          |
  |A while loop gets each character and prints it.                                                  |
  |_________________________________________________________________________________________________|
  |            				★The libraries are:★                                                            |
  |▸<stdio.h> - for input and output commandes, such as: scanf, printf.                             |
  |▸<string.h> - for a string of members, each member is steady size depending on the input.        |
  |_________________________________________________________________________________________________|
  |            				★Parameters:★                                                                       |
  |▸(char) c - parameter to indicate each character in the file.                                    |
  |▸(int) argc - number of argumentes transfered to the operation system.                           |
  |▸(char) argv - pointer to array of string.                                                       |
  |This program is written by Eyal Haimov, I.D - 316316868                                          |
  |_________________________________________________________________________________________________|
*/
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *file;
	char c;
	file = fopen(strcat(argv[0], ".c"), "r"); /*copying the file*/
	/*taking the text from the file and prints it - to get the text from the original file (this file)
	putchar - prints each character from the file*/
	while((c = getc(file)) != EOF)
	{
		putchar(c);
	}
	fclose(file);
	return 0;
}
