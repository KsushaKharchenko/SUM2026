/* FILE NAME  : u_dog.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */
 
#include "units.h"
 
typedef struct tagkh6UNIT_DOG
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIMS Dog;
  VEC DogPos;

  FLT Speed,
      WalkTime,
      DogAngle,
      PosAngle;

  BOOL IsMoving;
} kh6UNIT_DOG;
 
static VOID KH6_UnitInit( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsLoad(&Uni->Dog, "bin/models/dog/dog.g3dm");
  Uni->DogPos = VecSet(0, -5.4, 0);
  Uni->DogAngle = 40;
  Uni->Speed = 2.0;
  Uni->WalkTime = 0;
  Uni->PosAngle = 0;
  Uni->IsMoving = FALSE;
}
 
static VOID KH6_UnitClose( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimsFree(&Uni->Dog); 
}
 
static VOID KH6_UnitResponse( kh6UNIT_DOG *Uni, kh6ANIM *Ani )
{
  VEC NewPos;
  BOOL Moving = FALSE;

  if (Ani->Keys['W'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(1, 0, 1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 40;
    Moving = TRUE;
  }
  if (Ani->Keys['S'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(-1, 0, -1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 220;
    Moving = TRUE;
  }
  if (Ani->Keys['A'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(-1, 0, 1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = -50;
    Moving = TRUE;
  }
  if (Ani->Keys['D'])
  {
    NewPos = VecAddVec(Uni->DogPos, VecMulNum(VecSet(1, 0, -1), Ani->DeltaTime * Uni->Speed));
    Uni->DogAngle = 130;
    Moving = TRUE;
  }

  if (Moving)
  {
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
  KH6_RndPrimsDraw(&Uni->Dog, MatrMulMatr(MatrRotateY(Uni->DogAngle), MatrTranslate(Uni->DogPos)));
}
 
kh6UNIT * KH6_AnimUnitCreateDOG( VOID )
{
  kh6UNIT *Uni;
 
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_DOG))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return (kh6UNIT *)Uni;
}