#ifndef G_MEMOPS_H
#define G_MEMOPS_H

/******************************************************************************
 * Module - GLOBAL
 * Description - This file contains the definitions for utility functions that
 *               copy and set memory
 *****************************************************************************/

/* domain includes */
#include <platform.h>
/* global includes */
#include <g_std_types.h>
/* other  includes */


/******************************************************************************
 * g_memset - sets value at ptr
 *****************************************************************************/
void g_memset (void *ptr, int value, ulong size);

/******************************************************************************
 * g_memcpy - copy value at ptr
 *****************************************************************************/
void g_memcpy (void *dst, void *src, ulong size);



#endif /* G_MEMOPS_H */