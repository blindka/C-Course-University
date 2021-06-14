
#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> /* Required for "atol" function. */
#include <limits.h>




void bin_str_to_hex_str(char *bin, char *hex);
void add_to_ext_list (ext_list * e, char * name, int addr);

/*--------------------------------------------------------------------------------------------
remove_white_spaces: removes all white spaces from a given string (str).
--------------------------------------------------------------------------------------------*/
void remove_white_spaces(char *str);

#endif
