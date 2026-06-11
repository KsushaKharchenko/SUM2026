/* FILE NAME: anim.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#include "anim.h"


kh6ANIM kh6_Anim;

VOID KH6_AnimInit( HWND hWnd )
{
  memset(&kh6_Anim, 0, sizeof(kh6ANIM));

  kh6_Anim.hWnd = hWnd;
  KH6_RndInit(hWnd);
  kh6_Anim.hDC = KH6_hRndDCFrame;
  kh6_Anim.W = KH6_RndFrameW;
  kh6_Anim.H = KH6_RndFrameH;
  //KH6_TimerInit();
}

VOID KH6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < kh6_Anim.NumOfUnits; i++)
  {
    kh6_Anim.Units[i]->Close(kh6_Anim.Units[i], &kh6_Anim);
    free(kh6_Anim.Units[i]);
  }
  KH6_RndClose();
  memset(&kh6_Anim, 0, sizeof(kh6ANIM));
}

VOID KH6_AnimResize( INT W, INT H )
{
  KH6_RndResize(W, H);
  kh6_Anim.W = W;
  kh6_Anim.H = H;
  KH6_AnimRender();
}

VOID KH6_AnimCopyFrame( HDC hDC )
{
  KH6_RndCopyFrame(hDC);
}

VOID KH6_AnimRender( VOID )
{
  INT i;

  //KH6_TimerResponse();

  for (i = 0; i < kh6_Anim.NumOfUnits; i++)
    kh6_Anim.Units[i]->Response(kh6_Anim.Units[i], &kh6_Anim);
  
  KH6_RndStart();

  for (i = 0; i < kh6_Anim.NumOfUnits; i++)
    kh6_Anim.Units[i]->Render(kh6_Anim.Units[i], &kh6_Anim);

  KH6_RndEnd();
}
VOID KH6_AnimAddUnit( kh6UNIT *Uni )
{
  if (kh6_Anim.NumOfUnits < kh6_MAX_UNITS)
    kh6_Anim.Units[kh6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &kh6_Anim);
}

VOID KH6_AnimFlipFullScreen( VOID )
{
}

VOID KH6_AnimExit( VOID )
{
}
