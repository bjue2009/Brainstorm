#ifndef G_STD_TYPES_H
#define G_STD_TYPES_H

/******************************************************************************
 * Module - GLOBAL
 * Description - This file contains basic structure declarations that will be 
 *               used throughout the game and its various sub modules
 *****************************************************************************/

/* domain includes */
#include <platform.h>
/* global includes */
/* other  includes */

typedef unsigned int  ulong;
typedef unsigned char uchar;
typedef unsigned char boolean;

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


/* screen width in pixels */
#define G_MAX_SCREEN_WIDTH (800)
/* screen height in pixels */
#define G_MAX_SCREEN_HEIGHT (600)

#define G_MAX_RADIUS (G_MAX_SCREEN_HEIGHT / 2)

/* this defines structures that hold location value in 3 dimensions.
 * the coordinate system used is ECEF (Earth Centered Earth Fixed) with
 * the z axis parallel to the Earth's axis and the XY plane parallel to the
 * equator with the x axis pointing towards 0 degrees latitude and longitude
 * and the origin at the center of the Earth
 */
typedef enum G_3D_ELEMENT_TYPE
{
   G_X,
   G_Y,
   G_Z,
   G_MAX_DIMENSIONS
}g_3d_element_type;


typedef struct G_LOCATION_TYPE
{
   ulong x;
   ulong y;
}g_location_type;

#define NUM_SATS (5)
/* number of life satellites */
#define G_NUM_LIFE_SATS (15)

typedef float g_3d_array[G_MAX_DIMENSIONS];
typedef g_3d_array g_position_type;
typedef g_3d_array g_velocity_type;
typedef g_3d_array g_accel_type;

typedef struct G_MOTION_TYPE
{
   g_position_type position;
   g_velocity_type velocity;
   g_accel_type    accel;
}g_motion_type;

/* defines the type of satellites supported */
typedef enum G_SATELLITE_TYPE
{
   G_SAT_PLAIN,
   G_SAT_ATTACK,
   G_SAT_DEFENSE,
   G_SAT_SCAN
}g_satellite_type;

/* defines the types of players supported */
typedef enum G_PLAYER_TYPE
{
   G_PLAYER_AI,         /* AI Controlled   */
   G_PLAYER_NEUTRAL,    /* Neutral         */
   G_PLAYER_USER        /* User controlled */
}g_player_type;

typedef enum G_ORBIT_TYPE
{
   G_LOW_ORBIT,
   G_MEDIUM_ORBIT,
   G_HIGH_ORBIT
}g_orbit_type;

#define HEO_RADIUS (180) /* high earth orbit */
#define MEO_RADIUS (100) /* meadium earth orbit */
#define LEO_RADIUS (50)  /* low earth orbit */


/* defines the structure for a satellite */
typedef struct G_SAT_ENTITY_TYPE
{
   g_orbit_type      orbit;
   g_position_type   position;
   float             orbital_velocity;
   float             orbital_radius;
   int               theta;
   boolean           alive;
}g_sat_entity_type;

/* defines the structure for an enemy */
typedef struct G_ENEMY_TYPE
{
   g_orbit_type      orbit;
   g_position_type   position;
   int               hp;   
   boolean           alive;
}g_enemy_type;





#endif