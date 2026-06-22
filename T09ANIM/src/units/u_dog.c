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
      WalkTime,
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
  Uni->WalkTime = 0;
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
  BOOL Moving = FALSE;

  if (Ani->Keys['W'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(0, 0, -1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 0;
    Moving = TRUE;

  }
  if (Ani->Keys['S'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(0, 0, 1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 180;
    Moving = TRUE;
  }
  if (Ani->Keys['A'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(-1, 0, 0), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = -90;
    Moving = TRUE;
  }
  if (Ani->Keys['D'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(1, 0, 0), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 90;
    Moving = TRUE;
  }

  if (Moving)
  {
    NewPos.X = max(-3.0, min(3.0, NewPos.X));
    NewPos.Z = max(-3.0, min(3.0, NewPos.Z));
    Uni->DogPos = NewPos;
    Uni->IsMoving = TRUE;
    Uni->WalkTime += Ani->DeltaTime * 3;
  }
  else
  {
    Uni->IsMoving = FALSE;
    Uni->WalkTime = 0;
  }
} 
 
static VOID KH6_UnitRender( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsDraw(&Uni->Dog, MatrMulMatr(MatrRotateY(40 + Uni->DogAngle), 
    MatrTranslate(VecSet(0, 0, 0))));
  KH6_RndPrimsDraw(&Uni->Land, MatrMulMatr4(MatrRotateZ(-2), MatrRotateY(300), 
                               MatrRotateX(-3), MatrTranslate(VecSet(-40, -7.15, -280))));
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