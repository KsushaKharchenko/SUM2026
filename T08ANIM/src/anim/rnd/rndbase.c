/* FILE NAME: main.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include "def.h"

#include "anim/rnd/rnd.h"

VOID KH6_RndInit( HWND hWnd )
{
  HDC hDC;
  KH6_hRndWnd = hWnd;

  hDC = GetDC(hWnd);
  KH6_hRndBmFrame = CreateCompatibleBitmap(hDC, KH6_RndFrameW, KH6_RndFrameH);
  KH6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(KH6_hRndWnd, hDC);

  KH6_hRndBmFrame = NULL;
  KH6_RndResize(200, 200);
  KH6_RndCamSet(VecSet1(6), VecSet1(4), VecSet(0, 1, 0));
}

VOID KH6_RndClose( VOID )
{
  if (KH6_hRndBmFrame != NULL)
    DeleteObject(KH6_hRndBmFrame);
  DeleteDC(KH6_hRndDCFrame);
}

VOID KH6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(KH6_hRndWnd);
 
  if (KH6_hRndBmFrame != NULL)
    DeleteObject(KH6_hRndBmFrame);
  KH6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(KH6_hRndWnd, hDC);
 
  SelectObject(KH6_hRndDCFrame, KH6_hRndBmFrame);
 
  /* сохраняем размеры */
  KH6_RndFrameW = W;
  KH6_RndFrameH = H;
 
  /* пересчитываем проекию */
  KH6_RndProjSet();
}

VOID KH6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, KH6_RndFrameW, KH6_RndFrameH, KH6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID KH6_RndStart( VOID )
{
  SelectObject(KH6_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(KH6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(KH6_hRndDCFrame, RGB(0, 0, 100));
  Rectangle(KH6_hRndDCFrame, 0, 0, KH6_RndFrameW, KH6_RndFrameH);
  SelectObject(KH6_hRndDCFrame, GetStockObject(NULL_BRUSH));
  SelectObject(KH6_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(KH6_hRndDCFrame, RGB(255, 0, 255));
}
VOID KH6_RndEnd( VOID )
{
}
 
 VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  KH6_RndMatrView = MatrView(Loc, At, Up);
  KH6_RndMatrVP = MatrMulMatr(KH6_RndMatrView, KH6_RndMatrProj);

  KH6_RndCamRight = VecSet(KH6_RndMatrView.A[0][0],
                           KH6_RndMatrView.A[1][0],
                           KH6_RndMatrView.A[2][0]);
  KH6_RndCamUp = VecSet(KH6_RndMatrView.A[0][1],
                        KH6_RndMatrView.A[1][1],
                        KH6_RndMatrView.A[2][1]);
  KH6_RndCamDir = VecSet(-KH6_RndMatrView.A[0][2],
                         -KH6_RndMatrView.A[1][2],
                         -KH6_RndMatrView.A[2][2]);
  KH6_RndCamLoc = Loc;
  KH6_RndCamAt = At;
 }

VOID KH6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = KH6_RndProjSize;
  /* Correct aspect ratio */
  if (KH6_RndFrameW > KH6_RndFrameH)
    rx *= (DBL)KH6_RndFrameW / KH6_RndFrameH;
  else
    ry *= (DBL)KH6_RndFrameH / KH6_RndFrameW;
  KH6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      KH6_RndProjDist, KH6_RndProjFarClip);
  KH6_RndMatrVP = MatrMulMatr(KH6_RndMatrView, KH6_RndMatrProj);
}

 
 