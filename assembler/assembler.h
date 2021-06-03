#include "first_pass.h"
#include "second_pass.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /* Required for "atoi" function. */

#define MAX_LINE_LEN 82 /*80 for line + 2 for "\n" at the end of each line. (81?) */
#define MAX_LABEL_LEN 31 /*31 for the label string */
#define NUM_OF_INSTRUCTIONS 27
#define NUM_OF_DIRECTIVES 6

/* enum for the addressing methods */
enum {IMMEDIATE_ADDR,DIRECT_ADDR,RELATIVE_ADDR,DIRECT_REG_ADDR} ;
/* struct that represent a command from page 22 in the course booklet.
later will be used to create the commands table from that page. */
typedef struct instruction {
	char * name;
	char type;
	int funct;
	int opcode;
}instruction;
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
char directives[NUM_OF_DIRECTIVES] = {".db",".dw",".dh",".asciz",".entry",".extern"};

/* enum for the type of symbol methods */
typedef enum Symbol_Type {EXTERNAL, DATA, CODE, CODE_AND_ENTRY,DATA_AND_ENTRY} Sym_Type;

/* SYMBOL (part of SYMBOL TABLE LIST )*/
typedef struct symbol { 
	char *name; /* The name of the symbol */
	int address; /* The index in the data table in which the symbol data is held, or 0 if it's an external variable */
	Sym_Type type;
	struct symbol *next; 
}symbol;
/* SYMBOL TABLE (IS SYMBOL TABLE LIST )*/
typedef struct symbol_list {
    symbol *head;
    int count;
} symbol_list;
typedef struct R_instruction { 
	unsigned int not_used:6;
	unsigned int funct:5;
	unsigned int rd:5;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
}R_instruction;
typedef struct I_instruction { 
	unsigned int immed:16;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
}I_instruction;
typedef struct J_instruction { 
	unsigned int address:25;
	unsigned int reg:1;
	unsigned int opcode:6;
}J_instruction;
typedef struct instruction_node { 
	R_instruction R;
	I_instruction I;
	J_instruction J;
	struct instruction_node *next; 
}instruction_node;
/* SYMBOL TABLE (IS SYMBOL TABLE LIST )*/
typedef struct instruction_list {
    instruction_node *head;
    int count;
} instruction_list;

void print_symbol(symbol *s);

void print_symbol_table(symbol_table *st);

int get_instruction(char *line, char * instructions[]);

/*--------------------------------------------------------------------------------------------
skip_white_spaces_start: returns the number of white spaces from the start of a given string.
--------------------------------------------------------------------------------------------*/
int skip_white_spaces_start(char *s);
