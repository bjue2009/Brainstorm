/******************************************************************************
 * Module - GLOBAL
 * Description - This file contains the definitions for utility functions that
 *               can be used throughout the program
 *****************************************************************************/

/* domain includes */
/* global includes */
#include <g_utilities.h>
/* other  includes */

/******************************************************************************
 * g_get_distance - returns distance between two points
 * Description - Determine the euclidean distance between two points
 *****************************************************************************/
float g_get_distance(g_position_type to,
                     g_position_type from)
{
   /* TODO replace this with taylor series approximation to avoid expensive calculations*/
   float distance;

   distance = sqrt (pow (to[G_X]-from[G_X], 2) + 
                    pow (to[G_Y]-from[G_Y], 2) + 
                    pow (to[G_Z]-from[G_Z], 2));

   return distance;
}