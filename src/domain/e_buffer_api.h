#ifndef E_BUFFER_API_H
#define E_BUFFER_API_H
/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations required for allocating 
 *               dynamic memory for the system
 *****************************************************************************/
/* domain includes */
#include <e_msgs.h>
/* global includes */
#include <g_std_types.h>
/* other  includes */

/* definitions for the different sizes of buffers */
typedef enum E_BUFFER_SIZE_TYPE
{
   E_SMALL_BUFFER,
   E_MEDIUM_BUFFER,
   E_LARGE_BUFFER,
   E_SUPER_BUFFER,
   E_NUM_BUFFER_TYPE,
}e_buffer_size_type;


/* definition for buffer header type */
typedef struct E_BUFFER_HEADER_TYPE
{
   e_buffer_size_type            buffer_type;
   boolean                       in_use;
   ulong                         id;
   e_message_type                msg_type;
   struct e_buffer_header_type   *next;
}e_buffer_header_type;

/******************************************************************************
 * e_init_buffers - initializes buffers
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void e_init_buffers(void);

/******************************************************************************
 * e_get_buffer - returns buffer of specified size 
 *****************************************************************************/
void *e_get_buffer(ulong size);

/******************************************************************************
 * e_free_buffer - frees buffer pointed to by ptr
 *****************************************************************************/
void e_free_buffer (void *ptr);

#endif /* E_BUFFER_API_H */