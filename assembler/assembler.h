/*
Kfir Sibirsky	316317221
Eyal Haimov
=====================================================================================================
This file contains...
=====================================================================================================
*/
#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

char * file_name;

/*--------------------------------------------------------------------------------------------
first_pass: performs the first pass of the assembler on a given file (fptr).
            Returns 1 passed successfully, -1 if not.
--------------------------------------------------------------------------------------------*/
int first_pass(FILE * fptr);

/*--------------------------------------------------------------------------------------------
second_pass: performs the second pass of the assembler on a given file (fptr).
            Returns 1 passed successfully, -1 if not.
--------------------------------------------------------------------------------------------*/
int second_pass(FILE * fptr);

/*--------------------------------------------------------------------------------------------
write_output_files: Open files to write the 3 output files (ob, ext, ent) with the same name
                    (name) as the current file being analyzed.
--------------------------------------------------------------------------------------------*/
void write_output_files(char*name);

/*--------------------------------------------------------------------------------------------
write_ob_file: Write to the output file (f) the machine code.
--------------------------------------------------------------------------------------------*/
void write_ob_file(FILE *f);

/*--------------------------------------------------------------------------------------------
write_ext_file: Write to the output file (f) the list places (addresses) in the machine code
                in which a symbol that is declared as an external is used.
                (all symbols that appeared as an operand of .external,
                And is characterized in the symbol table as "external") 
--------------------------------------------------------------------------------------------*/
void write_ext_file(FILE *f);

/*--------------------------------------------------------------------------------------------
write_ent_file: Write to the output file (f) the list of symbols which declared as an entry
                point (all symbols that appeared as an operand of .entry,
                And is characterized in the symbol table as "data, entry" or "code, entry") 
--------------------------------------------------------------------------------------------*/
void write_ent_file(FILE *f);
#endif
