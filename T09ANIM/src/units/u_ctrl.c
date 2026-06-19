/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 12.06.2026
 */

#include <stdio.h>

#include "units.h"

#include "def.h"

typedef struct tagkh6UNIT_CONTROL
{
  KH6_UNIT_BASE_FIELDS;
}kh6UNIT_CONTROL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitInit( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  KH6_RndCamLoc = VecSet(8, 8, 8);
  KH6_RndCamAt = VecSet(0, 0, 0);
} /* End of 'KH6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitClose( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
} /* End of 'KH6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitResponse( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  FLT Dist;
  DBL CosT, SinT, CosP, SinP, plen, Azimuth, Elevator;
  FLT sx, sy, Wp, Hp;
  VEC NewLoc, dv;

    /*if (Ani->Keys[VK_CONTROL] && Ani->KeysClick['F'])
  KH6_AnimFlipFullScreen();*/
  
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  if (Ani->KeysClick[VK_ESCAPE])
    KH6_AnimExit();

  if (Ani->KeysClick[VK_F8])
  {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD NumCharsWritten;
    COORD Pos = {0};
 
    GetConsoleScreenBufferInfo(hCon, &info);
    FillConsoleOutputCharacter(hCon, ' ',
      (UINT)(info.dwSize.X * info.dwSize.Y), Pos, &NumCharsWritten);  
    FillConsoleOutputAttribute(hCon, 0x0F,
      (UINT)(info.dwSize.X * info.dwSize.Y), Pos, &NumCharsWritten);  
    SetConsoleCursorPosition(hCon, info.dwCursorPosition);
    SetConsoleCursorPosition(hCon, Pos);
  }


  Dist = VecLen(VecSubVec(KH6_RndCamAt, KH6_RndCamLoc));
  CosT = (KH6_RndCamLoc.Y - KH6_RndCamAt.Y) / Dist;
  SinT = sqrt(1 - CosT * CosT);
  
  plen = Dist * SinT;
  CosP = (KH6_RndCamLoc.Z - KH6_RndCamAt.Z) / plen;
  SinP = (KH6_RndCamLoc.X - KH6_RndCamAt.X) / plen;

  Azimuth = D2R(atan2(SinP, CosP));
  Elevator = D2R(atan2(SinT, CosT));

  Azimuth +=
            2 * -30 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 
            Ani->GlobalDeltaTime * 
            2 * 30 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]);
  Elevator +=
            2 * -30 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
            Ani->GlobalDeltaTime * 
            2 * 30 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
  Dist += Ani->GlobalDeltaTime * 
    (300 * Ani->Mdz +
     8 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));

  //NewLoc = PointTransform(VecSet(0, Dist, 0), MatrMulMatr(MatrRotateX(Elevator), MatrRotateY(Azimuth))); 
  NewLoc = VecAddVec(PointTransform(VecSet(0, Dist, 0),
                     MatrMulMatr(MatrRotateX(Elevator), MatrRotateY(Azimuth))),
                     KH6_RndCamAt);

  Wp = KH6_RndProjSize;
  Hp = KH6_RndProjSize;

  if (Ani->W > Ani-> H)
    Wp *= (FLT)Ani->W / Ani->H;
  else
    Hp *= (FLT)Ani->H / Ani->W;

  sx = Ani->Keys[VK_RBUTTON] * -Ani->Mdx * Wp / Ani->W * Dist / KH6_RndProjDist;
  sy = Ani->Keys[VK_RBUTTON] * Ani->Mdy * Hp / Ani->H * Dist / KH6_RndProjDist;
  dv =  VecAddVec(VecMulNum(KH6_RndCamRight, sx),
                  VecMulNum(KH6_RndCamUp, sy));
  KH6_RndCamAt = VecAddVec(KH6_RndCamAt, dv);
  KH6_RndCamLoc = VecAddVec(KH6_RndCamLoc, dv);
 
  KH6_RndCamSet(PointTransform(VecSet(0, Dist, 0), 
                               MatrMulMatr3(MatrRotateX(Elevator),
                                            MatrRotateY(Azimuth),
                                            MatrTranslate(KH6_RndCamAt))), 
                KH6_RndCamAt,
                VecSet(0, 1, 0));
} /* End of 'KH6_UnitResponse' function */
 /* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_CONTROL *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitRender( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  CHAR Buf[102];


  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  TextOut(Ani->hDC, 50, 50, Buf, sprintf(Buf,  "FPS: %.3f", Ani->FPS));
} /* End of 'KH6_UnitRender' function */ 

/* Unit control function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateControl( VOID )
{
  kh6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_CONTROL))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
 
  return Uni;
} /* End of 'KH6_UnitCreateControl' function */