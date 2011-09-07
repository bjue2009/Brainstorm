/******************************************************************************
 * Module - EXEC
 * Description - This file contains the definitions required for allocating 
 *               dynamic memory for the system
 *****************************************************************************/

/* domain includes */
#include <e_buffer_api.h>

/* global includes */
#include <g_memops.h>

/* other  includes */
#include "SDL_mutex.h"
#include <debug.h>


/* defines how many of each buffer there are */
#define E_NUM_SMALL_BUFFER   (1000)
#define E_NUM_MEDIUM_BUFFER  (1000)
#define E_NUM_LARGE_BUFFER   (1000)
#define E_NUM_SUPER_BUFFER   (1000)

#define E_HEADER_SIZE (sizeof (e_buffer_header_type))

/* defines size of each buffer in bytes */
#define E_SIZE_SMALL_BUFFER   (64)
#define E_SIZE_MEDIUM_BUFFER  (128)
#define E_SIZE_LARGE_BUFFER   (256)
#define E_SIZE_SUPER_BUFFER   (1024)

/* define size of each memory pool */
#define E_SMALL_POOL_SIZE  (E_NUM_SMALL_BUFFER  * (E_SIZE_SMALL_BUFFER  + E_HEADER_SIZE))
#define E_MEDIUM_POOL_SIZE (E_NUM_MEDIUM_BUFFER * (E_SIZE_MEDIUM_BUFFER + E_HEADER_SIZE))
#define E_LARGE_POOL_SIZE  (E_NUM_LARGE_BUFFER  * (E_SIZE_LARGE_BUFFER  + E_HEADER_SIZE))
#define E_SUPER_POOL_SIZE  (E_NUM_SUPER_BUFFER  * (E_SIZE_SUPER_BUFFER  + E_HEADER_SIZE))

#define E_TOTAL_BUFFER_SIZE (E_SMALL_POOL_SIZE + E_MEDIUM_POOL_SIZE + \
                             E_LARGE_POOL_SIZE + E_SUPER_POOL_SIZE)

typedef struct E_BUF_ENVIR_TYPE
{
   ulong                   in_use_count; /* number of buffers in use */
   ulong                   buffer_count; /* number of buffers */
   e_buffer_header_type    *first;       /* first buffer in the list */
}e_buf_envir_type;
                             
static e_buf_envir_type e_buf_envir[E_NUM_BUFFER_TYPE];

/* declaration for block of memory used by application */
static char e_buffers[E_TOTAL_BUFFER_SIZE];

/* mutext for buffers */
static SDL_mutex* e_buf_mutex;
/******************************************************************************
 * e_init_buffers - initializes buffers
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void e_init_buffers(void)
{
   e_buffer_header_type  *temp;
   e_buffer_header_type  *buf;
   ulong i;

   e_buf_mutex = SDL_CreateMutex();

   g_memset (e_buf_envir, 0, sizeof (e_buf_envir));

   temp = (e_buffer_header_type*) &e_buffers[0];


   

   /* initialize small buffers */
   for (i = 0; i < E_NUM_SMALL_BUFFER; i++)
   {
      /* initialize buffer information */
      temp->buffer_type = E_SMALL_BUFFER;
      temp->id          = i;
      temp->in_use      = FALSE;

      /* grab pointer to first node */
      buf = e_buf_envir[E_SMALL_BUFFER].first;

      /* set the temp's next ptr to current first node */
      (e_buffer_header_type*) temp->next = buf;

      /* set the first pointer to the new temp ptr */
      e_buf_envir[E_SMALL_BUFFER].first = temp;

      /* increment number of buffers */
      e_buf_envir[E_SMALL_BUFFER].buffer_count++;

      /* move ptr to start of next buffer */
      (uchar*)temp += (E_HEADER_SIZE + E_SIZE_SMALL_BUFFER);
   }

   /* initialize meduim buffers */
   for (i = 0; i < E_NUM_MEDIUM_BUFFER; i++)
   {
      /* initialize buffer information */
      temp->buffer_type = E_MEDIUM_BUFFER;
      temp->id          = i;
      temp->in_use      = FALSE;

      /* grab pointer to first node */
      buf = e_buf_envir[E_MEDIUM_BUFFER].first;

      /* set the temp's next ptr to current first node */
      (e_buffer_header_type*) temp->next = buf;

      /* set the first pointer to the new temp ptr */
      e_buf_envir[E_MEDIUM_BUFFER].first = temp;

      /* increment number of buffers */
      e_buf_envir[E_MEDIUM_BUFFER].buffer_count++;

      /* move ptr to start of next buffer */
      (uchar*)temp += (E_HEADER_SIZE + E_SIZE_MEDIUM_BUFFER);
   }

   /* initialize large buffers */
   for (i = 0; i < E_NUM_LARGE_BUFFER; i++)
   {
      /* initialize buffer information */
      temp->buffer_type = E_LARGE_BUFFER;
      temp->id          = i;
      temp->in_use      = FALSE;

      /* grab pointer to first node */
      buf = e_buf_envir[E_LARGE_BUFFER].first;

      /* set the temp's next ptr to current first node */
      (e_buffer_header_type*) temp->next = buf;

      /* set the first pointer to the new temp ptr */
      e_buf_envir[E_LARGE_BUFFER].first = temp;

      /* increment number of buffers */
      e_buf_envir[E_LARGE_BUFFER].buffer_count++;

      /* move ptr to start of next buffer */
      (uchar*)temp += (E_HEADER_SIZE + E_SIZE_LARGE_BUFFER);
   }

   /* initialize super buffers */
   for (i = 0; i < E_NUM_SUPER_BUFFER; i++)
   {
      /* initialize buffer information */
      temp->buffer_type = E_SUPER_BUFFER;
      temp->id          = i;
      temp->in_use      = FALSE;

      /* grab pointer to first node */
      buf = e_buf_envir[E_SUPER_BUFFER].first;

      /* set the temp's next ptr to current first node */
      (e_buffer_header_type*) temp->next = buf;

      /* set the first pointer to the new temp ptr */
      e_buf_envir[E_SUPER_BUFFER].first = temp;

      /* increment number of buffers */
      e_buf_envir[E_SUPER_BUFFER].buffer_count++;

      /* move ptr to start of next buffer */
      (uchar*)temp += (E_HEADER_SIZE + E_SIZE_SUPER_BUFFER);
   }
}


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
   e_buffer_header_type *header;
   e_buffer_size_type   type;



   if (SDL_mutexP (e_buf_mutex) == 0)
   {
      if (size > E_SIZE_LARGE_BUFFER)
      {
         type = E_SUPER_BUFFER;
      }
      else if (size > E_SIZE_MEDIUM_BUFFER)
      {
         type = E_LARGE_BUFFER;
      }
      else if (size > E_SIZE_SMALL_BUFFER)
      {
         type = E_MEDIUM_BUFFER;
      }
      else
      {
         type = E_SMALL_BUFFER;
      }

      if (e_buf_envir[type].in_use_count < e_buf_envir[type].buffer_count)
      {
         /* grab pointer to first buffer in list */
         header = e_buf_envir[type].first;
         header->in_use = TRUE;
         e_buf_envir[type].in_use_count++;
         
         /* set first buffer equal to next buffer */
         e_buf_envir[type].first = (e_buffer_header_type*) header->next;

         /* set return value to current buffer */
         buffer = (void*)((ulong)header + E_HEADER_SIZE);
      }
      else
      {
         /* TODO throw error about being out of buffers */
         buffer = NULL;
         TRIGGER_ERROR(3);
      }

      if (SDL_mutexV(e_buf_mutex) != 0)
      {
         /* ERROR because we could not release the mutex */
         TRIGGER_ERROR(0);
      }

   }
   else
   {
      /* error because we failed to get the mutex */
      TRIGGER_ERROR(1);
   }
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

void e_free_buffer (void *ptr)
{
#if   CFG_BUILD_FOR_PC     == CFG_ON
   e_buffer_header_type *header;
   e_buffer_size_type   type;

   if (SDL_mutexP (e_buf_mutex) == 0)
   {
      /* get start of the buffer */
      header = (e_buffer_header_type*)((ulong)ptr - E_HEADER_SIZE);
      type   = header->buffer_type;

      /* set the next ptr equal to the first buffer in the list */
      (e_buffer_header_type*) header->next = e_buf_envir[type].first;

      /* place the header at the front of the list */
      e_buf_envir[type].first = header;
      e_buf_envir[type].in_use_count--;

      /* update buffer info */
      header->in_use = FALSE;
      ptr = NULL;

      if (SDL_mutexV (e_buf_mutex) != 0)
      {
         /* error because we failed to uNLOCK the mutex */
         TRIGGER_ERROR(4);
      }
   }
   else
   {
      /* TODO error because we failed to loock the mutx */
      TRIGGER_ERROR(5);
   }

#elif CFG_BUILD_FOR_MAC    == CFG_ON
   free (ptr);
#elif CFG_BUILD_FOR_IPHONE == CFG_ON
   free (ptr);
#elif CFG_BUILD_FOR_LINUX  == CFG_ON
   free (ptr);
#else
   printf ("ERROR no platform specified for e_get_buffer");
#endif
}