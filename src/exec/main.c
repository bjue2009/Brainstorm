/******************************************************************************
 * Module - EXEC
 * Description - This file will contain the main game loop and is the entry
 *               point for the executable
 *****************************************************************************/

/* domain includes */

/* global includes */
#include <g_std_types.h>
#include <g_utilities.h>
/* other  includes */
#include <math.h>
#include "SDL.h"
#include "SDL_timer.h"

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
   //The images
//the code below tests the capability to drive a satellite's position
   // and update according to the laws of physics and to draw it.
   int i,j;//iterations to draw
#define NUM_SATS (1600)
   g_position_type sat[NUM_SATS];
   ulong thetas[NUM_SATS];
   ulong phis[NUM_SATS];
   g_position_type camera;
   float current_distance;
   int frame;
   int ticks;
   int last_update;

   char fps_string[64];
   float hypotenuse, height;


   SDL_Rect rect;
   SDL_Surface* hello = NULL;
   SDL_Surface* screen = NULL;
#define RADIUS (300)

   camera[G_X] = 0;
   camera[G_Y] = 0;
   camera[G_Z] = 0;
   frame = 0;
   ticks = 0;
   last_update = 0;
   //Start SDL
   SDL_Init (SDL_INIT_EVERYTHING);

   //Set up screen
   screen = SDL_SetVideoMode (640, 480, 32, SDL_SWSURFACE);


   for (j = 0; j < NUM_SATS; j++)
   {
      thetas[j] = rand()%360;
      phis[j]   = rand()%360;
   }

   //Load image
   //hello = SDL_LoadBMP( "hello.bmp" );
   for (i = 0; i < 90; i++)
   {//add in support for phi and pi
      /*TODO optimize trig functions by using lookup tables instead */
      SDL_FillRect(screen,NULL, 0x000000); 

      for (j = 0; j < NUM_SATS; j++)
      {
         thetas[j]++;
         phis[j]++;

         sat[j][G_X] = RADIUS * cos(thetas[j]*M_PI/180.0) * sin(phis[j]*M_PI/180.0);
         sat[j][G_Y] = RADIUS * sin(thetas[j]*M_PI/180.0) * sin(phis[j]*M_PI/180.0);
         sat[j][G_Z] = RADIUS * cos(phis[j]*M_PI/180.0);



         current_distance = g_get_distance (camera, sat[j]);

        // if (current_distance < RADIUS)
         {
            rect.x = 320 + sat[j][G_X];
            rect.y = 240 - sat[j][G_Z];
            rect.h = (2*RADIUS - current_distance)*.05+1;
            rect.w = rect.h;
            SDL_FillRect (screen, &rect, 0x00ffff00);
         }
#if 0
            (thetas[j]<<24) ||
            (phis[j]<<16)   ||
            (thetas[j]<<8)  ||
            (phis[j]));

#endif
      }
      

      



      
      SDL_Delay (30);
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

   return 0;
}