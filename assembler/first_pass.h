#ifndef FISRT_PASS_H
#define FISRT_PASS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> /* Required for "atoi" function. */
#include <limits.h>





void add_to_code_image (instruction_list *ci, int i_type,int i_idx, int oprnd1, int oprnd2, int oprnd3,symbol_list * symbols, char * label);
void add_to_data_image (directive_list *di, int d_idx, int to_store);
void add_to_symbol_table (symbol_list *st, char * name, int addr, sym_type ty);
void increase_address_to_data(symbol_list *st, directive_list *di);
#endif
