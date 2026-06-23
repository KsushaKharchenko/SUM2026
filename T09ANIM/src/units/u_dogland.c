/* FILE NAME  : u_land.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_LAND
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS Land;
} kh6UNIT_LAND;
 
static VOID KH6_UnitInit( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->Land, "bin/models/land2.g3dm");
}
 
static VOID KH6_UnitClose( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{ 
  KH6_RndPrimsFree(&Uni->Land); 
}
 
static VOID KH6_UnitResponse( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->Land, MatrMulMatr(MatrRotateY(300), MatrTranslate(VecSet(-40, -7.15, -280))));
}
 
kh6UNIT * KH6_AnimUnitCreateLAND( VOID )
{
  kh6UNIT_LAND *Uni;
 
  if ((Uni = (kh6UNIT_LAND *)KH6_AnimUnitCreate(sizeof(kh6UNIT_LAND))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}