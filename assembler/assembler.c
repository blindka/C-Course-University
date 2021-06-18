/*
Kfir Sibirsky	316317221
Eyal Haimov
=====================================================================================================
This file contains...
=====================================================================================================
*/
#include "utils.h"
#include "assembler.h"


/*--------------------------------------------------------------------------------------
	main: This function starts the program.
--------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{    
    FILE *fptr;
    int file_number;


    for(file_number = 1; file_number < argc; file_number++) /* Scanning argv from the second argument, the first file name to be checked */
    {
        /* Allocate memory for the file's name  including the ".as" ending, to it */
        file_name = (char *)calloc(1,strlen(argv[file_number]) + strlen(".as"));

        if(!file_name)
        {
			printf("ERROR! Memory allocation for the %d%s file name failed.",file_number,eng_ordinal_nums(file_number));
        }
        strcpy(file_name, argv[file_number]);
        strcat(file_name,".as");

        /* Opens the file, if it exists, for reading */
        fptr = fopen(file_name, "r");
        if(!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
        {
			printf("ERROR! Opening the %d%s file (%s) failed.",file_number,eng_ordinal_nums(file_number),file_name);
            continue;
        }
        if(!first_pass(fptr) && !second_pass(fptr))
        {
			puts("ＰＡＳＳＥＳ ＣＯＭＰＬＥＴＥＤ ＳＵＣＣＥＳＳＦＵＬＬＹ!"); 
		    write_output_files(argv[file_number]);
        }
        /* Closes the file after reading and frees the file_name string for the next file name */
        fclose(fptr); 
        free(file_name);
    }

    /*REMEMBER TO FREE ALL ALLOCATED MEMORY!!!! */

	return 0;
}
/*--------------------------------------------------------------------------------------------
eng_ordinal_nums: Returns the proper english ordinal numeration suffix for a given number (n).
--------------------------------------------------------------------------------------------*/
char * eng_ordinal_nums(int n)
{
	if(((n/10)%10)==1)
		return "th";
	switch(n%10)
	{
		case 1: 
			return "st";
		case 2: 
			return "nd";
		case 3: 
			return "rd";
		default:
			return "th";
	}
	return "";
}
/*--------------------------------------------------------------------------------------------
write_output_files: Open files to write the 3 output files (ob, ext, ent) with the same name
                    (name) as the current file being analyzed.
--------------------------------------------------------------------------------------------*/
void write_output_files(char *name)
{
    FILE *fptr;
    char *file_name = (char *)calloc(1,strlen(name) + strlen(".ob"));
    if(!file_name)  /*Allocates memory for the file's name and copies the name and the ending into it */
        printf("memory allocation failed");
    strcpy(file_name, name);
    strcat(file_name, ".ob");
    fptr = fopen(file_name, "w"); /* Opens the file, with writing permission */
    write_ob_file(fptr);
    
    file_name = (char *)calloc(1,strlen(name) + strlen(".ent"));
    if(!file_name)  /*Allocates memory for the file's name and copies the name and the ending into it */
        printf("memory allocation failed");
    strcpy(file_name, name);
    strcat(file_name, ".ent");
    fptr = fopen(file_name, "w"); /* Opens the file, with writing permission */
	write_ent_file(fptr);
    
    file_name = (char *)calloc(1,strlen(name) + strlen(".ext"));
    if(!file_name)  /*Allocates memory for the file's name and copies the name and the ending into it */
        printf("memory allocation failed");
    strcpy(file_name, name);
    strcat(file_name, ".ext");
    fptr = fopen(file_name, "w"); /* Opens the file, with writing permission */
	write_ext_file(fptr);
    free(file_name);  /* The file's name isn't needed anymore */

}
/*--------------------------------------------------------------------------------------------
write_ext_file: Write to the output file (f) the list places (addresses) in the machine code
                in which a symbol that is declared as an external is used.
                (all symbols that appeared as an operand of .external,
                And is characterized in the symbol table as "external") 
--------------------------------------------------------------------------------------------*/
void write_ext_file(FILE * file_to_write_in)
{
    ext *e = external_list->head;
	while(e)
	{
		fprintf(file_to_write_in,"%s %04d\n",e->name,e->address);
		e=e->next;
	}
	fclose(file_to_write_in);
}
/*--------------------------------------------------------------------------------------------
write_ent_file: Write to the output file (f) the list of symbols which declared as an entry
                point (all symbols that appeared as an operand of .entry,
                And is characterized in the symbol table as "data, entry" or "code, entry") 
--------------------------------------------------------------------------------------------*/
void write_ent_file(FILE * file_to_write_in)
{
    symbol *sptr = symbol_table->head;
	while(sptr)
	{
		if(sptr->type == DATA_AND_ENTRY || sptr->type == CODE_AND_ENTRY)
		{
			fprintf(file_to_write_in,"%s %04d\n",sptr->name,sptr->address);
		}
		sptr=sptr->next;
	}
	fclose(file_to_write_in);
}
/*--------------------------------------------------------------------------------------------
write_ob_file: Write to the output file (f) the machine code.
--------------------------------------------------------------------------------------------*/
void write_ob_file(FILE * file_to_write_in)
{
    instruction_node *in = code_image->head;
    directive_node *dn = data_image->head;
    char num_bin[32]="",num_hex[32]="",*pair_hex;
    int pairs_in_line=0,i=0,expected_address=0, parsing  = 0;
    /* print length of code image and length of data image. */
    fprintf(file_to_write_in,"     %d %d\n",ICF-IC_START_ADDR,DCF);
    /* print code image. */
    while (in != NULL)
    {
        if(in->R != NULL)
            int_to_bin_str(*(int*)in->R,32,num_bin);
        else if(in->I != NULL)
            int_to_bin_str(*(int*)in->I,32,num_bin);
        else if(in->J != NULL)
            int_to_bin_str(*(int*)in->J,32,num_bin);
        bin_str_to_hex_str(num_bin,num_hex);
        fprintf(file_to_write_in,"%04d %s\n",in->address,num_hex);
        for(i=0;i<32;i++)
        {
        	num_bin[i]='\0';
        	num_hex[i]='\0';
        }
        in = in->next;
    }
  	/* print data image. */
	expected_address=dn->address;
    while (dn != NULL)
    {
        if(dn->_8_bit != NULL)
            int_to_bin_str(*(int*)dn->_8_bit,8,num_bin);
        else if(dn->_16_bit != NULL)
            int_to_bin_str(*(int*)dn->_16_bit,16,num_bin);
        else if(dn->_32_bit != NULL)
            int_to_bin_str(*(int*)dn->_32_bit,32,num_bin);
    	bin_str_to_hex_str(num_bin,num_hex);
    	        	/*print_directive(dn);
    	        	puts("");*/
        if(pairs_in_line == 0)
        {
			fprintf(file_to_write_in,"%04d ",expected_address);
        }
        /* get the first token */
        pair_hex = strtok(num_hex, " ");
        /* walk through other tokens */
        while(pair_hex != NULL)
        {
		
            if(pairs_in_line<4)
            {
            	if(parsing == 1)
				{
					fprintf(file_to_write_in,"%04d ",expected_address);
				}
                fprintf(file_to_write_in,"%s ",pair_hex);
                pairs_in_line++;
                expected_address++;
            }
            if(pairs_in_line==4)
            {
                pairs_in_line=0;
				parsing = 1;
                fprintf(file_to_write_in,"\n");
            }
            pair_hex = strtok(NULL, " ");
        }
        for(i=0;i<32;i++)
        {
        	num_bin[i]='\0';
        	num_hex[i]='\0';
        }
        parsing  = 0;
        dn = dn->next;
    }
	fclose(file_to_write_in);
}

