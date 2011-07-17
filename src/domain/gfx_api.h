#ifndef GFX_API_H
#define GFX_API_H

/******************************************************************************
 * Module - GFX
 * Description - This file contains the task definition for the graphics module
 *****************************************************************************/

/* domain includes */
#include <platform.h>
/* global includes */
/* other  includes */


/******************************************************************************
 * gfx_task - task for graphics module
 * Description - based on the platform, should return buffer in constant run
 *               time O(1)
 *****************************************************************************/
void gfx_task (void);
void gfx_task_2 (void);
void gfx_task_3 (void);

#endif /* GFX_API_H */