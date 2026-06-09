/* FILE NAME: main.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include "def.h"
#include "rnd.h"

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

VOID KH6_RndInit( HWND hWnd )
{
  HDC hDC;
  KH6_hRndWnd = hWnd;

  hDC = GetDC(hWnd);
  KH6_hRndBmFrame = CreateCompatibleBitmap(hDC, KH6_RndFrameW, KH6_RndFrameH);
  ReleaseDC(KH6_hRndWnd, hDC);

  KH6_hRndBmFrame = NULL;
  KH6_RndResize(50, 50);
}

VOID KH6_RndClose( VOID )
{
  if (KH6_hRndBmFrame != NULL)
    DeleteObject(KH6_hRndBmFrame);
  DeleteDC(KH6_hRndDCFrame);
}


VOID KH6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, KH6_RndFrameW, KH6_RndFrameH, KH6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID KH6_RndStart( VOID )
{
  SelectObject(KH6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(KH6_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCBrushColor(KH6_hRndDCFrame, RGB(0, 0, 0));
  SetDCPenColor(KH6_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(KH6_hRndDCFrame, 0, 0, KH6_RndFrameW, KH6_RndFrameH);
}
VOID KH6_RndEnd( VOID )
{
}
 
 
VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  KH6_RndMatrView = MatrView(Loc, At, Up);
  KH6_RndMatrVP = MatrMulMatr(KH6_RndMatrView, KH6_RndMatrProj);
}
 
/*VOID KH6_RndPrimDraw( KH6PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr(World, KH6_RndMatrVP);

    VEC p = VecMulMatr(Prim->V[i], wvp);
 
    pnts[i].x = (INT)((P.X + 1) * KH6_RndFrameW / 2);
    pnts[i].y = (INT)((-P.Y + 1) * KH6_RndFrameH / 2);
  . . .
}*/
 