#include "assembler.h"



/*--------------------------------------------------------------------------------------
	main: This function starts the program.
--------------------------------------------------------------------------------------*/
int main()
{    
	open_files(argc, argv); /* Calls to the open file method to start the process */
    analyze_input(input);	/* Analyze the input from the user. */
    /*REMEMBER TO FREE ALL ALLOCATED MEMORY!!!! */

	return 0;
}
/*--------------------------------------------------------------------------------------------
open argc amount of files given as parameter to main.
	on each of them,  call first pass then second pass.
		if not errors then write output files.
	close file
	free allocated memory for file name/path.
--------------------------------------------------------------------------------------------*/

void open_files(int argc, char *argv[])
{
    FILE *fptr;
    int i = 1;
    char * file_name;
    for(; i < argc; i++)
    {
        file_name = (char *)malloc(strlen(argv[i]) + strlen(".as"));
        if(!file_name)
            print_error("memory allocation failed");
        strcpy(file_name, argv[i]);
        strcat(file_name,".as");
        fptr = fopen(file_name, "r");
        if(!fptr)
        {
            fprintf(stderr, "Couldn't open file %s\n", file_name);
            continue;
        }
        if(!first_pass(fptr) && !second_pass(fptr))
        {
           /* write_output_files(argv[i]);*/
		}
        fclose(fptr); /* Closes the file after reading and frees the file_name string for the next file name */
        free(file_name);
    }
}