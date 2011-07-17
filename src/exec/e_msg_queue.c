/******************************************************************************
 * Module - EXEC
 * Description - This file contains the definitions for communicating between
 *               the different tasks via message queues.
 *****************************************************************************/

/* domain includes */
#include <e_msg_queue_api.h>
#include <e_buffer_api.h>
#include <e_krn_defs.h>


/* global includes */
/* other  includes */

/* msg queue definitions */
typedef struct MSG_QUEUE_TYPE
{
   ulong                    msg_count;
   e_buffer_header_type     *first;
   e_buffer_header_type     *last_node;
}msg_queue_type;

/* each task will have its own queue */
static msg_queue_type msg_queue[E_NUM_QUEUES];

/* mutex for message queues */
static SDL_mutex* e_msg_mutex;

/******************************************************************************
 * e_init_msg_queues - initializes msg queues
 * Description - based on the platform, should return buffer in constant run
 *               time O(1) TODO update this
 *****************************************************************************/
void e_init_msg_queues (void)
{
   memset (msg_queue, 0, sizeof (msg_queue));
   e_msg_mutex = SDL_CreateMutex();
}

/******************************************************************************
 * e_send_message - sends a message to the specified task
 * Description - based on the platform, should return buffer in constant run
 *               time O(1) TODO update this
 *****************************************************************************/
void e_send_message (e_msg_queue_type queue, e_message_type msg, void *ptr)
{
   if (SDL_mutexP (e_msg_mutex) == 0)
   {
      e_buffer_header_type *temp;
      
      /* get address of header from buffer */
      temp = (e_buffer_header_type*)((ulong)ptr - sizeof (e_buffer_header_type));

      /* assign message type to buffer header */
      temp->msg_type = msg;

      /* if the node is empty, need to set the first pointer */
      if (msg_queue[queue].msg_count == 0)
      {
         msg_queue[queue].first     = ptr;
         msg_queue[queue].last_node = ptr;
      }
      else
      {
         /* set next pointer of last node to new node */
         temp = (e_buffer_header_type*) ((ulong)msg_queue[queue].last_node - sizeof (e_buffer_header_type));
         temp->next = ptr;

         /* set the last node pointer to the last node */
         msg_queue[queue].last_node = ptr;
      }
      /* increment msg_count */
      msg_queue[queue].msg_count++;

      if (SDL_mutexV (e_msg_mutex) != 0)
      {
         /* error because we failed to unlock the mutex */
         TRIGGER_ERROR(5);
      }
   }
   else
   {
      /* error because we failed to lock the mutex */
      TRIGGER_ERROR(6);
   }
}

/******************************************************************************
 * e_recv_message - returns buffer of specified size TODO update
 *****************************************************************************/
/* TODO add an option here to wait for a message or to not wait */
e_message_type e_recv_message (e_msg_queue_type queue, void **ptr)
{
   e_message_type       msg_type;
   e_buffer_header_type *temp;

   if (SDL_mutexP (e_msg_mutex) == 0)
   {
      msg_type = E_LAST_MESSAGE;

      if (msg_queue[queue].msg_count != 0)
      {
         /* get the message type from the buffer header */
         temp = (e_buffer_header_type*)
            ((ulong)msg_queue[queue].first - sizeof (e_buffer_header_type));
            
         msg_type = temp->msg_type;

         /* grab the node at the front of the queue */
         *ptr = msg_queue[queue].first;

         /* move first pointer to next node */
         msg_queue[queue].first = (e_buffer_header_type*) temp->next;
         /* decrement msg_count */
         msg_queue[queue].msg_count--;
      }
      else
      {
         /* TODO WAIT FOR MSG OR GOTO SLEEP */
         *ptr = NULL;
      }

      if (SDL_mutexV (e_msg_mutex) != 0)
      {
         /* error because we faile dto unlock the mutex */
         TRIGGER_ERROR(7);
      }
   }
   else
   {
      /* error because we failed to lock the mutex */
      TRIGGER_ERROR(8);
   }

   return msg_type;
}