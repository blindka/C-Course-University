/*
Kfir Sibirsky	316317221
Eyal Haimov
=====================================================================================================
This file contains...
=====================================================================================================
*/
#ifndef FISRT_PASS_H
#define FISRT_PASS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


/*--------------------------------------------------------------------------------------------
add_to_code_image: Create a new instruction node of given type (i_type = R / I / J) according
                   to a given index (i_idx) to the instruction table.
                   The new node consists of the corresponding given operands 
                   (oprnd1 / oprnd2 / oprnd 3 / label) to the expected operands of the 
                   instruction at i_idx.
                   Afterwards, append the new node to the end of the linked list of
                   instructions (ci = code image)
--------------------------------------------------------------------------------------------*/
void add_to_code_image (instruction_list *ci, int i_type,int i_idx, int oprnd1, int oprnd2,
                        int oprnd3,symbol_list * symbols, char * label);

/*--------------------------------------------------------------------------------------------
add_to_data_image: Create a new directive node of (8 bit / 16 bit / 32 bit) according
                   to a given index (d_idx) to the directive table.
                   The new node consists of the corresponding given number (to_store) 
                   to the expected operand of the directive at d_idx.
                   Afterwards, append the new node to the end of the linked list of
                   directives (di = data image)
--------------------------------------------------------------------------------------------*/
void add_to_data_image (directive_list *di, int d_idx, int to_store);

/*--------------------------------------------------------------------------------------------
add_to_symbol_table: Create a new symbol node, which consists of the corresponding given 
                     operands (name = name, address = addr, type = ty).
                     Afterwards, append the new node to the end of the linked list of
                     symbols (st = symbol table)
--------------------------------------------------------------------------------------------*/
void add_to_symbol_table (symbol_list *st, char * name, int addr, sym_type ty);

/*--------------------------------------------------------------------------------------------
increase_address_to_data: Adds the value of ICF to the address of each symbol in the symbol
                          table which characterized as "data". also, add the value of ICF to
                          the address of each node in the linked list of directives 
                          (data image)
--------------------------------------------------------------------------------------------*/
void increase_address_to_data(symbol_list *st, directive_list *di);
#endif
