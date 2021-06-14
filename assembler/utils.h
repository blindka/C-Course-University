#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> /* Required for "atoi" function. */
#include <limits.h>
#define MAX_LINE_LEN 82 /*80 for line + 1 for '\n' + 1 for '\0' at the end of each line. */
#define MAX_LABEL_LEN 31 /*31 for the label string */
#define NUMBER_OF_FUNCTIONS 8 /* 7 + help = 8*/
#define NUM_OF_INSTRUCTIONS 27
#define NUM_OF_DIRECTIVES 6
#define ERROR -1





/* struct that represent a command from page 22 in the course booklet.
later will be used to create the commands table from that page. */
typedef struct instruction {
	char * name;
	char type;
	int funct;
	int opcode;
}instruction;


/* enum for the type of symbol methods */
typedef enum symbol_type {EXTERNAL, DATA, CODE, CODE_AND_ENTRY,DATA_AND_ENTRY} sym_type;

/* SYMBOL (part of SYMBOL TABLE LIST )*/
typedef struct symbol { 
	char name[MAX_LABEL_LEN]; /* The name of the symbol */
	int address; /* The index in the data table in which the symbol data is held, or 0 if it's an external variable */
	sym_type type;
	struct symbol *next; 
}symbol;
/* SYMBOL TABLE (IS SYMBOL TABLE LIST )*/
typedef struct symbol_list {
    symbol *head;
    int count;
} symbol_list;
extern symbol_list *symbol_table;

/*INSTRUCTION STRUCTS*/
typedef struct bit {
    unsigned int bit:1;
} bit;

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
	int address;
	R_instruction *R;
	I_instruction *I;
	J_instruction *J;
	bit partial;
	struct instruction_node *next; 
}instruction_node;

typedef struct instruction_list {
    instruction_node *head;
    int count;
} instruction_list;
extern instruction_list *code_image;

/*DIRECTIVES STRUCTS*/
typedef struct _8_bit_directive { 
	unsigned int data:8;
}_8_bit_directive;

typedef struct _16_bit_directive { 
	unsigned int data:16;
}_16_bit_directive;

typedef struct _32_bit_directive { 
	unsigned int data:32;
}_32_bit_directive;

typedef struct directive_node { 
	int address;
	_8_bit_directive  *_8_bit;
	_16_bit_directive *_16_bit;
	_32_bit_directive *_32_bit;
	struct directive_node *next; 
}directive_node;

typedef struct directive_list {
    directive_node *head;
    int count;
} directive_list;

extern directive_list *data_image;

/* ext (part of SYMBOL TABLE LIST )*/
typedef struct ext { 
	char name[MAX_LABEL_LEN]; /* The name of the symbol */
	int address; /* The index in the data table in which the symbol data is held, or 0 if it's an external variable */
	struct ext *next; 
}ext;
/* SYMBOL TABLE (IS SYMBOL TABLE LIST )*/
typedef struct ext_list {
    ext *head;
    int count;
} ext_list;
extern ext_list *external_list;
extern int IC, DC, ICF, DCF;


int skip_white_spaces(char *s);
int skip_non_white_spaces(char *s);
int is_label(char * tkn ,instruction instructions[] ,char * directives[] ,symbol_list * symbols, int is_parameter_check);
void int_to_bin_str(int n, int len, char *str);
void bin_str_to_hex_str(char *bin, char *hex);
void print_machine_code(instruction_list *ci, directive_list *di);
void print_instruction(instruction_node *i);
void print_instruction_list(instruction_list *ci);
void print_directive(directive_node *d);
void print_directive_list(directive_list *di);
void print_symbol(symbol *s);
void print_symbol_list(symbol_list *st);
void print_ext(ext * e);
void print_ext_list(ext_list *el);

char * eng_ordinal_nums(int n);
#endif
