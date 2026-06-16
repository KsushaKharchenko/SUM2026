/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 12.06.2026
 */

#include <stdio.h>

#include "units.h"

typedef struct tagkh6UNIT_CONTROL
{
  KH6_UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;

}kh6UNIT_CONTROL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitInit( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);
  Uni->Speed = 1;
} /* End of 'KH6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitClose( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
} /* End of 'KH6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitResponse( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  VEC d;
    /*if (Ani->Keys[VK_CONTROL] && Ani->KeysClick['F'])
  KH6_AnimFlipFullScreen();*/
  
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  if (Ani->KeysClick[VK_ESCAPE])
    KH6_AnimExit();
  
  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));
  Uni->CamLoc =VecAddVec(Uni->CamLoc,
    VecMulNum(d, Ani->GlobalDeltaTime * Uni->Speed *
    (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));

  KH6_RndCamSet(Uni->CamLoc, Uni->CamAt, VecSet(0, 1, 0));
} /* End of 'KH6_UnitResponse' function */
 /* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitRender( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  CHAR Buf[102];


  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  TextOut(Ani->hDC, 50, 50, Buf, sprintf(Buf,  "FPS: %.3f", Ani->FPS));
} /* End of 'KH6_UnitRender' function */ 

/* Unit control function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateControl( VOID )
{
  kh6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_CONTROL))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
 
  return Uni;
} /* End of 'KH6_UnitCreateControl' function */