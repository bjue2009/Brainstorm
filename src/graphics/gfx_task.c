/******************************************************************************
 * Module - GFX
 * Description - This file contains the task definition for the graphics module
 *****************************************************************************/

/* domain includes */
#include <gfx_api.h>
#include <e_msg_queue_api.h>
#include <e_buffer_api.h>
/* global includes */
/* other  includes */
#include <debug.h>


/******************************************************************************
 * gfx_task - task for graphics module
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void gfx_task (void)
{
   char *buffer;
   char test;
   test = '\0';
   FOREVER
   {
      buffer = (char *)e_get_buffer (sizeof (char));
      *buffer = test++;

      e_send_message (0, 0, buffer);
   }
}

void gfx_task_2 (void)
{
   char *buffer;
   char out[64];
   FOREVER
   {
      e_recv_message (0, &buffer);

      if (buffer != NULL)
      {
         sprintf (out, "output is: %d\n", *buffer);
         debug_write_to_output (out);

         e_free_buffer (buffer);
      }
   }
}

void gfx_task_3 (void)
{
   volatile int test;
test = 1; 
   while (test!=0)
   {
      test++;
   }
}
