/******************************************************************************
 * Module - EXEC
 * Description - This file will contain the main game loop and is the entry
 *               point for the executable
 *****************************************************************************/

/* domain includes */
#include <e_msg_queue_api.h>
#include <e_buffer_api.h>
#include <gfx_api.h>

/* global includes */
#include <g_utilities.h>

/* other  includes */
#include <math.h>
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"

#include <debug.h>

int main (int argc, char *argv[])
{
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

   SDL_Surface* screen = NULL;
   /* initialize sub systems */
   e_init_msg_queues();
   debug_init_output();

   e_init_buffers();

   //Start SDL
   SDL_Init (SDL_INIT_EVERYTHING);

   //Set up screen
   screen = SDL_SetVideoMode (640, 480, 32, SDL_SWSURFACE);


   /* start tasks */
   SDL_CreateThread ((void*)gfx_task,   (void *) NULL);
   SDL_CreateThread ((void*)gfx_task_2, (void *) NULL);
   SDL_CreateThread ((void*)gfx_task_3, (void *) NULL);

   SDL_Quit();

#if 0 // REMOVE OTHER CODE 

      /* SCHEDULER  10 ms timer*/
      /* user input thread */
      /* graphics thread */
      /* AI thread */
      /* sound thread */

   /* initialize threads for sub systems */

   /* start threads for sub systems */
   //The images
//the code below tests the capability to drive a satellite's position
   // and update according to the laws of physics and to draw it.
   int i,j;//iterations to draw
#define NUM_SATS (1)
   g_position_type sat[NUM_SATS];
   ulong thetas[NUM_SATS];
   ulong phis[NUM_SATS];
   int   offset[NUM_SATS];
   g_position_type camera;
   float current_distance;
   int frame;
   int ticks;
   int last_update;
   char output_debug[128];
   char fps_string[64];
   float hypotenuse, height;
   double aspect;

   double x, y, z;
   double field_x, field_y;
   SDL_Rect rect;
   SDL_Surface* hello = NULL;
   SDL_Surface* screen = NULL;
#define RADIUS (200)

   camera[G_X] = RADIUS;
   camera[G_Y] = 0;
   camera[G_Z] = 0;
   frame = 0;
   ticks = 0;
   last_update = 0;
   //Start SDL
   SDL_Init (SDL_INIT_EVERYTHING);

   //Set up screen
   screen = SDL_SetVideoMode (640, 480, 32, SDL_SWSURFACE);



  debug_init_output();

   for (j = 0; j < NUM_SATS; j++)
   {
      thetas[j] = rand()%360;
      phis[j]   = rand()%360;
      if (phis[j] > 180)
      {
         offset[j] = 1;
      }
      else
      {
         offset[j]= -1;
      }
   }
   aspect = 640.0/480.0;
   //Load image
   //hello = SDL_LoadBMP( "hello.bmp" );
   for (i = 0; i < 540; i++)
   {//add in support for phi and pi
      /*TODO optimize trig functions by using lookup tables instead */
      SDL_FillRect(screen,NULL, 0x000000); 

      for (j = 0; j < NUM_SATS; j++)
      {
         thetas[j] += offset[j];
         //phis[j]++;
#if 0
         sat[j][G_X] = RADIUS * cos(thetas[j]*M_PI/180.0) * sin(phis[j]*M_PI/180.0);
         sat[j][G_Y] = RADIUS * sin(thetas[j]*M_PI/180.0) * sin(phis[j]*M_PI/180.0);
         sat[j][G_Z] = RADIUS * cos(phis[j]*M_PI/180.0);
#else
         sat[j][G_X] = RADIUS * cos((double)thetas[j]*M_PI/180.0);
         sat[j][G_Y] = RADIUS * sin((double)thetas[j]*M_PI/180.0);

#endif

         x = sat[j][G_X] - camera[G_X];
         y = sat[j][G_Y] - camera[G_Y];
         z = sat[j][G_Z] - camera[G_Z];
         current_distance = g_get_distance (camera, sat[j]);

        // if (current_distance < RADIUS)
         {
#if 0
            field_x = x / (-z * tan(M_PI / 2));

            field_y = (y * aspect) / (-z * tan(M_PI / 2));

            rect.x = (short)(640.0 * (field_x+1.0)/2.0);
            rect.y = (short)(480.0 * (1-((field_y+1.0)/2.0)));
#endif

#if 0
            rect.x = (long)(((640.0) * (sat[j][G_X])/(2 * RADIUS)) + 320 );
            rect.y = (long)(((480.0) * (sat[j][G_Y])/(2 * RADIUS)) + 240 );
#else
            rect.x = (long)320 + sat[j][G_X];
            rect.y = (long)240 + sat[j][G_Y];
#endif
        
            sprintf (output_debug, 
                     "%d:, %d, %d, %f, %u\n",
                     j,
                     rect.x,
                     rect.y,
                     current_distance,
                     thetas[j]);

          
            debug_write_to_output (output_debug);

            rect.h = 20;
            rect.w = rect.h;

            SDL_FillRect (screen, &rect, 0x00ffff00);
         }

      }
      

      



      
      SDL_Delay (15);
      SDL_Flip( screen );

      //Increment the frame counter
      frame++;
      //If a second has passed since the caption was last updated
      ticks = SDL_GetTicks();
      if (ticks - last_update > 1000)
      {
         sprintf (fps_string,
                  "Average Frames Per Second: %f",
                  frame / ( ticks / 1000.f ));

         //Reset the caption
         SDL_WM_SetCaption( fps_string, NULL );

         //Restart the update timer
         last_update = ticks;
      }
      //update accleration
      //update velocity
      //update position

      //clean screen
      //draw satellite
      //flip screen
   }
   //Apply image to screen
   //SDL_BlitSurface( hello, NULL, screen, NULL );

   //Update Screen
   SDL_Flip( screen );

   //Pause
   SDL_Delay( 2000 );

   //Free the loaded image
   //SDL_FreeSurface( hello );

   //Quit SDL
   SDL_Quit();
#endif
   debug_stop();
   return 0;
}