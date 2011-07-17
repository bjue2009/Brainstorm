#ifndef DEBUG_H
#define DEBUG_H

/******************************************************************************
 * Module - debug
 * Description - This file contains methods for outputting debug info
 *****************************************************************************/

/* domain includes */

/* global includes */

/* other  includes */
#include <stdio.h>
#include <stdlib.h>


void debug_init_output (void);
void debug_write_to_output (char* input);
void debug_stop (void);
void TRIGGER_ERROR(int i);

#endif /* DEBUG_H */