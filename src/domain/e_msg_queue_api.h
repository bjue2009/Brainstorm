#ifndef E_MSG_QUEUE_API_H
#define E_MSG_QUEUE_API_H
/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations required for communicating
 *               between the different tasks via message passing
 *****************************************************************************/
/* domain includes */
#include <e_msgs.h>
#include <e_krn_defs.h>
#include <e_buffer_api.h>

/* global includes */
#include <g_std_types.h>
/* other  includes */

typedef enum E_MSG_QUEUE_TYPE
{
   E_USER_INPUT_QUEUE,
   E_GRAPHICS_QUEUE,
   E_ENGINE_QUEUE,
   E_SOUND_QUEUE,
   E_NUM_QUEUES
}e_msg_queue_type;


/******************************************************************************
 * e_init_msg_queues - initializes msg queues
 * Description - based on the platform, should return buffer in constant run
 *               time O(1) TODO update this
 *****************************************************************************/
void e_init_msg_queues (void);

/******************************************************************************
 * e_send_message - returns buffer of specified size TODO update
 *****************************************************************************/
void e_send_message (e_msg_queue_type queue, e_message_type msg, void *ptr);

/******************************************************************************
 * e_recv_message - returns buffer of specified size TODO update
 *****************************************************************************/
e_message_type e_recv_message (e_msg_queue_type queue, void **ptr);

#endif /* E_BUFFER_API_H */