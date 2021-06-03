/*
Kfir Sibirsky	316317221
=====================================================================================================

=====================================================================================================
*/

#include "first_pass.h"

void print_symbol(symbol *s) {
	printf("\t%s\t|\t%d\t|\t",s->name,s->address);
	switch (s->type) {
		case EXTERNAL:
			puts("external");
			return;
		case DATA:
			puts("data");
			return;
		case CODE:
			puts("code");
			return;
		case CODE_AND_ENTRY:
			puts("code, entry");
			return;
		case DATA_AND_ENTRY:
			puts("data, entry");
			return;
	}
}

void print_symbol_list(symbol_list *st) {
    symbol *temp = st->head;
    printf("--------------------------------------------------\n");
	printf("\tSYMBOL\t|VALUE (decimal)|\tATTRIBUTES\n");
	printf("--------------------------------------------------\n");
    while (temp != NULL) {
        print_symbol(temp);
        temp = temp->next;
    }
}
/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void add_to_symbol_table (symbol_list *st, char * name, int addr, Sym_Type ty)
{
    symbol * new_node = (symbol*) malloc(sizeof(symbol));
    symbol *last = st->head;
  
    new_node->name  = name;
    new_node->address  = addr;
    new_node->type  = ty;
    new_node->next = NULL;
 
     if (st->head == NULL)
       st->head = new_node;
    else {
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
    st->count++;
    return;   
}
/**
 * Preforms the first pass on the given file, searching for most of the syntax errors,
 * and translating most of the .as file into machine code
 * @param fptr - a pointer to the given file
 * @return ERROR or OK, according to the correctness of the file's syntax
 */
int first_pass(FILE *fptr)
{
   
    /*
    is instruction?
    ===============
		-	R?
				--	add?/sub?/and?/or?/nor? 	 (3 operands: $reg,$reg,$reg)
				--	move?/mvhi?/mvlo?			 (2 operands: $reg,$reg)
		-	I?
				--	addi?/subi?/andi?/ori?/nori? (3 operands: $reg,immed,$reg)
				--	beq?/bne?/blt?/bgt?			 (3 operands: $reg,$reg,lable)
				--	lb?/sb?/lw?/sw?/lh?/sh?		 (3 operands: $reg,immed,$reg)
		-	J?
				--	jmp?						 (1 operand: lable / $reg)
				--	la?							 (1 operand: lable)  
				--	call?						 (1 operand: lable)
				--	stop?						 (0 operands = NO OPERANDS!)  			
					
    */
    char line[MAX_LINE_LEN],first[MAX_LABEL_LEN]="",second[MAX_LABEL_LEN]="", cpy_str[MAX_LINE_LEN]="", *cpy_ptr, *sus;
    int count = 0, status = 0, def_error = 0, label_len=0,i,first_char_after_colon;
    IC = 0, DC = 0;
	symbol_list *symbol_table = calloc(1, sizeof(symbol_list));
    for(line_num = 1; fgets(line, LINE_LEN, fptr); line_num++) /* Scanning through each line of the file */
    {
        strcpy(cpy_str,line);
		cpy_ptr = cpy_str;
		/* Skip unnecessary white spaces at the start of the input. */
		cpy_ptr += skip_white_spaces_start(cpy_ptr);
		/* Check if the input is a blank line. */
		if (cpy_ptr[0] == '\n') 
		{
			printf("Blank line was entered.\n");
			status=ERROR;
		}
		if (cpy_ptr[0] == ';') 
		{
			printf("comment, skip current line and continue to next line in file.\n");
			status=ERROR;
		}
		while(!isspace(cpy_ptr[count])) {/* getting first "token". (sus label) */
	    count++;
	    } 
	    strncpy(first,cpy_ptr,count);
	    
	    sus = first;
		/* Skip the first token. */
	    cpy_ptr += count;
	    first_char_after_colon = cpy_ptr[0];
		/* Skip unnecessary white spaces between first and second token. */
		cpy_ptr += skip_white_spaces_start(cpy_ptr);
	    count = 0;
	    
		while(!isspace(cpy_ptr[count])) {/* getting second "token". (sus cmd name) */
	    	count++;
	    }
	    strncpy(second,cpy_ptr,count);
	    
		status=is_label(first, instructions, directives, symbol_table, &label_len);
		if(status == -1)/* Error in label - NO need to check in line more errors, ONLY to go to next line. */{
			continue;
		if(status == 1)/* VALID LABEL, SKIP to second token. */
		{
			/* Expecting white space (one or more). */
			if(!isspace(first_char_after_colon))
			{
				printf("ERROR! Non white space character right after label's colon.");
				continue;
			}
			sus = second;
		}
		/* as of now, either:
		 * sus = second (because valid label).
		 * OR
		 * sus = first (because NO label).  */
		 
		if(!strcmp(sus, ".db") || !strcmp(sus, ".dh") || !strcmp(sus, ".dw") || !strcmp(sus, ".asciz"))
		{
			if (status == 1) 
			{
		         add_to_symbol_table(symbol_table, first, DC, DATA);
   			}
   			if (strcmp(sus, ".asciz"))/*.db / .dh / .dw*/
   			{
				token = strtok(cpy_str, ",");
			   
				while( token != NULL ) 
				{        
					temp_num = atoi(token);
					/* Check validity of the result from "atoi" function. */
					sprintf(res_to_string, "%d", temp_num);
					if(strcmp(token,res_to_string))
					{
						printf("Invalid set member - not an integer.\n");
						return;
					}
					/* Check range validity of number from list. */
					if(temp_num != -1 && (temp_num<LOWER_BOUND || temp_num>UPPER_BOUND))
					{
						printf("Invalid set member - out of range.\n");
						return;
					}
					/* Only if passed the checks, add the number from the list to the
					 * correct place in the array that will be added to the set. */
					add_to_set[idx]=temp_num;
					idx++;
					count++;
					token = strtok(NULL,",");
				}
   			}
   			/* add to DATA IMAGE (MACHINE CODE).
   			 * DC += NUMBER OF DATA TO STORE. (numbers in array? chars of string? etc...) 
   			 * Continue to next line. */
   			DC +=
 			continue;
		}
		else if(!strcmp(sus, ".entry"))
		{
			/* This is handeled in second pass.
			 * Continue to next line. */
 			continue;
		}
		else if(!strcmp(sus, ".extern"))
		{
			if (status == -2)
				sus = second;
			if (status == 1) 
			{
	   			/* VALID label but need to skip it, not relevant. 
	   			 * Add to symbol table (TYPE = EXTERNAL , ADDR = 0).
	   			 * Now, expecting whitespace (one or more). */
				char third[MAX_LABEL_LEN]="";
				/* Skip the second token. */
				cpy_ptr += count;
				/* Skip unnecessary white spaces between second and third token. */
				cpy_ptr += skip_white_spaces_start(cpy_ptr);
				count = 0;
			
				while(!isspace(cpy_ptr[++count]));/* getting second "token". (sus cmd name) */
				strncpy(third,cpy_ptr,count);
				sus = third;
   			}
			add_to_symbol_table(symbol_table, sus, 0, EXTERNAL);
   			continue;
		}
		else /* MUST BE AN INSTRUCTION. */
		{	
			int found = 0;
			/* check which instruction is it, if even valid? */
			for(i=0;i<NUM_OF_INSTRUCTIONS;i++)
			{
				if(!strcmp(sus, instructions[i].name))
				{
					found = 1;
					break;
				}
			}
			if(found == 0)
			{
				printf("ERROR! Undefined instruction name.\n");
				continue;
			}
			
			if (status == 1) 
			{
	   			/* VALID label. 
	   			 * Add to symbol table (TYPE = CODE , ADDR = IC).
	   			 * Now, expecting whitespace (one or more).
	   			 * Then, instruction / directive name. */

				add_to_symbol_table(symbol_table, first, IC, CODE);
   			 	
	   			 
   			}
   			

 			
   				 			
   			/* add to INSTRUCTION IMAGE (MACHINE CODE).
   			 * IC += 4
   			 * Continue to next line. */
   			 IC += 4;
   			 continue;
		}/*end else MUST BE AN INSTRUCTION. */
	}/* end for loop of lines in files. */
	
	if(!error) /* If the code in the file valid so far, we increase the addresses of the data variables */
	    increase_address_to_data();

	rewind(fptr); /* Rewinds the file for the second pass and returns a flag regarding a spotted error in the file */
	return error;
}
/*--------------------------------------------------------------------------------------------
skip_white_spaces_start: returns the number of white spaces from the start of a given string.
--------------------------------------------------------------------------------------------*/
int skip_white_spaces_start(char *str)
{
	int i=0;
	while(isspace(str[i]) && i<strlen(str))
	{
		i++;
    }
	return i;
}

int is_label(char * tkn ,instruction instructions[] ,char * directives[] ,symbol_list * symbols, int *label_len)
{
    int i=0;
	char str[MAX_LABEL_LEN]="";
	symbol * sptr = symbols->head;
	int col=0;
	if(tkn[strlen(tkn)-1]==':')
	{
	    col = 1;
	    strncpy(str,tkn,strlen(tkn)-1);
	}
	else
	    strncpy(str,tkn,strlen(tkn));
	    
	*label_len=strlen(str);
	
    if(col == 1 && strlen(str)==0)
    {
		printf("ERROR IN LABEL - blank label.");
        return -1;
    }
    if(col == 1 && strlen(str)>MAX_LABEL_LEN)
    {
		printf("ERROR IN LABEL - label has exceeded maximum valid length (%d characters long)",MAX_LABEL_LEN);
	        return -1;
    }
	for(i=0;i<NUM_OF_INSTRUCTIONS;i++)
	{
		if(!strcmp(str, instructions[i].name) || (i<NUM_OF_DIRECTIVES && !strcmp(str, directives[i])))
		{
		    if(col == 1)
		    {
		    	puts("ERROR IN LABEL - symbol cannot be a reserved word!");
    	        return -1;
		    }
	        return -2;
        }
	}
    if(!isalpha(str[0]))
	{
		if(col == 1)
    		puts("ERROR IN LABEL - first char is not alphabetic (lower/upper letter)");
    	else
		    puts("undefined intruction / directive name.(alpha)");
        return -1;
	}
	for(i=1;i<strlen(str);i++)
	{
		if(!isalnum(str[i]))
    	{
    		if(col == 1)
    			printf("ERROR IN LABEL - char at index number %d is not alphanumeric (letter / digit)",i);
        	else
    		    puts("undefined intruction / directive name.(alnum)");
	        return -1;
    	}
    }
	while(sptr)
	{
		if(!strcmp(str, sptr->name) && sptr->type != EXTERNAL )
		{
		    if(col == 1)
		    	puts("ERROR IN LABEL - symbol already exist in symbol table");
		    else
    		    puts("ERROR IN LABEL - missing colon");
            return -1;
		}
		sptr=sptr->next;
	}	
	if(col == 0)
	{
	    puts("ERROR IN LABEL - missing colon");
	    return -1;
	}
	return 1;
}