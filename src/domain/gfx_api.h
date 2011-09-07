#ifndef GFX_API_H
#define GFX_API_H

/******************************************************************************
 * Module - GFX
 * Description - This file contains the task definition for the graphics module
 *****************************************************************************/

/* domain includes */
#include <platform.h>
/* global includes */
#include <g_std_types.h>
/* other  includes */

typedef enum GFX_TILE_TYPE
{
   GFX_TILE_VOID,
   GFX_TILE_GRASS,
   GFX_TILE_WATER,
   GFX_TILE_BRICK_WALL,
   GFX_TILE_TREE,
   GFX_TILE_BRICK_DOOR,
   GFX_TILE_TOP_LEFT_BRICK,
   GFX_TILE_TOP_RIGHT_BRICK,
   GFX_TILE_BOTTOM_LEFT_BRICK,
   GFX_TILE_BOTTOM_RIGHT_BRICK,
   GFX_TILE_TOP_LEFT_TEMPLE,
   GFX_TILE_TEMPLE_WALL,
   GFX_TILE_TOP_RIGHT_TEMPLE,
   GFX_TILE_FANCY_FLOOR,
   GFX_TILE_TOP_WATER,
   GFX_TILE_BOTTOM_WATER,
   GFX_TILE_LEFT_WATER,
   GFX_TILE_RIGHT_WATER,
   GFX_TILE_TOP_RIGHT_WATER,
   GFX_TILE_BOTTOM_RIGHT_WATER,
   GFX_TILE_BOTTOM_LEFT_WATER,
   GFX_TILE_TOP_LEFT_WATER,
   GFX_TILE_DIRT_1,
   GFX_TILE_DIRT_2,
   GFX_TILE_DIRT_3,
   GFX_NUM_TILES    /* this needs to be the last tile */
}gfx_tile_type;

/* tile dimensions in pixels */
#define GFX_TILE_WIDTH  (64)
#define GFX_TILE_HEIGHT (64)


/******************************************************************************
 * gfx_task - task for graphics module
 *****************************************************************************/
void gfx_task (void);

/******************************************************************************
 * gfx_init - initializes graphics module
 *****************************************************************************/
void gfx_init (void);


/******************************************************************************
 * gfx_init_tile_system - initializes the tile system
 *****************************************************************************/
void gfx_init_tile_system (void);


#endif /* GFX_API_H */
