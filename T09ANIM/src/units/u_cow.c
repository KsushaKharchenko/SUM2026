/* FILE NAME  : u_cow.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 15.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_COW
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIM Cow;
} kh6UNIT_LAND;
 
static VOID KH6_UnitInit( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");
}
 
static VOID KH6_UnitClose( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimFree(&Uni->Cow); 
}
 
static VOID KH6_UnitRender( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  INT s = 0, i, j;
 
  for (i = -s; i <= s; i++)  
    for (j = -s; j <= s; j++)
      KH6_RndPrimDraw(&Uni->Cow, 
        MatrMulMatr5(MatrScale(VecSet1(0.03)),
        MatrRotateY(Ani->Time * 180),
        MatrRotateX(sin(Ani->Time) * 30), 
        MatrRotateZ(sin(Ani->Time) * 30),
        MatrTranslate(VecSet(1, j, i))));
}
 
kh6UNIT * KH6_AnimUnitCreateCow( VOID )
{
  kh6UNIT *Uni;
 
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Render = (VOID *)KH6_UnitRender;
  return Uni;
}