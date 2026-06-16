/* FILE NAME: timer.c
 * PURPOSE: Implementation of timer functions and global variables
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include <windows.h>
#include <time.h>

#include "timer.h"

typedef unsigned long long UINT64;

<<<<<<< HEAD
static UINT64 
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCount; /* Frames counter */
  
VOID GlobalTimerInit( VOID )
=======
/* Definitions of global variables */
DOUBLE GlobalTime = 0.0,
       GlobalDeltaTime = 0.0,
       GLB_Time = 0.0,
       GLB_DeltaTime = 0.0,
       GLB_FPS = 30.0;
BOOL GLB_IsPause = FALSE;

static UINT64
    StartTime = 0,
    OldTime = 0,
    OldTimeFPS = 0,
    PauseTime = 0,
    TimePerSec = 0,  
    FrameCount = 0;

VOID GLB_TimerInit(VOID)
>>>>>>> 0a8637611e3f657fe14655ef26ad92ead9acf33c
{
  LARGE_INTEGER t;
  LARGE_INTEGER frequency;

  QueryPerformanceFrequency(&frequency);
  TimePerSec = frequency.QuadPart;

  QueryPerformanceCounter(&t);

  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  PauseTime = 0;
  FrameCount = 0;
  GlobalIsPause = FALSE;
  GlobalTime = GlobalDeltaTime = 0;
  GlobalFPS = 30;
}

VOID GLB_TimerResponse(VOID)  /* Исправлено имя функции */
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (!GlobalIsPause)
  {
    GlobalTime = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    GlobalDeltaTime = GlobalDeltaTime;
  }
  else
  {
    GlobalDeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }

  /* FPS */
  FrameCount++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    GlobalFPS = FrameCount * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCount = 0;
  }
  OldTime = t.QuadPart;
}
