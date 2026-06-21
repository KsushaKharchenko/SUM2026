/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 22.06.2026
 */
 
#include "stdio.h"
#include "units.h"
 
typedef struct tagkh6UNIT_CONTROL
{
  KH6_UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;
} kh6UNIT_CONTROL;
 
static VOID KH6_UnitInit( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);
  Uni->Speed = 1;
}
 
static VOID KH6_UnitClose( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
}
 
static VOID KH6_UnitResponse( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  FLT Wp, Hp, sx, sy;
  DBL CosT, SinT, CosP, SinP, 
      Dist, plen, Azimuth, Elevator;
  VEC NewLoc, dv;

  /* Clear console on F8 */
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

  /* Pause toggle */
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  /* Exit */
  if (Ani->KeysClick[VK_ESCAPE])
    KH6_AnimExit();

  Dist = VecLen(VecSubVec(KH6_RndCamAt, KH6_RndCamLoc));
  
  if (Dist < 0.001)
    Dist = 0.001;

  CosT = (KH6_RndCamLoc.Y - KH6_RndCamAt.Y) / Dist;
  
  if (CosT > 1.0)
    CosT = 1.0;
  else if (CosT < -1.0)
    CosT = -1.0;
    
  SinT = sqrt(1 - CosT * CosT);

  plen = Dist * SinT;
  if (plen < 0.001)
    plen = 0.001;
    
  CosP = (KH6_RndCamLoc.Z - KH6_RndCamAt.Z) / plen;
  SinP = (KH6_RndCamLoc.X - KH6_RndCamAt.X) / plen;

  Azimuth = R2D(atan2(SinP, CosP));
  Elevator = R2D(atan2(SinT, CosT)); 
  
  Azimuth += 
    Ani->GlobalDeltaTime * Uni->Speed * 47 * 
      (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]) +
    Ani->Keys[VK_LBUTTON] * 0.01 * -30 * Ani->Mdx;

  Elevator += 
    Ani->GlobalDeltaTime * Uni->Speed * 47 * 
      (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) +
    Ani->Keys[VK_LBUTTON] * 0.01 * -30 * Ani->Mdy;

  if (Elevator < 0.08)
    Elevator = 0.08;
  if (Elevator > 178.0)
    Elevator = 178.0;

  Dist += 
    Ani->Mdz * 0.01 +
    Ani->GlobalDeltaTime * 8 * 
      (1 + Ani->Keys[VK_SHIFT] * 30) *  
      (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]);
  
  if (Dist < 0.001)
    Dist = 0.001;

  Wp = KH6_RndProjSize;
  Hp = KH6_RndProjSize;
  
  if (Ani->W > Ani->H)
    Wp *= (FLT)Ani->W / Ani->H;
  else
    Hp *= (FLT)Ani->H / Ani->W;

  sx = Ani->Keys[VK_RBUTTON] * -Ani->Mdx * Wp / Ani->W * Dist / KH6_RndProjDist;
  sy = Ani->Keys[VK_RBUTTON] * Ani->Mdy * Hp / Ani->H * Dist / KH6_RndProjDist;

  dv = VecAddVec(VecMulNum(KH6_RndCamRight, sx),
                 VecMulNum(KH6_RndCamUp, sy));
  KH6_RndCamAt = VecAddVec(KH6_RndCamAt, dv);
  KH6_RndCamLoc = VecAddVec(KH6_RndCamLoc, dv);

  
  NewLoc = PointTransform(VecSet(0, Dist, 0),
                          MatrMulMatr(MatrRotateX(Elevator),
                                      MatrRotateY(Azimuth)));

  KH6_RndCamSet(
    PointTransform(VecSet(0, Dist, 0),
                   MatrMulMatr3(MatrRotateX(Elevator),
                                MatrRotateY(Azimuth),
                                MatrTranslate(KH6_RndCamAt))),
    KH6_RndCamAt,
    VecSet(0, 1, 0)
  );
}
 
static VOID KH6_UnitRender( kh6UNIT_CONTROL *Uni, kh6ANIM *Ani )
{
  /*
  CHAR Buf[102];
  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(255, 255, 0));
  TextOut(Ani->hDC, Ani->W - 200, 30, Buf, 
    sprintf(Buf, "FPS: %.3f  Dist: %.2f", Ani->FPS, 
      VecLen(VecSubVec(KH6_RndCamAt, KH6_RndCamLoc))));
  */
}
 
kh6UNIT * KH6_AnimUnitCreateControl( VOID )
{
  kh6UNIT *Uni;
 
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_CONTROL))) == NULL)
    return NULL;
 
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
  return Uni;
}