/* FILE NAME: rnddata.c
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */
#include "anim/rnd/rnd.h"

HWND KH6_hRndWnd;
HDC KH6_hRndDC;
HGLRC KH6_hRndGLRC;
INT KH6_RndFrameW, KH6_RndFrameH;

DBL
  KH6_RndProjSize = 0.1,     /* Project plane fit square */
  KH6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  KH6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  KH6_RndMatrView, /* View coordinate system matrix */
  KH6_RndMatrProj, /* Projection coordinate system matrix */
  KH6_RndMatrVP;   /* Stored (View * Proj) matrix */
 