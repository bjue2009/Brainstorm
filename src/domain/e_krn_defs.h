#ifndef E_KRN_DEFS_H
#define E_KRN_DEFS_H
/******************************************************************************
 * Module - EXEC
 * Description - This file contains the declarations for the different threads
 *****************************************************************************/
/* domain includes */

/* global includes */
/* other  includes */

/* task definitions */
typedef enum E_TASK_DEF_TYPE
{
   E_USER_INPUT_TASK,      /* UIT */
   E_GRAPHICS_TASK,        /* GT  */
   E_ENGINE_TASK,          /* ET  */
   E_SOUND_TASK,           /* ST  */
   E_LAST_TASK
}e_task_def_type;





#endif /* E_KRN_DEFS_H */