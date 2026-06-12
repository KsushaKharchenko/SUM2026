/* FILE NAME: timer.c
 * PURPOSE: Implementation of timer functions and global variables
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include <windows.h>
#include <time.h>

#include "timer.h"

typedef unsigned long long UINT64;

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
{
  LARGE_INTEGER t;
  LARGE_INTEGER frequency;

  QueryPerformanceFrequency(&frequency);
  TimePerSec = frequency.QuadPart;

  QueryPerformanceCounter(&t);

  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  PauseTime = 0;
  FrameCount = 0;
  GLB_IsPause = FALSE;
  GLB_Time = GLB_DeltaTime = 0;
  GLB_FPS = 30;
}

VOID GLB_TimerResponse(VOID)  /* Исправлено имя функции */
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    GLB_DeltaTime = GlobalDeltaTime;
  }
  else
  {
    GLB_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }

  /* FPS */
  FrameCount++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    GLB_FPS = FrameCount * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCount = 0;
  }
  OldTime = t.QuadPart;
}
