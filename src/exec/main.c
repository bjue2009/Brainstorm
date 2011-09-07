/******************************************************************************
 * Module - EXEC
 * Description - This file will contain the main game loop and is the entry
 *               point for the executable
 *****************************************************************************/

/* domain includes */
#include <e_msg_queue_api.h>
#include <e_buffer_api.h>
#include <gfx_api.h>
#include <eng_api.h>

/* global includes */
#include <g_utilities.h>

/* other  includes */
#include <e_scheduler.h>

#include <math.h>
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"

#include <debug.h>

int main (int argc, char *argv[])
{
  volatile ulong test_x;
  volatile ulong test_y;
  void     *ptr;
/******************************************************************************
 * game loop description:
 * Initialize all game modules: graphics, input, logic, libraries, etc
 * While user has not 'quit'
 *    Update Satellite Locations
 *    Update Satellite targets
 *    Update projectiles
 *       Update for hits
 *    Draw all objects(lock to 30fps)
 *    Update user input
 *****************************************************************************/
   SDL_Event sdl_event;
   boolean quit;
   /* initialize sub systems */
   e_init_msg_queues();
   debug_init_output();

   e_init_buffers();

   e_init_scheduler();

   //Start SDL
   SDL_Init (SDL_INIT_EVERYTHING);
   eng_init();
   gfx_init();
   


   /* start tasks */
   SDL_CreateThread ((void*)gfx_task,   (void *) NULL);
   SDL_CreateThread ((void*)eng_task,   (void *) NULL);
   //SDL_CreateThread ((void*)gfx_task_3, (void *) NULL);

   e_start_scheduler();

   quit = FALSE;

   test_x = 0;
   test_y = 0;
   /* enter main game loop, this should be replaced with a
    * "idle loop"
    */
   while (quit == FALSE)
   {
      //If there's an event to handle
        if( SDL_PollEvent( &sdl_event ) )
        {
            //If a key was pressed
            if( sdl_event.type == SDL_KEYDOWN )
            {

                
                switch( sdl_event.key.keysym.sym )
                {
                    case SDLK_0:
                       switch_target();
                       break;
                    
                    case SDLK_UP:
                       test_y-=10;
                       ptr = e_get_buffer (sizeof (g_location_type));
                       ((g_location_type *) ptr)->x = test_x;
                       ((g_location_type *) ptr)->y = test_y;    
                       e_send_message (E_GRAPHICS_QUEUE, GT_MSG_SET_VIEW_RECT, ptr);
                       break;

                    case SDLK_DOWN:
                       test_y+=10;
                       ptr = e_get_buffer (sizeof (g_location_type));
                       ((g_location_type *) ptr)->x = test_x;
                       ((g_location_type *) ptr)->y = test_y;    
                       e_send_message (E_GRAPHICS_QUEUE, GT_MSG_SET_VIEW_RECT, ptr);
                       break;

                    case SDLK_LEFT:
                       test_x-=10;
                       ptr = e_get_buffer (sizeof (g_location_type));
                       ((g_location_type *) ptr)->x = test_x;
                       ((g_location_type *) ptr)->y = test_y;    
                       e_send_message (E_GRAPHICS_QUEUE, GT_MSG_SET_VIEW_RECT, ptr);
                       break;

                    case SDLK_RIGHT:
                       test_x+=10;
                       ptr = e_get_buffer (sizeof (g_location_type));
                       ((g_location_type *) ptr)->x = test_x;
                       ((g_location_type *) ptr)->y = test_y;    
                       e_send_message (E_GRAPHICS_QUEUE, GT_MSG_SET_VIEW_RECT, ptr);
                       break;
                    
                    case SDLK_ESCAPE: 
                       quit = TRUE;
                       break;
                }
            }
            
            //If the user has Xed out the window
            else if( sdl_event.type == SDL_QUIT )
            {
                //Quit the program
                quit = TRUE;
            }
        }
   }

   SDL_Quit();
   debug_stop();
   return 0;
}