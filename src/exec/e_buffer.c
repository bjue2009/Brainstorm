/******************************************************************************
 * Module - EXEC
 * Description - This file contains the definitions required for allocating 
 *               dynamic memory for the system
 *****************************************************************************/

/* domain includes */
#include <e_buffer_api.h>

/* global includes */
/* other  includes */


/******************************************************************************
 * e_get_buffer - returns buffer of specified size 
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void *e_get_buffer(ulong size)
{
   void *buffer;
/* TODO below needs to be replaced with memory allocation scheme that is best suited
   for whatever platform is being used 
 */
#if   CFG_BUILD_FOR_PC     == CFG_ON
   buffer = (void*) malloc (sizeof (char) * size);
#elif CFG_BUILD_FOR_MAC    == CFG_ON
   buffer = (void*) malloc (sizeof (char) * size);
#elif CFG_BUILD_FOR_IPHONE == CFG_ON
   buffer = (void*) malloc (sizeof (char) * size);
#elif CFG_BUILD_FOR_LINUX  == CFG_ON
   buffer = (void*) malloc (sizeof (char) * size);
#else
   printf ("ERROR no platform specified for e_get_buffer");
#endif

   return buffer;
}