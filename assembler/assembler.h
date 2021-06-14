
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> /* Required for "atoi" function. */
#include <limits.h>



int first_pass(FILE * fptr);

int second_pass(FILE * fptr);

void open_files(int argc, char *argv[]);
char * eng_ordinal_nums(int n);
void write_output_files(char*name);
void write_ob_file(FILE *f);
void write_ext_file(FILE *f);
void write_ent_file(FILE *f);
