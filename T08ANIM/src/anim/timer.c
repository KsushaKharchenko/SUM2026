/* FILE NAME: timer.h
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */


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
  KH6_FPS = 30.0;
  PauseTime = 0;
}
 
VOID KH6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  Kh6_Anim.GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  Kh6_Anim.GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (KH6_Anim.IsPause)
  {
    GLB_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    KH6_Anim.DeltaTime = 0;
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