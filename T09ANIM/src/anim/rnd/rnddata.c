/* FILE NAME  : rnddata.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 09.06.2026
 */
 
#include "rnd.h"
HWND KH6_hRndWnd;        /* Work window handle */
HDC KH6_hRndDC;     /* Work window memory device context  */
INT KH6_RndFrameW, KH6_RndFrameH; /* Work window size */
HGLRC KH6_hRndGLRC; /* OpenGL rendering context */
INT KH6_MouseWheel;
 
DBL
  KH6_RndProjSize = 0.1,     /* Project plane fit square */
  KH6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  KH6_RndProjFarClip = 3000;  /* Distance to project far clip plane (far) */
 
MATR
  KH6_RndMatrView, /* View coordinate system matrix */
  KH6_RndMatrProj, /* Projection coordinate system matrix */
  KH6_RndMatrVP;   /* Stored (View * Proj) matrix */
 
VEC
  KH6_RndCamLoc, KH6_RndCamAt, KH6_RndCamDir, 
  KH6_RndCamRight, KH6_RndCamUp;
 
INT KH6_RndShdAddonI[8]; 
FLT KH6_RndShdAddonF[8];
VEC KH6_RndShdAddonV[8];