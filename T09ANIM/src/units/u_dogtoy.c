/* FILE NAME  : u_dogbowl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_TOY
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS DogToy;
} kh6UNIT_TOY;
 
static VOID KH6_UnitInit( kh6UNIT_TOY *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->DogToy, "bin/models/toy.g3dm");
}
 
static VOID KH6_UnitClose( kh6UNIT_TOY *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->DogToy);
}
 
static VOID KH6_UnitResponse( kh6UNIT_TOY *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_TOY *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->DogToy, MatrMulMatr(MatrScale(VecSet1(0.07)), MatrTranslate(VecSet(1, -6.3, 0))));
}
 
kh6UNIT * KH6_AnimUnitCreateTOY( VOID )
{
  kh6UNIT_TOY *Uni;
 
  if ((Uni = (kh6UNIT_TOY *)KH6_AnimUnitCreate(sizeof(kh6UNIT_TOY))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}