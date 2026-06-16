/* FILE NAME: timer.h
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#ifndef __timer_h_
#define __timer_h_

extern DOUBLE
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    GlobalTime, GlobalDeltaTime,             /* Time with pause and interframe interval */
    GlobalFPS;                         /* Frames per second value */
extern BOOL GlobalIsPause;                     /* Pause flag */

VOID GlobalTimerInit( VOID );

VOID GlobalTimerResponse( VOID );

#endif /* __timer_h_ */