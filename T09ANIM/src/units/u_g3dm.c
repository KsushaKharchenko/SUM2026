/* FILE NAME  : u_g3dm.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_G3DM
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS Model;
} kh6UNIT_G3DM;
 
static VOID KH6_UnitInit( kh6UNIT_G3DM *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->Model, "bin/models/house.g3dm");
}
 
static VOID KH6_UnitClose( kh6UNIT_G3DM *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->Model); 
}
 
static VOID KH6_UnitResponse( kh6UNIT_G3DM *Uni, kh6ANIM *Ani )
{
} 
 
static VOID KH6_UnitRender( kh6UNIT_G3DM *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->Model, MatrIdentity());
}
 
kh6UNIT * KH6_AnimUnitCreateG3DM( VOID )
{
  kh6UNIT_G3DM *Uni;
 
  if ((Uni = (kh6UNIT_G3DM *)KH6_AnimUnitCreate(sizeof(kh6UNIT_G3DM))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}