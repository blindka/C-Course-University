/*
Kfir Sibirsky	316317221
=====================================================================================================

=====================================================================================================
*/
#include "utils.h"
#include "first_pass.h"

int IC, DC, ICF, DCF;
symbol_list *symbol_table;
instruction_list *code_image;
directive_list *data_image;


/* setting the values to create the table from page 22 in the course booklet. */
instruction instructions[NUM_OF_INSTRUCTIONS] = {			
{"add",'R',1,0},
{"sub",'R',2,0},
{"and",'R',3,0},
{"or",'R',4,0},
{"nor",'R',5,0},
{"move",'R',1,1},
{"mvhi",'R',2,1},
{"mvlo",'R',3,1},
{"addi",'I',0,10},
{"subi",'I',0,11},
{"andi",'I',0,12},
{"ori",'I',0,13},
{"nori",'I',0,14},
{"bne",'I',0,15},
{"beq",'I',0,16},
{"blt",'I',0,17},
{"bgt",'I',0,18},
{"lb",'I',0,19},
{"sb",'I',0,20},
{"lw",'I',0,21},
{"sw",'I',0,22},
{"lh",'I',0,23},
{"sh",'I',0,24},
{"jmp",'J',0,30},
{"la",'J',0,31},
{"call",'J',0,32},
{"stop",'J',0,63}
};
char *directives[NUM_OF_DIRECTIVES] = {".db",".dh",".dw",".asciz",".entry",".extern"};


/* this function converts an integer to a binary string. */
void int_to_bin_str(int n, int len, char *str)
{
    /* Possible numbers representable by len bits is:
     * -((2^len)/2), ... , -2, -1, 0, 1, 2, ... , ((2^len/2)-1)
     * Meaning, the possible range of numbers is: [-((2^len)/2) , ((2^len/2)-1)]
     */
    char bin[33]="";
    int i = len-1;
    
	while(i>=0)
    {
        (n&(1u<<i--))?strcat(bin, "1"):strcat(bin, "0");
    }
    strncpy(str,bin,len);
}

void print_instruction(instruction_node *i) {
    char num_bin[80]="";
    if(i->R != NULL)
        int_to_bin_str(*(int*)i->R,32,num_bin);
    else if(i->I != NULL)
        int_to_bin_str(*(int*)i->I,32,num_bin);
    else if(i->J != NULL)
        int_to_bin_str(*(int*)i->J,32,num_bin);

    printf("%04d|%s|",i->address,num_bin);
    (i->partial.bit==1? printf("  NO!   |\n"):printf("  YES   |\n"));
}

void print_instruction_list(instruction_list *ci) {
    instruction_node *temp = ci->head;
    if(ci->count==0)
    {
        printf("code image empty.\n");
        return;
    }
    puts("\naddr|     machine code  (binary)     |complete|");
    while (temp != NULL) {
        print_instruction(temp);
        temp = temp->next;
    }
}

void print_directive(directive_node *d) {
    char num_bin[80]="";
    if(d->_8_bit != NULL)
        int_to_bin_str(*(int*)d->_8_bit,8,num_bin);
    else if(d->_16_bit != NULL)
        int_to_bin_str(*(int*)d->_16_bit,16,num_bin);
    else if(d->_32_bit != NULL)
        int_to_bin_str(*(int*)d->_32_bit,32,num_bin);
    printf("%04d|%-32s|\n",d->address,num_bin);
}

void print_directive_list(directive_list *di) {
    directive_node *temp = di->head;
    if(di->count==0)
    {
        printf("data image empty.\n");
        return;
    }
    puts("\naddr|     machine code  (binary)     |");
    while (temp != NULL) {
        print_directive(temp);
        temp = temp->next;
    }
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void add_to_code_image (instruction_list *ci, int i_type,int i_idx, int oprnd1, int oprnd2, int oprnd3,symbol_list * symbols, char * label)
{
    instruction_node *new_node = (instruction_node*) malloc(sizeof(instruction_node));
    instruction_node *last = ci->head;
    new_node->partial.bit = 0;
    printf("%c\n",i_type);
    printf("%d\n",i_idx);
    printf("%d\n",oprnd1);
    printf("%d\n",oprnd2);
    printf("%d\n",oprnd3);

    if(i_type == 'R')
    {
        R_instruction * r = (R_instruction*) malloc(sizeof(R_instruction));
        r->opcode=instructions[i_idx].opcode;
        if(i_idx>=0 && i_idx<=4)
        {
            r->rs=oprnd1;
            r->rt=oprnd2;
            r->rd=oprnd3;
        }
        else/*5-7*/
        {
            r->rs=oprnd2;
            r->rd=oprnd1;
            r->rt=0;
        }
        r->funct=instructions[i_idx].funct;
        r->not_used=0;
        new_node->R = r;
        new_node->I = NULL;
        new_node->J = NULL;
    }
    else if(i_type == 'I')
    {
        I_instruction * i = (I_instruction*) malloc(sizeof(I_instruction));
        i->opcode=instructions[i_idx].opcode;
        if(i_idx>=13 && i_idx<=16 )
        {
            int label_addr = -7;
        	symbol * sptr = symbols->head;
        	while(sptr)
        	{
        		if(!strcmp(label, sptr->name))
        		{
                    label_addr=sptr->address;
                    break;
        		}
        		sptr=sptr->next;
        	}
        	if(label_addr==-7)
        	{
        	    /* not found in first pass in symbol table.
        	     * there is still hope in second pass.*/
	             new_node->partial.bit = 1;
        	}
        	else
	            i->immed = label_addr-IC;
            i->rs=oprnd1;
            i->rt=oprnd2;
        }
        else/*8-12 OR 17-22*/
        {
            i->rs=oprnd1;
            i->rt=oprnd3;
            i->immed=oprnd2;
        }
        new_node->I = i;
        new_node->R = NULL;
        new_node->J = NULL;
    }
    else if(i_type == 'J')
    {
        J_instruction * j = (J_instruction*) malloc(sizeof(J_instruction));
        j->opcode=instructions[i_idx].opcode;
        j->reg=0;
        if(i_idx>=23 && i_idx<=25)
        {
            printf("label=|%s|\n",label);
            if(label[0]!='\0')/* reg = 0 */
            {
                int label_addr = -7;
            	symbol * sptr = symbols->head;
            	while(sptr)
            	{
            		if(!strcmp(label, sptr->name))
            		{
                        label_addr=sptr->address;
                        break;
            		}
            		sptr=sptr->next;
            	}
	        	if(label_addr==-7)
            	{
            	    /* not found in first pass in symbol table.
            	     * there is still hope in second pass. */
     	             new_node->partial.bit = 1;
            	}
            	else
                {
                    j->address = (sptr->type == EXTERNAL? 0 : label_addr);
                }
            }
            else
            {
                if(i_idx==23)
                {            printf("lssssssabel=|%s|\n",label);
                    j->reg=1;
                    j->address=oprnd1;
                }
            }
        }
        else/*26*/
        {
            j->address=0;
        }
        new_node->J = j;
        new_node->R = NULL;
        new_node->I = NULL;
    }    
    new_node->address = IC;
    if (ci->count == 0)
       ci->head = new_node;
    else {
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
    ci->count++;
}
/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void add_to_data_image (directive_list *di, int d_idx, int to_store)
{
    directive_node *new_node = (directive_node*) malloc(sizeof(directive_node));
    directive_node *last = di->head;
    if(d_idx == 0 || d_idx == 3)/* .db / .asciz */
    {
        _8_bit_directive  * _8b = (_8_bit_directive*) malloc(sizeof(_8_bit_directive));
        _8b->data = to_store;
        new_node->_8_bit = _8b;
        new_node->_16_bit = NULL;
        new_node->_32_bit = NULL;
    }
    else if(d_idx == 1)/* .dh */
    {
        _16_bit_directive  * _16b = (_16_bit_directive*) malloc(sizeof(_16_bit_directive));
        _16b->data = to_store;
        new_node->_8_bit = NULL;
        new_node->_16_bit = _16b;
        new_node->_32_bit = NULL;
    }
    else if(d_idx == 2)/* .dw */
    {
        _32_bit_directive  * _32b = (_32_bit_directive*) malloc(sizeof(_32_bit_directive));
        _32b->data = to_store;
        new_node->_8_bit = NULL;
        new_node->_16_bit = NULL;
        new_node->_32_bit = _32b;
    }
    new_node->address = DC;
    if (di->count == 0)
       di->head = new_node;
    else {
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
    di->count++;
}

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
void add_to_symbol_table (symbol_list *st, char * name, int addr, sym_type ty)
{
    symbol * new_node = (symbol*) malloc(sizeof(symbol));
    symbol *last = st->head;
    strcpy(new_node->name,name);
    new_node->address  = addr;
    new_node->type  = ty;
    new_node->next = NULL;
 
     if (st->count == 0)
       st->head = new_node;
    else {
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
    st->count++;
    return;  
    
}


void increase_address_to_data(symbol_list *st, directive_list *di)
{
    symbol *s = st->head;
	directive_node *d = di->head;
    while (s != NULL) 
    {
        if(s->type==DATA)
        	s->address+=ICF;
        s = s->next;
    }
	while (d != NULL)
	{
		d->address+=ICF;
		d = d->next;
	}
}

/**
 * Preforms the first pass on the given file, searching for most of the syntax errors,
 * and translating most of the .as file into machine code
 * @param fptr - a pointer to the given file
 * @return ERROR or OK, according to the correctness of the file's syntax
 */
int first_pass(FILE *fptr)
{
    char line[MAX_LINE_LEN]="",first[MAX_LABEL_LEN]="",second[MAX_LABEL_LEN]="", cpy_str[MAX_LINE_LEN]="", *cpy_ptr, *sus;
    int c=0,count = 0, status = 0, error = 0,i=0,first_char_after_colon='\0',line_num=1;
    int operands[3];
	symbol_table = calloc(1, sizeof(symbol_list));
	code_image = calloc(1, sizeof(instruction_list));
	data_image = calloc(1, sizeof(directive_list));
operands[0]=0;
operands[1]=0;
operands[2]=0;
    IC = 100;
    DC = 0;
    for(line_num = 1; fgets(line, MAX_LINE_LEN, fptr); line_num++) /* Scanning through each line of the file */
    {
		for(c=0;c<MAX_LABEL_LEN;c++)
		{
			first[c]='\0';
			second[c]='\0';
			cpy_str[c]='\0';
		}
    	cpy_ptr=NULL;
    	sus=NULL;
    	count = 0;
    	status = 0; 
    	puts(line);
        strcpy(cpy_str,line);
		cpy_ptr = cpy_str;
    	puts(cpy_ptr);
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
		strncpy(first,cpy_ptr,count);
		status = is_label(first ,instructions, directives, symbol_table,0);

		/* Skip the first token. */
		cpy_ptr += count;
		first_char_after_colon = cpy_ptr[0];

		/* Skip unnecessary white spaces between first and second token. */
		cpy_ptr += skip_white_spaces(cpy_ptr);
		count = 0;

		while(count<strlen(cpy_ptr) && !isspace(cpy_ptr[count])) {
			/* getting second "token". (sus cmd name) */
			count++;
		}
		strncpy(second,cpy_ptr,count);
		sus = first;
		
		if(status == -1)/* Error in label - NO need to check in line more errors, ONLY to go to next line. */
		{
			error=ERROR;
			continue;
		}
		if(status == 1)/* VALID LABEL, SKIP to second token. */
		{
			/* Expecting white space (one or more). */
			if(!isspace(first_char_after_colon))
			{
				printf("ERROR! Non white space character right after label's colon.");
				error=ERROR;
				continue;
			}
			/* Skip the second token. */
			cpy_ptr += count;
			/* Skip unnecessary white spaces between second and third token. */
			cpy_ptr += skip_white_spaces(cpy_ptr);
			count = 0;
			sus = second;
	        first[strlen(first)-1]='\0';
	        printf("first(label)=|%s|\n",first);
		}
		/* as of now, either:
		 * sus = second (because valid label).
		 * OR
		 * sus = first (because NO label).  */
	 	printf("sus=|%s|\n",sus);
		if(!strcmp(sus, ".db") || !strcmp(sus, ".dh") || !strcmp(sus, ".dw") || !strcmp(sus, ".asciz"))
		{
		    long temp_num=0;
			if (status == 1) 
			{
			     add_to_symbol_table(symbol_table, first, DC, DATA);
	   		}
	   		if (strcmp(sus, ".asciz"))/*.db / .dh / .dw*/
	   		{
		        char num[80]="", t[1]="";
		        int j=0;
	        	printf("cpy_ptr=|%s|\n",cpy_ptr);

		        while(j<strlen(cpy_ptr))
		        {
		        	while(isspace(cpy_ptr[j]))
		        	{
		        	    j++;
		        	}
		        	if(isdigit(cpy_ptr[j])||cpy_ptr[j]=='-'||cpy_ptr[j]=='+')
		        	{
		        	    if(cpy_ptr[j]=='-'||cpy_ptr[j]=='+')
		        	    {
		        	        t[0]=cpy_ptr[j];
		        	        strncat(num,t,1);
		                    j++;
		                    if(cpy_ptr[j]=='-'||cpy_ptr[j]=='+')
		                    {
		                        printf("ERROR! more than one sign.\n");
		                        error=ERROR;
								continue;
		                    }
		                    if(isspace(cpy_ptr[j]))
		                    {
		                        printf("ERROR! white space between '%c' sign and number.\n",cpy_ptr[j-1]);
		                        error=ERROR;
								continue;
		                    }
		                    if(!isdigit(cpy_ptr[j]))
		                    {
		                        printf("ERROR! not an integer.\n");
		                        error=ERROR;
								continue;
		                    }
		        	    }
		                while(isdigit(cpy_ptr[j]))
		                {
		        	        t[0]=cpy_ptr[j];
		        	        strncat(num,t,1);
		        	        j++;
		                }
			            temp_num = atol(num);
			            printf("|%ld|\n",temp_num);
		    	   		if(!strcmp(sus, ".db"))
		    	   		{	                
		                  if(temp_num > CHAR_MAX || temp_num < CHAR_MIN)
		                    {
		                        printf("ERROR! data to store is out of bounds of Two’s Complement convertion.\n");
		                        printf("%ld (decimal) is not in the range [%d,%d].\n",temp_num,CHAR_MIN,CHAR_MAX);
		                    }
		    	   		    add_to_data_image (data_image, 0, temp_num);
		   	                DC++;
		    	   		}
			   		    else if(!strcmp(sus, ".dh"))
		    	   		{
		                  if(temp_num > SHRT_MAX || temp_num < SHRT_MIN)
		                    {
		                        printf("ERROR! data to store is out of bounds of Two’s Complement convertion.\n");
		                        printf("%ld (decimal) is not in the range [%d,%d].\n",temp_num,SHRT_MIN,SHRT_MAX);
		                    }
		    	   		    add_to_data_image (data_image, 1, temp_num);
		   	                DC+=2;
			   		    }
		    	   		else if(!strcmp(sus, ".dw"))
		    	   		{
		                    if(temp_num > INT_MAX || temp_num < INT_MIN)
		                    {
		                        printf("ERROR! data to store is out of bounds of Two’s Complement convertion.\n");
		                        printf("%ld (decimal) is not in the range [%d,%d].\n",temp_num,INT_MIN,INT_MAX);
		                    }
		    	   		    add_to_data_image (data_image, 2, temp_num);
		   	                DC+=4;
			   		    }
			            num[0]='\0';
			            print_directive_list(data_image);
			    	}
		        	else
		        	{
		                printf("ERROR! not an integer.\n");
		                error=ERROR;
						continue;
		        	}
		        	while(isspace(cpy_ptr[j]))
		        	{
		        	    j++;
		        	}
		        	if(cpy_ptr[j]==',')
		        	{
		                j++;
		            	while(isspace(cpy_ptr[j]))
		            	{
		            	    j++;
		            	}
		            	if(cpy_ptr[j]==',')
		            	{
		                    printf("ERROR! Multiple consecutive commas.\n");
		                    error=ERROR;
							continue;
		            	}
		        	}
		        	else
		        	{
		                if(isdigit(cpy_ptr[j]))
		                {
		                    printf("Error! missing comma.\n");
		                    error=ERROR;
							continue;
		                }
		                if(cpy_ptr[j]!='\n' && cpy_ptr[j]!='\0')
		                {
		                    printf("ERROR! not an integer in or after number list.\n");
		                    error=ERROR;
							continue;
		                }
		        	}/*end else*/    	
		        }/*end while*/
	   		} else {
	   	        int j=0;
	   	        printf("cpy_ptr=|%s|\n",cpy_ptr);
		    	if(cpy_ptr[j]=='\"')/* opening quotation mark found. */
		    	{
		            j++;
		            while(j < strlen(cpy_ptr) && cpy_ptr[j]!='\"')
		            {
		                if(!isprint(cpy_ptr[j]))
		            	{
		                    printf("ERROR! character that has the value %d (decimal) is not a printable ascii character.\n",cpy_ptr[j]);
		                    error=ERROR;
							continue;
		            	}
		                printf("cpy_ptr[%d]=|%c|\n",j,cpy_ptr[j]);
        	   		    add_to_data_image (data_image, 3, cpy_ptr[j]);
			            print_directive_list(data_image);
            	   		/* add cpy_ptr[j] to DATA IMAGE (MACHINE CODE). */
		                DC++;
		                j++;
		            }
		       	    if(cpy_ptr[j]!='\"')
		            {
		                printf("Error! missing closing quotation mark after last printable character.\n");
		                error=ERROR;
						continue;
		            }
    	   		    add_to_data_image (data_image, 0,0);
		            print_directive_list(data_image);
	                DC++;
		            j++;/* closing quotation mark found. */
		        	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
		        	{
		        	    j++;
		        	}
		            if(cpy_ptr[j]!='\0' && cpy_ptr[j]!='\n')
		            {
		                printf("Error! Extraneous text after comand.\n");
		                error=ERROR;
						continue;
		            }
		    	}
		    	else
		    	{
		            if(isprint(cpy_ptr[j]))
		                printf("Error! missing opening quotation mark before first printable character.\n");
		            else
		                printf("Error! missing parameter, non printable character found instead.\n");
	                error=ERROR;
					continue;
		    	}
	   		}
	   		/* Continue to next line. */
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
				cpy_ptr += skip_white_spaces(cpy_ptr);
				count = 0;
			
				while(count<strlen(cpy_ptr) && !isspace(cpy_ptr[count])) {
					/* getting second "token". (sus cmd name) */
					count++;
				}
				strncpy(third,cpy_ptr,count);
				sus = third;
   			}
			add_to_symbol_table(symbol_table, sus, 0, EXTERNAL);
   			continue;
		}
		else /* Instruction is expected. */
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
				error=ERROR;
				continue;
			}
			else
			{
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
				int num_of_operands, operands_expected;
                int ops=0;
		        char num[80]="", t[1]="", label_operand[MAX_LABEL_LEN]="";
		        int j=0;
				if (status == 1) 
				{
					add_to_symbol_table(symbol_table, first, IC, CODE);
				    print_symbol_list(symbol_table);
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
						printf("cpy_ptr=|%s|\n",cpy_ptr);
						num_of_operands = 0;
						operands_expected=((i >= 5 && i <= 7) ? 2 : 3);
						printf("num_of_operands=|%d|\n",num_of_operands);
						while(j<strlen(cpy_ptr))
						{
							
							while(isspace(cpy_ptr[j]))
							{
								j++;
							}
							if(cpy_ptr[j]=='$')
							{
							    j++;
							    if(!isdigit(cpy_ptr[j]))
							    {
							        printf("ERROR! invalid parameter - register must be $0-$31.\n");
							        error=ERROR;
							        continue;
							    }
							    while(isdigit(cpy_ptr[j]))
							    {
								    t[0]=cpy_ptr[j];
								    strncat(num,t,1);
								    j++;
							    }
							    if(atoi(num)>31 || atoi(num)<0)
							    {
							        printf("ERROR! invalid parameter - register must be $0-$31.\n");
							        error=ERROR;
							        continue;
							    }
							    operands[ops]=atoi(num);
							    ops++;
							    printf("|%d|\n",atoi(num));
							    num[0]='\0';
							}
							else
							{
								if(i<= 7 || (i >= 13 && i <= 16 && num_of_operands < 2))
								{
							        printf("ERROR! invalid parameter - register must start with '$'.\n");
							        error=ERROR;
							        continue;
								}
							}
							while(isspace(cpy_ptr[j]))
							{
								j++;
							}
							if(num_of_operands < operands_expected-1 && cpy_ptr[j]==',')
							{
							    j++;
								while(isspace(cpy_ptr[j]))
								{
								    j++;
								}
								if(cpy_ptr[j]==',')
								{
							        printf("ERROR! Multiple consecutive commas.\n");
							        error=ERROR;
							        continue;
								}
							}
							else
							{
							    if(num_of_operands < operands_expected-1 &&
						    	((i<=7 && cpy_ptr[j]=='$') || 
						    	(i>=13 && num_of_operands == 0 && cpy_ptr[j]=='$') ||
						    	(i>=13 && num_of_operands == 1 &&isalpha(cpy_ptr[j]))))
							    {
							        printf("Error! missing comma.\n");
							        error=ERROR;
							        continue;
							    }
							}/*end else*/
							num_of_operands++;            
							printf("num_of_operands=|%d|\n",num_of_operands);
							if(i>=13 && num_of_operands==2)
							    break;
							if(i<=7 && num_of_operands==operands_expected)
							{
							   	while(isspace(cpy_ptr[j]))
								{
								    j++;
								}
							    if(cpy_ptr[j]!='\n' && cpy_ptr[j]!='\0')
							    {
							        printf("Error! Extraneous text after comand.\n");
							        error=ERROR;
							        continue;
							    }
							}
						}/*end while*/
						if(i >= 13 && i <= 16)
						{
							int reg=0;
				    case 23: /* jmp */
				 	   /* (1 operand: $reg/label) */
							reg=0;
				    case 24: /* la */
				    case 25: /* call */
				       /* (1 operand: label) */
							while(j<strlen(cpy_ptr) && !isspace(cpy_ptr[j]))
							{
							    /* getting label operand "token". */
							    t[0]=cpy_ptr[j];
							    strncat(label_operand,t,1);
							    j++;
							}
							if(label_operand[0]=='$')
							{
							    int k=1;
						    	if((i >= 13 && i <= 16) || i == 24 || i == 25)
								{					            
								    printf("ERROR! invalid parameter - register instead of label.\n");
							        error=ERROR;
							        continue;
								}
							    while(isdigit(label_operand[k]))
						        {
							        t[0]=label_operand[k];
							        strncat(num,t,1);
						            k++;
						        }
						        if(k==1 || (atoi(num)>31 || atoi(num)<0))
						        {
						            printf("ERROR! invalid parameter - register must be $0-$31.\n");
						            error=ERROR;
							        continue;
						        }
						        reg =1 ;
								num_of_operands = 1;
								operands_expected = 1;
							    operands[ops]=atoi(num);
							    ops++;
							    label_operand[0]='\0';
						        printf("label_operand[0]=='$'|%d|\n",atoi(num));
						        num[0]='\0';
						    }
						    if(!reg)
						    {
						        if(label_operand[0]=='\0'||label_operand[0]=='\n')
						        {
						            printf("Error! Missing label parameter.\n");
						            error=ERROR;
							        continue;
						        }
						        if(is_label(strncat(label_operand,":",1) ,instructions, directives, symbol_table,1)!=1)
						        {
						            printf("ERROR! invalid parameter - invalid label.\n");
						            error=ERROR;
							        continue;
						        }
						        label_operand[strlen(label_operand)-1]='\0';
							    if(i==23)
							    {
									num_of_operands = 1;
									operands_expected = 1;
							    }
							    else
							    {
							        num_of_operands++;
							    }
						        printf("label_operand=|%s|\n",label_operand);
						    }
						    /* check extra */
							while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
							{
							    j++;
							}
					case 26: /* stop */
						    if(j<strlen(cpy_ptr) && (cpy_ptr[j]!='\n' && cpy_ptr[j]!='\0'))
						    {
						        printf("Error! Extraneous text after comand.\n");
						        error=ERROR;
						        continue;
						    }
						    if(i==24 ||i==25)
						    {
						    	num_of_operands = 1;
						    	operands_expected = 1;
								/* although la / call build machine code and continue;*/
						    }
						    if(i==26)
						    {
						    	num_of_operands = 0;
						    	operands_expected = 0;
								/* although stop build machine code and continue;*/
						    }
						}
				    	if(num_of_operands<operands_expected)
				    	{                    
			                printf("Error! Missing %d parameter/s.\n",(operands_expected-num_of_operands));
			                error=ERROR;
						    continue;
				        }
					    /* i = 0-4   reached here no problem.
					     * i = 5-7   reached here no problem. 
					     * i = 13-16 reached here no problem. 
					     * i = 23    reached here no problem. 
					     * i = 24-25 reached here no problem. 				        
					     * i = 26    reached here no problem. 
		    	   		 * add to INSTRUCTION IMAGE (MACHINE CODE). */
			   			printf("operands[0]=|%d|\n",operands[0]);
		            	printf("operands[1]=|%d|\n",operands[1]);
		            	printf("operands[2]=|%d|\n",operands[2]);
		            	printf("label_operand=|%s|\n",label_operand);
		            	if(i>=0 && i<=7)/* $reg, $reg / $reg, $reg , $reg */
		                    add_to_code_image(code_image,'R',i,operands[0],operands[1],operands[2],symbol_table,label_operand);
		                else if(i>=13 && i<=16)/* $reg, $reg, label */
		                    add_to_code_image(code_image,'I',i,operands[0],operands[1],0,symbol_table,label_operand);
		                else if(i==23) /* $reg/label */
		                    add_to_code_image(code_image,'J',i,operands[0],0,0,symbol_table,label_operand);
		                else if(i==24||i==25) /*label */
		                    add_to_code_image(code_image,'J',i,0,0,0,symbol_table,label_operand);
		                else if(i==26) /* NO OPERANDS */
		                    add_to_code_image(code_image,'J',i,0,0,0,symbol_table,label_operand);
		                print_instruction_list(code_image);
			            IC+=4;
					    continue;
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
		                /* (3 operands: $reg,immed,$reg) */
				    	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				    	{
				    	    j++;
				    	}
				    	if(cpy_ptr[j]=='$')
				    	{
				            j++;
				            if(j<strlen(cpy_ptr) && !isdigit(cpy_ptr[j]))
				            {
				                printf("ERROR! invalid parameter - register must be $0-$31.\n");
				                error=ERROR;
						    	continue;
				            }
				            while(j<strlen(cpy_ptr) && isdigit(cpy_ptr[j]))
				            {
				    	        t[0]=cpy_ptr[j];
				    	        strncat(num,t,1);
				    	        j++;
				            }
				            if(atoi(num)>31 || atoi(num)<0)
				            {
				                printf("ERROR! invalid parameter - register must be $0-$31.\n");
				                error=ERROR;
						    	continue;
				            }
						    operands[ops]=atoi(num);
						    ops++;
				            printf("|%d|\n",atoi(num));
		                	num[0]='\0';
				    	}
				    	else
				    	{
				            printf("ERROR! invalid parameter - register must start with '$'.\n");
				            error=ERROR;
					    	continue;
				    	}
				    	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				    	{
				    	    j++;
				    	}                    
				    	if(cpy_ptr[j]==',')
				    	{
				            j++;
				        	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				        	{
				        	    j++;
				        	}
				        	if(j<strlen(cpy_ptr) && cpy_ptr[j]==',')
				        	{
				                printf("ERROR! Multiple consecutive commas.\n");
				                error=ERROR;
						    	continue;
				        	}
				    	}
				    	else
				    	{
				            if(j<strlen(cpy_ptr) && isdigit(cpy_ptr[j]))
				            {
				                printf("Error! missing comma.\n");
				                error=ERROR;
						    	continue;
				            }
				    	}/*end else*/
				    	if(j<strlen(cpy_ptr) && (isdigit(cpy_ptr[j])||cpy_ptr[j]=='-'||cpy_ptr[j]=='+'))
				    	{
				    	    if(j<strlen(cpy_ptr) && (cpy_ptr[j]=='-'||cpy_ptr[j]=='+'))
				    	    {
				    	        t[0]=cpy_ptr[j];
				    	        strncat(num,t,1);
				                j++;
				                if(j<strlen(cpy_ptr) && (cpy_ptr[j]=='-'||cpy_ptr[j]=='+'))
				                {
				                    printf("ERROR! more than one sign.\n");
				                    error=ERROR;
						    		continue;
				                }
				                if(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				                {
				                    printf("ERROR! white space between '%c' sign and number.\n",cpy_ptr[j-1]);
				                    error=ERROR;
						    		continue;
				                }
				                if(j<strlen(cpy_ptr) && !isdigit(cpy_ptr[j]))
				                {
				                    printf("ERROR! not an integer.\n");
				                    error=ERROR;
						    		continue;
				                }
				    	    }
				            while(j<strlen(cpy_ptr) && isdigit(cpy_ptr[j]))
				            {
				    	        t[0]=cpy_ptr[j];
				    	        strncat(num,t,1);
				    	        j++;
				            }
						    operands[ops]=atoi(num);
						    ops++;
				            printf("|%d|\n",atoi(num));
				            num[0]='\0';
				    	}
				    	else
				    	{
				            printf("ERROR! not an integer.\n");
				            error=ERROR;
				    		continue;
				    	}
				    	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				    	{
				    	    j++;
				    	}
				    	if(j<strlen(cpy_ptr) && cpy_ptr[j]==',')
				    	{
				            j++;
				        	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				        	{
				        	    j++;
				        	}
				        	if(j<strlen(cpy_ptr) && cpy_ptr[j]==',')
				        	{
				                printf("ERROR! Multiple consecutive commas.\n");
				                error=ERROR;
					    		continue;
				        	}
				    	}
				    	else
				    	{
				            if(j<strlen(cpy_ptr) && cpy_ptr[j]=='$')
				            {
				                printf("Error! missing comma.\n");
				                error=ERROR;
					    		continue;
				            }
				    	}/*end else*/ 
				    	if(j<strlen(cpy_ptr) && cpy_ptr[j]=='$')
				    	{
				            j++;
				            if(j<strlen(cpy_ptr) && !isdigit(cpy_ptr[j]))
				            {
				                printf("ERROR! invalid parameter - register must be $0-$31.\n");
				                error=ERROR;
					    		continue;
				            }
				            while(j<strlen(cpy_ptr) && isdigit(cpy_ptr[j]))
				            {
				    	        t[0]=cpy_ptr[j];
				    	        strncat(num,t,1);
				    	        j++;
				            }
				            if(atoi(num)>31 || atoi(num)<0)
				            {
				                printf("ERROR! invalid parameter - register must be $0-$31.\n");
				                error=ERROR;
					    		continue;
				            }
						    operands[ops]=atoi(num);
						    ops++;
				            printf("|%d|\n",atoi(num));
				            num[0]='\0';
				    	}
				    	else
				    	{
				            printf("ERROR! invalid parameter - register must start with '$'.\n");
				            error=ERROR;
				    		continue;
				    	}
				    	while(j<strlen(cpy_ptr) && isspace(cpy_ptr[j]))
				    	{
				    	    j++;
				    	}
				        if(j<strlen(cpy_ptr) && (cpy_ptr[j]!='\n' && cpy_ptr[j]!='\0'))
				        {
				            printf("Error! Extraneous text after comand.\n");
				            error=ERROR;
				    		continue;
				        }

					    /* i = 8-12 reached here no problem.
					     * i = 17-22 reached here no problem.				        
		    	   		 * add to INSTRUCTION IMAGE (MACHINE CODE). */
		   	   			printf("operands[0]=|%d|\n",operands[0]);
		            	printf("operands[1]=|%d|\n",operands[1]);
		            	printf("operands[2]=|%d|\n",operands[2]);
		            	if((i>=8 && i<=12) || (i>=17 && i<=22))/* $reg, immed, $reg */
		                    add_to_code_image(code_image,'I',i,operands[0],operands[1],operands[2],symbol_table,label_operand);
		                print_instruction_list(code_image);
			            IC+=4;
					    continue;
			    }/*end of switch(i)*/
			}/*end of else (just like found == 1, where found is good insturction or not.)*/
		}/*end else MUST BE AN INSTRUCTION. */
	}/* end for loop of lines in files. */
	ICF = IC;
	DCF = DC;
	if(!error) /* If the code in the file valid so far, we increase the addresses of the data variables */
	    increase_address_to_data(symbol_table, data_image);

	rewind(fptr); /* Rewinds the file for the second pass and returns a flag regarding a spotted error in the file */
	return error;
}
/*--------------------------------------------------------------------------------------------
skip_white_spaces: returns the number of white spaces from the start of a given string.
--------------------------------------------------------------------------------------------*/
int skip_white_spaces(char *str)
{
	int count=0;
   	while(count<strlen(str) && isspace(str[count]))
	{
		count++;
	}
	return count;
}
/*--------------------------------------------------------------------------------------------
skip_non_white_spaces: returns the number of non white spaces from the start of a given string.
--------------------------------------------------------------------------------------------*/
int skip_non_white_spaces(char *str)
{
	int count=0;
   	while(count<strlen(str) && !isspace(str[count]))
	{
		count++;
	}
	return count;
}
int is_label(char * tkn ,instruction instructions[] ,char * directives[] ,symbol_list * symbols, int is_parameter_check)
{
    int i=0;
	char str[MAX_LABEL_LEN]="";
	symbol * sptr = symbols->head;
	int col=0;
	puts(tkn);
	if(tkn[strlen(tkn)-1]==':')
	{
	    col = 1;
	    strncpy(str,tkn,strlen(tkn)-1);
	}
	else
	    strncpy(str,tkn,strlen(tkn));
	puts(str);
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
		    {    
		        if(is_parameter_check == 1)
		        {
		            return 1;
		        }
	    	    puts("ERROR IN LABEL - symbol already exist in symbol table");
		    }
		    else
    		    puts("ERROR IN LABEL - missing colo1");
            return -1;
		}
		sptr=sptr->next;
	}
	if(col == 0)
	{
	    puts("ERROR IN LABEL - missing colo2n");
	    return -1;
	}
	return 1;
}
