

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

} /* End of 'KH6_UnitRender' function */ 