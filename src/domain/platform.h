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
#endif


#endif /* PLATFORM_H */