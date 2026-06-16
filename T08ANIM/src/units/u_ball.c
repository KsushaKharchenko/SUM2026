/* FILE NAME: u_ball.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#include "units.h"

typedef struct tagkh6UNIT_BALL
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIM Ball;               /*ball primitive*/
  VEC Pos;
  DBL Scale, Shift;
}kh6UNIT_BALL;

static VOID KH6_UnitInit( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimCreateSphere(&Uni->Ball, 0.5, 18, 15);
  Uni->Pos = VecSet(Rnd1()* 8, 1, Rnd1()* 8); 
  Uni->Scale = Rnd1() * 0.5 + 3;
  Uni->Shift = Rnd1() * 33 + 1;
} /* End of 'KH6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_BALL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitClose( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimFree(&Uni->Ball);
} /* End of 'KH6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_BALL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitResponse( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
} /* End of 'KH6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_BALL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitRender( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimDraw(&Uni->Ball, MatrTranslate(VecAddVec(Uni->Pos, VecSet(0, fabs(sin(Ani->Time + Uni->Shift * Uni->Scale)), 0))));
} /* End of 'KH6_UnitRender' function */

 
/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateBall( VOID )
{
  kh6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_BALL))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
 
  return Uni;
} /* End of 'KH6_AnimUnitCreate' function */
