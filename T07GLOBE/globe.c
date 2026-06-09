/* Kharchenko Ksenia, 10-6, 06.06.2026 */

#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "globe.h"

#define GLB_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GLB_MAX(A, B) ((A) > (B) ? (A) : (B))

static VEC Geom[GRID_H][GRID_W];
static VEC GeomN[GRID_H][GRID_W];
static INT GLB_Ws, GLB_Hs;
static DBL GLB_ProjSize = 1, GLB_ProjDist = 1, GLB_Wp, GLB_Hp;


COLORREF ColorTo255( VEC Color )
{
  INT
    R = (INT)(Color.X * 255),
    G = (INT)(Color.Y * 255),
    B = (INT)(Color.Z * 255);

  R = GLB_MIN(255, GLB_MAX(0, R));
  G = GLB_MIN(255, GLB_MAX(0, G));
  B = GLB_MIN(255, GLB_MAX(0, B));
  return RGB(R, G, B);
}
VEC RotateZ( VEC P, DBL Angle )
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
}

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
}

VOID GLB_Resize( INT Ws, INT Hs)
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;
  if (GLB_Ws >= GLB_Hs)
    GLB_Wp = GLB_ProjSize * GLB_Ws / GLB_Hs, 
    GLB_Hp = GLB_ProjSize;
  else
    GLB_Hp = GLB_ProjSize * GLB_Hs / GLB_Ws,
    GLB_Wp = GLB_ProjSize;
}

VOID GLB_Draw( HDC hDC)
{ 
   INT i, j, s = 2;
   DBL 
     t = (DOUBLE)clock() / CLOCKS_PER_SEC,
     Xp, Yp, len, nl;
   VEC P, N, L, C = {0.30, 0.8, 0.50};
   POINT pts[4];
   static POINT pnts[GRID_H][GRID_W];

   SelectObject(hDC, GetStockObject(NULL_PEN));
   SelectObject(hDC, GetStockObject(DC_BRUSH));
   SetDCBrushColor(hDC, RGB(0, 255, 255));

   /* coordinate system */
   for (i = 0; i < GRID_H; i++)
     for (j = 0; j < GRID_W; j++)
     {
       P = Geom[i][j];

       P = RotateZ(P, 47 * t);
       P = RotateY(P, 60 * t);

       P.Z -= 3;

       Xp = P.X * GLB_ProjDist / -P.Z;
       Yp = P.Y * GLB_ProjDist / -P.Z;

       pnts[i][j].x = (INT)(Xp * GLB_Ws / GLB_Wp + GLB_Ws / 2);
       pnts[i][j].y = (INT)(-Yp * GLB_Hs / GLB_Hp + GLB_Hs / 2);
     }
     
     /* point */
     for (i = 0; i < GRID_H; i++)
       for (j = 0; j < GRID_W; j++)
         Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
         pnts[i][j].x + s, pnts[i][j].y + s);

     /* line */
     SelectObject(hDC, GetStockObject(DC_PEN));
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
     }

     /* facets */
     

     L.X = 1;
     L.Y = 1;
     L.Z = 1;
     len = sqrt(L.X * L.X + L.Y * L.Y + L.Z * L.Z);
     L.X /= len;
     L.Y /= len;
     L.Z /= len;

     for (i = 0; i < GRID_H - 1; i++)
       for (j = 0; j < GRID_W - 1; j++)
       {
         N = GeomN[i][j]; 

         N = RotateZ(N, 47 * t);
         N = RotateY(N, 60 * t);
         nl = N.X * L.X + N.Y * L.Y + N.Z * L.Z;
         C.X *= nl;
         C.Y *= nl;
         C.Z *= nl;

         pts[0] = pnts[i][j];
         pts[1] = pnts[i][j + 1];
         pts[2] = pnts[i + 1][j + 1];
         pts[3] = pnts[i + 1][j];

         SetDCBrushColor(hDC, ColorTo255(C));
         Polygon(hDC, pts, 4);
       }
}


