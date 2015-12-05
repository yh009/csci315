/*
 * Ravi Lonberg
 * csci315
 * Lab 12
 */
#include "wrappers.h"
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_H_


/** 
print follows the follwing usage:

> print [filename]

The user is then prompted with a list of installed, running printers on the linux machine and is asked to select one as a destination.
'print' uses the following /usr/bin/ commands...

"lpstat -a"  ::: to prove a list of printers

and

"a2ps [filename] -P [printer]" ::: to execute the print command

**/

int print(char *args[]);
    

