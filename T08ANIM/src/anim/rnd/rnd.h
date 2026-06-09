/* FILE NAME: rnd.h
 * PURPOSE:
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include "def.h"

extern HWND KH6_hRndWnd;
extern HDC KH6_hRndDCFrame;
extern HBITMAP KH6_hRndBmFrame;
extern INT KH6_RndFrameW, KH6_RndFrameH;

extern DBL
  KH6_RndProjSize,     /* Project plane fit square */
  KH6_RndProjDist,     /* Distance to project plane from viewer (near) */
  KH6_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  KH6_RndMatrView, /* View coordinate system matrix */
  KH6_RndMatrProj, /* Projection coordinate system matrix */
  KH6_RndMatrVP;   /* Stored (View * Proj) matrix */

VOID KH6_RndProjSet( VOID );
VOID KH6_RndResize( INT W, INT H );
VOID KH6_RndInit( HWND hWnd );
VOID KH6_RndClose( VOID );
VOID KH6_RndCopyFrame( HDC hDC );
VOID KH6_RndStart( VOID );
VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up );

