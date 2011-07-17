/******************************************************************************
 * Module - debug
 * Description - This file contains methods for outputting debug info
 *****************************************************************************/

/* domain includes */
#include <platform.h>
/* global includes */

/* other  includes */



static FILE *output_file;


void debug_init_output (void)
{
   output_file = fopen ("debug_info.txt", "w");
}

void debug_write_to_output (char* input)
{
   fputs (input, output_file);
}

void TRIGGER_ERROR(int i)
{
   char error[16];

   sprintf (error, "STOP: %x\n", i);

   debug_write_to_output (error);

   system ("PAUSE");
}

void debug_stop (void)
{
   fclose (output_file);
}