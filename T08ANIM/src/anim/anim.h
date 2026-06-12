/* FILE NAME: anim.h
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#include "rnd/rnd.h"

#define kh6_MAX_UNITS 3000

typedef struct tagkh6UNIT kh6UNIT;
typedef struct tagkh6ANIM kh6ANIM;

#define KH6_UNIT_BASE_FIELDS \
  VOID (*Init)( kh6UNIT *Uni, kh6ANIM *Ani );      \
  VOID (*Close)( kh6UNIT *Uni, kh6ANIM *Ani );     \
  VOID (*Response)( kh6UNIT *Uni, kh6ANIM *Ani );  \
  VOID (*Render)( kh6UNIT *Uni, kh6ANIM *Ani )

struct tagkh6UNIT
{
  KH6_UNIT_BASE_FIELDS;
};

struct tagkh6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
 
 
  kh6UNIT * Units[kh6_MAX_UNITS];
  INT NumOfUnits;

   DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
};

extern kh6ANIM kh6_Anim;

VOID KH6_AnimInit( HWND hWnd );
VOID KH6_AnimClose( VOID );
VOID KH6_AnimResize( INT W, INT H );
VOID KH6_AnimCopyFrame( HDC hDC );
VOID KH6_AnimRender( VOID );
VOID KH6_AnimAddUnit( kh6UNIT *Uni );
VOID KH6_AnimFlipFullScreen( VOID );
VOID KH6_AnimExit( VOID );

kh6UNIT * KH6_AnimUnitCreate( INT Size );
//kh6UNIT * KH6_AnimUnitCreateBall( VOID );


  
