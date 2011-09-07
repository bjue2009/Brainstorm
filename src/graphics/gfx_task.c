/******************************************************************************
 * Module - GFX
 * Description - This file contains the task definition for the graphics module
 *****************************************************************************/

/* domain includes */
#include <gfx_api.h>
#include <e_msg_queue_api.h>
#include <e_buffer_api.h>
#include <eng_api.h>

/* global includes */

/* other  includes */
#include <gfx_private.h>
#include <debug.h>

#include "SDL_TTF.h"

static SDL_Surface* screen;
SDL_mutex* sat_mutex;
ulong frame;
ulong ticks;
ulong last_update;
char fps_string[64];
TTF_Font* font;

SDL_Surface* textSurface;
SDL_Surface* view_text_surface;

SDL_Color foregroundColor = { 255, 255, 255 }; 
SDL_Color backgroundColor = { 0, 0, 255 };


SDL_Rect textLocation = { 100, 100, 0, 0 };
g_motion_type* target;

/* pointer to life sats */
g_sat_entity_type   *life_sats;
/******************************************************************************
 * gfx_task - task for graphics module
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void gfx_task (void)
{
   char           *msg;
   e_message_type  msg_type;   
   ulong             i;
   SDL_Rect          rect;

   gfx_init_tile_system();

   FOREVER
   {
      msg_type = e_recv_message (E_GRAPHICS_QUEUE, &msg);

      if (msg_type != E_NO_MSG)
      {
         switch (msg_type)
         {
            case GT_MSG_PERFORM_DRAW:
            {
               ulong off_x;
               ulong off_y;

               view_get_view_rect (&off_x, &off_y);

               sat_mutex = eng_get_sat_mutex();


               SDL_mutexP (sat_mutex);

               /* clear screen */   
               SDL_FillRect(screen,NULL, 0x000000); 
               rect.h = 4;
               rect.w = rect.h;

               for (i = 0; i < G_NUM_LIFE_SATS; i++)
               {
                  rect.x = (long)400 + life_sats[i].position[G_X];
                  rect.y = (long)300 + life_sats[i].position[G_Y];

                  rect.x -= off_x;
                  rect.y -= off_y;

                  if (i == (G_NUM_LIFE_SATS - 1))
                  {
                     SDL_FillRect (screen, &rect, 0x00ff0000);
                  }
                  else
                  {
                     SDL_FillRect (screen, &rect, 0x00ffff00);
                  }
               }

               rect.x = (long)400 + target->position[G_X];
               rect.y = (long)300 + target->position[G_Y];
               SDL_FillRect (screen, &rect, 0xffffffff);
               


               
#if DEBUG_SHOW_FPS == CFG_ON /* enable FPS tagging */
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
                  //SDL_WM_SetCaption (fps_string, NULL);

                  //Restart the update timer
                  last_update = ticks;

                  
                  textSurface = TTF_RenderText_Shaded (font,
                                                       fps_string, 
                                                       foregroundColor, 
                                                       backgroundColor);

                  

                  
                  


               }
               textLocation.x = 100;
                  textLocation.y = 100;
               SDL_BlitSurface (textSurface, 
                                   NULL, 
                                   screen, 
                                   &textLocation);
#endif

#if DEBUG_VIEW_RECT == CFG_ON
               sprintf (fps_string,
                           "View (%u, %u)",
                           off_x,
                           off_y);
               textLocation.x = 0;
               textLocation.y = 0;

               view_text_surface = TTF_RenderText_Shaded (font,
                                                    fps_string, 
                                                    foregroundColor, 
                                                    backgroundColor);
               SDL_BlitSurface (view_text_surface, 
                                NULL, 
                                screen, 
                                &textLocation);

#endif
               
	       test_drawing_tiles();

               SDL_Flip (screen);    

               SDL_mutexV (sat_mutex);
            }
            break;

            case GT_MSG_SET_VIEW_RECT:
               view_set_view_rect (((g_location_type*) msg)->x,
                                   ((g_location_type*) msg)->y);
               break;

            default:
               TRIGGER_ERROR(99);
         }

         if (msg != NULL)
         {
            e_free_buffer (msg);
         }
      }
   }
}

void gfx_init (void)
{
   screen = SDL_SetVideoMode (G_MAX_SCREEN_WIDTH, 
                              G_MAX_SCREEN_HEIGHT, 
                              32, 
                              SDL_SWSURFACE);

   life_sats = eng_get_unit_db()->life_sats;

   target = eng_get_pod();

   frame       = 0;
   ticks       = 0;
   last_update = 0;

   TTF_Init();

   font = TTF_OpenFont("ARIAL.TTF", 12);


}

SDL_Surface *get_screen (void)
{
   return screen;
}
