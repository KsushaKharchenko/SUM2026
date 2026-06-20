/* FILE NAME: globe.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 06.06.2026
 */


#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "globe.h"
#include "timer.h"

#define GlobalMIN(A, B) ((A) < (B) ? (A) : (B))
#define GlobalMAX(A, B) ((A) > (B) ? (A) : (B))

static VEC Geom[GRID_H][GRID_W];
static VEC GeomN[GRID_H][GRID_W];
static INT GlobalWs, GlobalHs;
static DBL GlobalProjSize = 1, GlobalProjDist = 1, GlobalWp, GlobalHp;


COLORREF ColorTo255( VEC Color )
{
  INT
    R = (INT)(Color.X * 255),
    G = (INT)(Color.Y * 255),
    B = (INT)(Color.Z * 255);

  R = GlobalMIN(255, GlobalMAX(0, R));
  G = GlobalMIN(255, GlobalMAX(0, G));
  B = GlobalMIN(255, GlobalMAX(0, B));
  return RGB(R, G, B);
}

/*VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
}

VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X;
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  return NewP;
} 

VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  NewP.Z = P.Z * co - P.X * si;
  return NewP;
}*/

VOID GLB_Init( DBL r )
{
  INT i, j;
  DBL theta, phi;

  for (i = 0; i < GRID_H; i++)
  {
    theta = i * PI / (GRID_H - 1);
    for (j = 0; j < GRID_W; j++)
    {
      phi = j * 2 * PI / (GRID_W - 1);
      GeomN[i][j].X = sin(theta) * sin(phi);
      GeomN[i][j].Y = cos(theta); 
      GeomN[i][j].Z = sin(theta) * cos(phi);

      Geom[i][j].X = r * sin(theta) * sin(phi);
      Geom[i][j].Y = r * cos(theta); 
      Geom[i][j].Z = r * sin(theta) * cos(phi);
    }
  }

  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      VEC N1 = VecNormalize(VecCrossVec(VecSubVec(Geom[i][j + 1], Geom[i][j]), VecSubVec(Geom[i + 1][j], Geom[i][j])));
      VEC N2 = VecNormalize(VecCrossVec(VecSubVec(Geom[i + 1][j], Geom[i + 1][j + 1]), VecSubVec(Geom[i][j + 1], Geom[i + 1][j + 1])));
      GeomN[i][j] = VecNeg(VecNormalize(VecAddVec(N1, N2)));
    }
}

VOID GLB_Resize( INT Ws, INT Hs)
{
  GlobalWs = Ws;
  GlobalHs = Hs;
  if (GlobalWs >= GlobalHs)
    GlobalWp = GlobalProjSize * GlobalWs / GlobalHs, 
    GlobalHp = GlobalProjSize;
  else
    GlobalHp = GlobalProjSize * GlobalHs / GlobalWs,
    GlobalWp = GlobalProjSize;
}

VOID GLB_Draw( HDC hDC)
{ 
   INT i, j, s = 2;
   DBL 
     t = GlobalTime,
     Xp, Yp, nl;
   VEC P, N, L, L1, C = {0.3, 0.8, 0.5};
   POINT pts[4];
   MATR m;
   static POINT pnts[GRID_H][GRID_W];

   /*SelectObject(hDC, GetStockObject(NULL_PEN));
   SelectObject(hDC, GetStockObject(DC_BRUSH));
   SetDCBrushColor(hDC, RGB(0, 255, 255));*/

   m = MatrMulMatr(MatrMulMatr(MatrRotateX(8 * t), MatrMulMatr(MatrRotateZ(47 * t), MatrRotateY(60 * t))), MatrTranlate(VecSet(0, 0, -3)));

   /* coordinate system */
   for (i = 0; i < GRID_H; i++)
     for (j = 0; j < GRID_W; j++)
     {
       /* Wolrd */
       P = PointTransform(Geom[i][j], m);

       /* Top project plabne */
       Xp = P.X * GlobalProjDist / -P.Z;
       Yp = P.Y * GlobalProjDist / -P.Z;

       /* To screen (viewport transform) */
       pnts[i][j].x = (INT)(Xp * GlobalWs / GlobalWp + GlobalWs / 2);
       pnts[i][j].y = (INT)(-Yp * GlobalHs / GlobalHp + GlobalHs / 2);
     }
     
     /* point */
     
     /*for (i = 0; i < GRID_H; i++)
       for (j = 0; j < GRID_W; j++)
         Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
           pnts[i][j].x + s, pnts[i][j].y + s);*/
     

     /* line */
     
     /*SelectObject(hDC, GetStockObject(DC_PEN));
     SetDCPenColor(hDC, RGB(0, 255, 255));
     
     for (i = 0; i < GRID_H; i++)
     {
       MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
       for (j = 1; j < GRID_W; j++)
         LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
     }

     for (j = 0; j < GRID_W; j++)
     {
       MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
       for (i = 1; i < GRID_H; i++)
         LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
     }*/
     

     /* facets */
     SelectObject(hDC, GetStockObject(NULL_PEN));
     SelectObject(hDC, GetStockObject(DC_BRUSH));
     SetDCBrushColor(hDC, RGB(180, 80, 180));

     L = VecNormalize(VecSet(2, 1, 1));
     L1 = VecNormalize(VecSet(-2, 1, 1));

     for (i = 0; i < GRID_H - 1; i++)
       for (j = 0; j < GRID_W - 1; j++)
       {
         N = VectorTransform(GeomN[i][j], m);
         nl = VecDotVec(N, L);
         if (nl < 0.1)
           nl = 0.1;
         C = VecMulNum(VecSet(0, 0.8, 1), nl);

         nl = VecDotVec(N, L1);
         if (nl < 0.1)
           nl = 0.1;
         C = VecAddVec(C, VecMulNum(VecSet(0.30, 0.8, 0.47), nl));

         pts[0] = pnts[i][j];
         pts[1] = pnts[i][j + 1];
         pts[2] = pnts[i + 1][j + 1];
         pts[3] = pnts[i + 1][j];

         SetDCBrushColor(hDC, ColorTo255(C));
         /* SetDCBrushColor(hDC, ColorTo255(VecDivNum(VecAddVec(N, VecSet1(1)), 2))); */

         if ((pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
             (pts[1].x - pts[2].x) * (pts[1].y + pts[2].y) +
             (pts[2].x - pts[3].x) * (pts[2].y + pts[3].y) +
             (pts[3].x - pts[0].x) * (pts[3].y + pts[0].y) > 0)
           Polygon(hDC, pts, 4);
       }
}
