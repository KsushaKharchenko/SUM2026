/* FILE NAME  : u_g2dm.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_DOG
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS Dog;
  kh6PRIMS Land;
  kh6PRIMS DogToy;
  kh6PRIMS DogHouse;
  kh6PRIMS DogBowl;

  VEC DogPos;

  FLT Speed,
      DogAngle;

  BOOL IsMoving;
} kh6UNIT_DOG;
 
static VOID KH6_UnitInit( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  //VEC B;
  //MATR m;
  
  KH6_RndPrimsLoad(&Uni->Dog, "bin/models/dog.g3dm");
  KH6_RndPrimsLoad(&Uni->Land, "bin/models/land2.g3dm");
  /*B = VecSubVec(Uni->Land.MaxBB, Uni->Land.MinBB);
  m = MatrMulMatr(MatrTranslate(VecAddVec(VecNeg(Uni->Land.MinBB), VecSet(-B.X / 2, 0, -B.Z / 2))), MatrScale(VecSet1(1 / B.Y)));
  Uni->Land.Trans = m;*/
  Uni->DogPos = VecSet(10, 10, 10);
  Uni->DogAngle = 0;
  Uni->IsMoving = FALSE;
}
 
static VOID KH6_UnitClose( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->Dog); 
  KH6_RndPrimsFree(&Uni->Land); 
  //KH6_RndPrimsFree(&Uni->DogToy); 
  //KH6_RndPrimsFree(&Uni->DogHouse);
  //KH6_RndPrimsFree(&Uni->DogBowl);
}
 
static VOID KH6_UnitResponse( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  VEC NewPos;

  if (Ani->KeysClick['W'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(0, 0, -1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 0;
    Uni->IsMoving = TRUE;

  }
  if (Ani->KeysClick['S'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(0, 0, 1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 180;
    Uni->IsMoving = TRUE;
  }
  if (Ani->KeysClick['A'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(-1, 0, 0), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = -90;
    Uni->IsMoving = TRUE;
  }
  if (Ani->KeysClick['D'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(1, 0, 0), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 90;
    Uni->IsMoving = TRUE;
  }

  if (Uni->IsMoving)
  {
    Uni->DogPos = NewPos;
    Uni->IsMoving = TRUE;
  }
  else
    Uni->IsMoving = FALSE;
} 
 
static VOID KH6_UnitRender( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->Dog, MatrMulMatr(MatrRotateY(90), MatrTranslate(VecSet(0, 5, 0))));
  KH6_RndPrimsDraw(&Uni->Land, MatrIdentity());
  //KH6_RndPrimsDraw(&Uni->DogHouse, MatrIdentity());
  //KH6_RndPrimsDraw(&Uni->DogToy, MatrIdentity());
  //KH6_RndPrimsDraw(&Uni->DogBowl, MatrIdentity());
}
 
kh6UNIT * KH6_AnimUnitCreateDOG( VOID )
{
  kh6UNIT_DOG *Uni;
 
  if ((Uni = (kh6UNIT_DOG *)KH6_AnimUnitCreate(sizeof(kh6UNIT_DOG))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}