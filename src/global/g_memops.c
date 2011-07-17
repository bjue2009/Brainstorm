/******************************************************************************
 * Module - GLOBAL
 * Description - This file contains the definitions for utility functions that
 *               copy and set memory
 *****************************************************************************/

/* domain includes */
/* global includes */
#include <g_memops.h>
/* other  includes */

/******************************************************************************
 * g_memset - sets value at ptr
 *****************************************************************************/
void g_memset (void *ptr, int value, ulong size)
{
   memset (ptr, value, size);
}

/******************************************************************************
 * g_memcpy - copy value at ptr
 *****************************************************************************/
void g_memcpy (void *dst, void *src, ulong size)
{
   memcpy (dst, src, size);
}