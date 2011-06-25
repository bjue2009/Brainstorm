#ifndef PLATFORM_H
#define PLATFORM_H

/* this file will include definitions pertaining to the different platforms
 * this game will be supported on 
 */

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


#endif /* PLATFORM_H */