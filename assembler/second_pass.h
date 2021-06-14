/*
Kfir Sibirsky	316317221
Eyal Haimov
=====================================================================================================
This file contains...
=====================================================================================================
*/
#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

/*--------------------------------------------------------------------------------------------
add_to_ext_list: Create a new ext node (external symbol), which consists of the corresponding given 
                 operands (name = name, address = addr).
                 Afterwards, append the new node to the end of the linked list of
                 external symbols (e = external list)
--------------------------------------------------------------------------------------------*/
void add_to_ext_list (ext_list * e, char * name, int addr);

/*--------------------------------------------------------------------------------------------
remove_white_spaces: removes all white spaces from a given string (str).
--------------------------------------------------------------------------------------------*/
void remove_white_spaces(char *str);

#endif
