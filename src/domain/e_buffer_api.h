#ifndef E_BUFFER_API_H
#define E_BUFFER_API_H
/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations required for allocating 
 *               dynamic memory for the system
 *****************************************************************************/
/* domain includes */

/* global includes */
#include <g_std_types.h>
/* other  includes */


/******************************************************************************
 * e_get_buffer - returns buffer of specified size 
 *****************************************************************************/
void *e_get_buffer(ulong size);

#endif /* E_BUFFER_API_H */