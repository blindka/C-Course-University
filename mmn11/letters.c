#include <stdio.h>
#include <ctype.h>
/* _______________________________________________________________________________________________
  |This program inputting from a standart input text until the end of the input (EOF)              |
  |Using a while loop - it will output the the text by these changes:                              |
  |1.If the begining of a sentence if the first letter is lowercase, it will convert to uppercase  |
  |2.If text between quotation marks will convert every lowercase alphabit letter to uppercase     |
  |3.everywhere in the text (besides the first two conditions) will convert uppercase to lowercase |
  |4.Digits between ('0'-'9') will not output, it will output nothing and skip it (if condition)   |
  |5.every char(aski code) that isn't alphabit letter or digits, will print with no changes        |
  |Parameters: 'startover': checking when it is new sentce and changing to uppercase               |
  |'inprogress' checking when the text is in quatation marks and changing to uppercase             | 
  |'queotes' counting the quotation marks to make sure the char is lowercase and isn't changing    |
  |This programs is written by Eyal Haimov, I.D - 316316868                                        |
   ________________________________________________________________________________________________
*/
int main()
{
	char a;
	int startover = 1;
	int inprogress = 0;
	int queotes = 0;
    printf(" ______________________________________________________________________________________\n");
	printf("|                          Welcome to the text helper:                                 |\n");
	printf("|Every start of sentence will uppercase the letter                                     |\n");
	printf("|Text between quotation marks will convert to uppercase                                |\n");
	printf("|Every uppercase char will turn to lowercase in the text                               |\n");
	printf("|Every sentence ends with a dot(.)                                                     |\n");
	printf("|Sentece can ben longer than one line of input, or entirly empty                       |\n");
	printf("|Sentce can be empty only containting a dot (.)                                        |\n");
	printf("|Please Enter a text - make sure to not enter digit(it will not output and skip them): |\n");
	printf(" ______________________________________________________________________________________\n");
	while(scanf("%c",&a) != EOF) /*input text until end of input (EOF), making sure it isn't digit*/ 
	{
	if(!isdigit(a))
	{
	if((startover || inprogress) && isalpha(a))
	{	
		a = toupper(a);
		startover = 0;
	}
	else{
	if(isalpha(a)) /*changing uppercase char to lowercase*/
	a = tolower(a);
	}
	if(a == '.')
	{
		/*when we have a dot in quotation it will not start new sentence*/
		if(queotes == 1)
		{
		startover = 0;
		}
	startover = 1;
	}
	if(a == '"') /*changing text in quotation marks to uppercase*/
	{
	queotes++;
	inprogress = 1;
		/*making sure when we 2 quotation marks the text after the second one is lowercase*/
		if(queotes == 2)
		{
		inprogress = 0;
		}
	}
	printf("%c",a);
	} /* end of isdigits(a)*/
	} /*end of while*/
	/*every char(aski code) that isn't alphabit letter or digits, will print with no changes*/
	return 0; /* returns nothing when it is digit*/
}
