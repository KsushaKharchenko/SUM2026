/* FILE NAME: anim.c
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#include "anim.h"


kh6ANIM KH6_Anim;

VOID KH6_AnimInit( HWND hWnd )
{
  memset(&KH6_Anim, 0, sizeof(kh6ANIM));

  KH6_Anim.hWnd = hWnd;
  KH6_RndInit(hWnd);
  KH6_Anim.W = KH6_RndFrameW;
  KH6_Anim.H = KH6_RndFrameH;
  KH6_TimerInit();
  KH6_AnimInputInit();
}

VOID KH6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < KH6_Anim.NumOfUnits; i++)
  {
    KH6_Anim.Units[i]->Close(KH6_Anim.Units[i], &KH6_Anim);
    free(KH6_Anim.Units[i]);
  }
  KH6_RndClose();
  memset(&KH6_Anim, 0, sizeof(kh6ANIM));
}

VOID KH6_AnimResize( INT W, INT H )
{
  KH6_RndResize(W, H);
  KH6_Anim.W = W;
  KH6_Anim.H = H;
  KH6_AnimRender();
}

VOID KH6_AnimCopyFrame( VOID )
{
  KH6_RndCopyFrame();
}

VOID KH6_AnimRender( VOID )
{
  INT i;

  KH6_TimerResponse();
  if (KH6_Anim.IsActive)
    KH6_AnimInputResponse();

  for (i = 0; i < KH6_Anim.NumOfUnits; i++)
    KH6_Anim.Units[i]->Response(KH6_Anim.Units[i], &KH6_Anim);
  
  KH6_RndStart();

  for (i = 0; i < KH6_Anim.NumOfUnits; i++)
    KH6_Anim.Units[i]->Render(KH6_Anim.Units[i], &KH6_Anim);

  KH6_RndEnd();
}
VOID KH6_AnimAddUnit( kh6UNIT *Uni )
{
  if (KH6_Anim.NumOfUnits < kh6_MAX_UNITS)
    KH6_Anim.Units[KH6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &KH6_Anim);
}

VOID KH6_AnimFlipFullScreen( VOID )
{
}

VOID KH6_AnimExit( VOID )
{
  PostMessage(KH6_Anim.hWnd, WM_CLOSE, 0, 0);
}
