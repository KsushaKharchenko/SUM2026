/* FILE NAME  : u_g3dm.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_HOUSE
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS Model;
} kh6UNIT_HOUSE;
 
static VOID KH6_UnitInit( kh6UNIT_HOUSE *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->Model, "bin/models/house.g3dm");
}
 
static VOID KH6_UnitClose( kh6UNIT_HOUSE *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->Model); 
}
 
static VOID KH6_UnitResponse( kh6UNIT_HOUSE *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_HOUSE *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->Model, MatrMulMatr3(MatrRotateY(45), MatrScale(VecSet1(0.1)), MatrTranslate(VecSet(-7, 0.7, -5))));
}
 

kh6UNIT * KH6_AnimUnitCreateHOUSE( VOID )
{
  kh6UNIT_HOUSE *Uni;
 
  if ((Uni = (kh6UNIT_HOUSE *)KH6_AnimUnitCreate(sizeof(kh6UNIT_HOUSE))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}