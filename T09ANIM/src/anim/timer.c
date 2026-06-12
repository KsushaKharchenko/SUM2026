/* FILE NAME: timer.h
 * PURPOSE: 
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
  kh6_Anim.IsPause = FALSE;
  kh6_Anim.FPS = 30.0;
  PauseTime = 0;
}
 
VOID KH6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  kh6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  kh6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (kh6_Anim.IsPause)
  {
    PauseTime += t.QuadPart - OldTime;
    kh6_Anim.DeltaTime = 0;
  }
  else
  {
    kh6_Anim.DeltaTime = kh6_Anim.GlobalDeltaTime;
    kh6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
 
  /* FPS */
  FrameCount++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    kh6_Anim.FPS = FrameCount * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCount = 0;
  }
  OldTime = t.QuadPart;
}