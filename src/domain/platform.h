#ifndef PLATFORM_H
#define PLATFORM_H

/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations determining the platform
 *               for which this executable will run on
 *****************************************************************************/

/* declaration for boolean values */
#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/* declaration for configuration values */
#define CFG_ON  (1)
#define CFG_OFF (0)

/* shows coordinates of view rect */
#define DEBUG_VIEW_RECT (CFG_ON)
#define DEBUG_SHOW_FPS  (CFG_ON)

/* determines which platform to build for, only one of these should be enabled */
#define CFG_BUILD_FOR_PC      CFG_ON
#define CFG_BUILD_FOR_MAC     CFG_OFF
#define CFG_BUILD_FOR_IPHONE  CFG_OFF
#define CFG_BUILD_FOR_LINUX   CFG_OFF

#if CFG_BUILD_FOR_PC == CFG_ON
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "SDL.h"
#include "SDL_mutex.h"
#include "SDL_timer.h"
/* disable warnings */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#define FOREVER while (1)\


#endif /* PLATFORM_H */