#ifndef E_MSGS_H
#define E_MSGS_H
/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations for the various messages
 *               that are passed between the different tasks
 *****************************************************************************/
/* domain includes */
/* global includes */
/* other  includes */

/* these are the definitions for the various messages that can be used by the
 * different tasks 
 */

typedef enum E_MESSAGE_TYPE
{
   E_NO_MSG                                           = 0x0000,
   /* USER INPUT MESSAGES */
   UI_MSG1                                            = 0x0001,      /* UIT */
                     /**
                       *
                       *
                       */
   UI_LAST_MSG                                        = 0x3fff,
   /* GRAPHICS TASK MESSAGES */
   GT_MSG1                                            = 0x4000,      /* GT  */
   GT_MSG_PERFORM_DRAW                                = 0x4001,      /* draw all graphics */
   GT_MSG_SET_VIEW_RECT                               = 0x4100,      /* sets the view rect location */
                           /**
                             *
                             *
                             */
   GT_LAST_MSG                                        = 0x7fff,
   /* ENGINE TASK MESSAGES */
   ET_MSG1                                            = 0x8000,      /* ET  */
   ET_MSG_UPDATE_ENGINE                               = 0x8001,
                                 /**
                                   *
                                   *
                                   */
   ET_LAST_MSG                                        = 0xbfff,
   /* SOUND TASK MESSAGES */
   ST_MSG1                                            = 0xc000,      /* ST  */
                                       /**
                                         *
                                         *
                                         */

   ST_LAST_MSG                                        = 0xffff,
   E_LAST_MESSAGE                                     = 0xffff
}e_message_type;

#endif /* E_MSGS_H */