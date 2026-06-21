/* FILE NAME  : u_ball.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_BALL
{
  KH6_UNIT_BASE_FIELDS;
  VEC Pos;
  kh6PRIM Ball;
} kh6UNIT_BALL;
 
static VOID KH6_UnitInit( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimCreateSphere(&Uni->Ball, 0.1, 30, 12);
  Uni->Pos = VecSet(Rnd1() * 4, 1, Rnd1() * 4);
}
 
static VOID KH6_UnitClose( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimFree(&Uni->Ball); 
}
 
static VOID KH6_UnitResponse( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_BALL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimDraw(&Uni->Ball, MatrTranslate(VecAddVec(Uni->Pos, VecSet(0, fabs(sin(5 * Ani->Time)), 0))));
}
 
kh6UNIT * KH6_AnimUnitCreateBall( VOID )
{
  kh6UNIT_BALL *Uni;
 
  if ((Uni = (kh6UNIT_BALL *)KH6_AnimUnitCreate(sizeof(kh6UNIT_BALL))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}