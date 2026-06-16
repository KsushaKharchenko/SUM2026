/* FILE NAME: timer.c
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#include "anim.h"

static UINT64 
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCount; /* Frames counter */


VOID KH6_TimerInit( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;

  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCount = 0;
  KH6_Anim.IsPause = FALSE;
  KH6_Anim.FPS = 30.0;
  PauseTime = 0;
}
 
VOID KH6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  KH6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  KH6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (KH6_Anim.IsPause)
  {
    KH6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    KH6_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    KH6_Anim.DeltaTime = KH6_Anim.GlobalDeltaTime;
  }
 
  /* FPS */
  FrameCount++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    KH6_Anim.FPS = FrameCount * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCount = 0;
  }
  OldTime = t.QuadPart;
}