#include "utils.h"
#include "second_pass.h"

ext_list *external_list;
extern char *directives[];
extern instruction instructions[];


void print_ext(ext * e) {
	printf("%-4s|%04d|\n",e->name,e->address);
}

void print_ext_list(ext_list *el) {
    ext *temp = el->head;
    if(el->count==0)
    {
        printf("external list empty.\n");
        return;
    }
    printf("----------\n");
	printf("NAME|ADDR|\n");
	printf("----------\n");
    while (temp != NULL) {
        print_ext(temp);
        temp = temp->next;
    }
}
void add_to_ext_list (ext_list * e, char * name, int addr)
{
    ext * new_node = (ext*) malloc(sizeof(ext));
    ext *last = e->head;

    strcpy(new_node->name,name);
    new_node->address  = addr;
    new_node->next = NULL;
 
     if (e->count == 0)
       e->head = new_node;
    else {
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
    e->count++;
    return;   
}

/*--------------------------------------------------------------------------------------------
remove_white_spaces: removes all white spaces from a given string (str).
--------------------------------------------------------------------------------------------*/
void remove_white_spaces(char *str)
{
	int i=0,j=0;
	while(i < strlen(str)) 
	{   
		if (!isspace(str[i]))
		{
		    /* Any non white space character gets moved back to the corresponding index. */
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int second_pass(FILE * fptr)
{
    char line[MAX_LINE_LEN],token[MAX_LABEL_LEN]="",lbl_opr[MAX_LABEL_LEN]="", cpy_str[MAX_LINE_LEN]="", *cpy_ptr;
    int c=0,count = 0, status = 0, error = 0,i,line_num;
	symbol * sptr = symbol_table->head;
	int found = 0;
	external_list = calloc(1, sizeof(ext_list));
    IC = 100;
    DC = 0;
    print_symbol_list(symbol_table);
    print_instruction_list(code_image);
    print_directive_list(data_image);
    for(line_num = 1; fgets(line, MAX_LINE_LEN, fptr); line_num++) /* Scanning through each line of the file */
    {
		for(c=0;c<MAX_LABEL_LEN;c++)
		{
			token[c]='\0';
			lbl_opr[c]='\0';
			cpy_str[c]='\0';
		}
		for(c=0;c<MAX_LINE_LEN;c++)
		{
			cpy_str[c]='\0';
		}
    	cpy_ptr=NULL;
    	count = 0;
    	status = 0; 
    	sptr = symbol_table->head;
    	puts(line);
        strcpy(cpy_str,line);
		cpy_ptr = cpy_str;
		/* Skip unnecessary white spaces at the start of the input. */
		cpy_ptr += skip_white_spaces(cpy_ptr);
		/* Check if the input is a blank line. */
		if (cpy_ptr[0] == '\n' || cpy_ptr[0] == '\0' || cpy_ptr[0] == ';') 
		{
			continue;
		}
		while(count<strlen(cpy_ptr) && !isspace(cpy_ptr[count])) {
	    /* getting first "token". (sus label) */
	    count++;
		}
		strncpy(token,cpy_ptr,count);
		status = is_label(token ,instructions, directives, symbol_table,1);
		if(status == 1)/* VALID LABEL, SKIP to second token. */
		{
			/* Skip the label. */
			cpy_ptr += count;
			/* Skip unnecessary white spaces between label and instruction/directive name. */
			cpy_ptr += skip_white_spaces(cpy_ptr);
			count = 0;
			while(count<strlen(cpy_ptr) && !isspace(cpy_ptr[count])) {
			/* getting instruction/directive name. */
				count++;
			}
			for(c=0;c<MAX_LABEL_LEN;c++)
			{
				token[c]='\0';
			}
			strncpy(token,cpy_ptr,count);
		}
		printf("TOKEN=|%s|\n",token);
		printf("cpy_ptr=|%s|\n",cpy_ptr);
		/* If there WAS label, we skipped it and now TOKEN = instruction/directive name.
		 * If there WAS NOT label, 					 TOKEN = instruction/directive name. */
		/* Skip the instruction / directive name. */
		cpy_ptr += count;
		/* Skip unnecessary white spaces between instruction/directive name and first operand. */
		cpy_ptr += skip_white_spaces(cpy_ptr);
		count = 0;
		while(count<strlen(cpy_ptr) && !isspace(cpy_ptr[count])) {
		/* getting label operand. */
			count++;
		}
		strncpy(lbl_opr,cpy_ptr,count);
 
		if(!strcmp(token, ".db") || !strcmp(token, ".dh") || !strcmp(token, ".dw") || !strcmp(token, ".asciz") || !strcmp(token, ".extern"))
		{
			continue;
		}
		else if(!strcmp(token, ".entry"))
		{
			while(sptr)
			{
				if(!strcmp(lbl_opr, sptr->name))
				{
					found = 1;
					if(sptr->type == DATA)
						sptr->type = DATA_AND_ENTRY;
					else if(sptr->type == CODE)
							sptr->type = CODE_AND_ENTRY;
				}
				sptr=sptr->next;
			}	
			if(!found)
			{
				printf("ERROR! the label %s was not found in symbol table.\n",lbl_opr);
				error=ERROR;
			}
 			continue;
		}
		else /* Instruction is expected. */
		{	
	        instruction_node *temp = code_image->head;
			/* we know which instruction is it.(it is instructions[i].name) 
			 *	-	R?
			 *		--	add?/sub?/and?/or?/nor? 	 (3 operands: $reg,$reg,$reg)   ✔
			 *		--	move?/mvhi?/mvlo?			 (2 operands: $reg,$reg)        ✔
			 *	-	I?
			 *		--	addi?/subi?/andi?/ori?/nori? (3 operands: $reg,immed,$reg)  ✔
			 *		--	bne?/beq?/blt?/bgt?			 (3 operands: $reg,$reg,label)  ✔
			 *		--	lb?/sb?/lw?/sw?/lh?/sh?		 (3 operands: $reg,immed,$reg)  ✔
			 *	-	J?
			 *		--	jmp?						 (1 operand: label / $reg)      ✔
			 *		--	la?							 (1 operand: label)             ✔
			 *		--	call?						 (1 operand: label)             ✔
			 *		--	stop?						 (0 operands = NO OPERANDS!)    ✔   */

			for(i=0;i<NUM_OF_INSTRUCTIONS;i++)
			{
				if(!strcmp(token, instructions[i].name))
				{
					break;
				}
			}
	        switch (i)
	        {
	            case 0: /* add */
	            case 1: /* sub */
	            case 2: /* and */
	            case 3: /* or */
	            case 4: /* nor */
	                /* (3 operands: $reg,$reg,$reg) */
	            case 5: /* move */
	            case 6: /* mvhi */
	            case 7: /* mvlo */
	                /* (2 operands: $reg,$reg) */
	            case 13: /* bne */
	            case 14: /* beq */
	            case 15: /* blt */
	            case 16: /* bgt */
	                /* (3 operands: $reg,$reg,label) */
			    case 23: /* jmp */
			 	   /* (1 operand: $reg/label) */
			    case 24: /* la */
			    case 25: /* call */
			       /* (1 operand: label) */
				case 26: /* stop */
				    /* i = 0-4   reached here no problem.
				     * i = 5-7   reached here no problem. 
				     * i = 13-16 reached here no problem. 
				     * i = 23    reached here no problem. 
				     * i = 24-25 reached here no problem. 				        
				     * i = 26    reached here no problem.*/ 

					while (temp != NULL)/* code image list not ended */
					{printf("temp->address=|%d|\n",temp->address);
						if(temp->address==IC)/* found corresponding instruction node in code image to current line. */
						{printf("found addres=|%d|\n",temp->address);
							if(temp->partial.bit == 1)/* machine code in the instruction node is partial. */
							{
								if(i >= 13 && i <= 16)/* bne / beq / blt / bgt */
								{
									/* Since all of the lines are grammatically correct, we can remove all white spaces.  */
									remove_white_spaces(cpy_ptr);
									/* Get string from last comma. */
									cpy_ptr=strrchr(cpy_ptr, ',');
									/* Skip ',' at start. */
									cpy_ptr++;
									/* getting label operand. */
									strcpy(lbl_opr,cpy_ptr);
									printf("lbl_opr=|%s|\n",lbl_opr);
									while(sptr)
									{
										if(!strcmp(lbl_opr, sptr->name))
										{
											found = 1;
											if(sptr->type == EXTERNAL)
											{
												printf("ERROR! the label %s is external and is used in %s instruction.\n",lbl_opr,token);
												error=ERROR;
												continue;
											}
											temp->I->immed = sptr->address-IC;
											temp->partial.bit = 0;
											print_instruction_list(code_image);
										}
										sptr=sptr->next;
									}	
									if(!found)
									{
										printf("ERROR! the label %s was not found in symbol table.\n",lbl_opr);
										error=ERROR;
									}
								}
								else if(i >= 23 && i <= 25)/* jmp / la / call */
								{
								printf("lbl_opr=|%s|\n",lbl_opr);
									while(sptr)
									{printf("sptr->name=|%s|\n",sptr->name);
										if(!strcmp(lbl_opr, sptr->name))
										{
											found = 1;
											temp->J->address = sptr->address;
											temp->partial.bit = 0;
											print_instruction_list(code_image);
											if(sptr->type == EXTERNAL)
											{
												add_to_ext_list (external_list, lbl_opr, IC);
												print_ext_list(external_list);
											}
										}
										sptr=sptr->next;
									}	
									if(!found)
									{
										printf("ERROR! the label %s was not found in symbol table.\n",lbl_opr);
										error=ERROR;
									}
								}
							}
							if(i >= 23 && i <= 25)/* jmp / la / call */
								{
									while(sptr)
									{
										if(!strcmp(lbl_opr, sptr->name))
										{
											if(sptr->type == EXTERNAL)
											{
												add_to_ext_list (external_list, lbl_opr, IC);
												print_ext_list(external_list);
											}
										}
										sptr=sptr->next;
									}
								}	
							puts("#####################ALL GOOD DOC!#####################");
							break;
						}
						temp = temp->next;
					}
	            case 8:  /* addi */
	            case 9:  /* subi */
	            case 10: /* andi */
	            case 11: /* ori */
	            case 12: /* nori */
	            case 17: /* lb */
	            case 18: /* sb */
	            case 19: /* lw */
	            case 20: /* sw */
	            case 21: /* lh */
	            case 22: /* sh */
					puts("#####################ALL GOOD DOC!#####################");
		            IC+=4;
				    continue;
		    }/*end of switch(i)*/
		}/*end else MUST BE AN INSTRUCTION. */
	}/* end for loop of lines in files. */
	
	    print_symbol_list(symbol_table);
    print_instruction_list(code_image);
    print_directive_list(data_image);
    print_machine_code(code_image, data_image);

	return error;
}
void bin_str_to_hex_str(char *bin, char *hex)
{
    char temp[4]="";
    int hex_right=0, hex_left=0, mult;
    int i=strlen(bin)-1,j=0,k;
    /* binary to hexadecimal conversion is as follows:
     * 0111 -> 0*(2^3) + 1*(2^2) + 1*(2^1) + 1*(2^0) = 
            -> 0*8     + 1*4     + 1*2     + 1*1     = 
            -> 0       + 4       + 2       + 1       =
            -> 7
    */
    while(i>=0)
    {
        k=i;
        /* calculating the hex value of the right most group */
        for(mult=1, j=3; j>=0; j--, k--)
        {
            hex_right += (bin[k]=='0'? 0 : mult);
            mult *= 2;
        }
        /* calculaing the hex value of the group that is left to the right most group */
        for(mult=1, j=3; j>=0; j--, k--)
        {
            hex_left += (bin[k]=='0'? 0 : mult);
            mult *= 2;
        }
        i=k;
        /* Concatinate left group then right group to hex string. */
        sprintf(temp,"%X%X ",hex_left,hex_right);
        strcat(hex,temp);
        hex_right=0;
        hex_left=0;
    }
}
void print_machine_code(instruction_list *ci, directive_list *di) {
    instruction_node *in = ci->head;
    directive_node *dn = di->head;
    char num_bin[32]="",num_hex[32]="",*pair_hex;
    int pairs_in_line=0,i=0,expected_address=0, parsing  = 0;
    /* print length of code image and length of data image. */
    printf("\n     %d %d\n",ICF-100,DCF);
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
        printf("%04d %s\n",in->address,num_hex);
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
			printf("%04d ",expected_address);
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
					printf("%04d ",expected_address);
				}
                printf("%s ",pair_hex);
                pairs_in_line++;
                expected_address++;
            }
            if(pairs_in_line==4)
            {
                pairs_in_line=0;
				parsing = 1;
                puts("");
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
    puts("");    
}
