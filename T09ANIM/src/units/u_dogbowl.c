/* FILE NAME  : u_dogbowl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_BOWL
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS DogBowl;
} kh6UNIT_BOWL;
 
static VOID KH6_UnitInit( kh6UNIT_BOWL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->DogBowl, "bin/models/dog_bowl/bowl.g3dm");
}
 
static VOID KH6_UnitClose( kh6UNIT_BOWL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->DogBowl);
}
 
static VOID KH6_UnitResponse( kh6UNIT_BOWL *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_BOWL *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->DogBowl, MatrMulMatr(MatrScale(VecSet1(0.4)), MatrTranslate(VecSet(-0.2, -6.5, 2))));
}
 
kh6UNIT * KH6_AnimUnitCreateBOWL( VOID )
{
  kh6UNIT_BOWL *Uni;
 
  if ((Uni = (kh6UNIT_BOWL *)KH6_AnimUnitCreate(sizeof(kh6UNIT_BOWL))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}