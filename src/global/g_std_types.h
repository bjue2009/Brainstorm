#ifndef G_STD_TYPES_H
#define G_STD_TYPES_H

/* domain includes */
#include <platform.h>
/* global includes */
/* other  includes */

typedef unsigned int  ulong;
typedef unsigned char uchar;
typedef unsigned char boolean;

/* this defines structure that holds location value in 3 dimensions.
 * the coordinate system used is ECEF (Earth Centered Earth Fixed) with
 * the z axis parallel to the Earth's axis and the XY plane parallel to the
 * equator with the x axis pointing towards 0 degrees latitude and longitude
 */
typedef struct G_LOCATION_TYPE
{
   float x;
   float y;
   float z;
}g_location_type;




#endif