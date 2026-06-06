/* Kharchenko Ksenia, 10-6, 06.06.2026 */
#include <windows.h>
#include <math.h>
#include <time.h>
#include "globe.h"

static INT GLB_Ws, GLB_Hs;
static VEC Geom[GRID_H][GRID_W];
static DBL PI = 3.1415926535;
static DBL GLB_ProjSize = 1, GLB_ProjDist = 1, GLB_Wp, GLB_Hp;

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
      Geom[i][j].X = r * sin(theta) * sin(phi);//* GLB_Ws / GLB_Wp + GLB_Ws / 2;
      Geom[i][j].Y = r * cos(theta); //* GLB_Hs / GLB_Hp) + GLB_Hs / 2;
      Geom[i][j].Z = r * sin(theta) * cos(phi);
    }
  }
}

VOID GLB_Resize( INT Ws, INT Hs)
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;
  if (GLB_Ws >= GLB_Hs)
    GLB_Wp = GLB_ProjSize * GLB_Ws / GLB_Wp, 
    GLB_Hp = GLB_ProjSize;
  else
    GLB_Hp = GLB_ProjSize * GLB_Hs / GLB_Hp,
    GLB_Wp = GLB_ProjSize;
}

VOID GLB_Draw( HDC hDC)
{
   static POINT pts[GRID_H][GRID_W]; 
   INT i, j, s = 2;
   DBL t;
   VEC P;

   t = 8 * (DOUBLE)clock() / CLOCKS_PER_SEC;
   for (i = 0; i < GRID_H; i++)
     for (j = 0; j < GRID_W; j++)
     {
       P = Geom[i][j];
       P = RotateZ(P, 47 + t);
       P = RotateY(P, 60 + t);
       pts[i][j].x = GLB_Ws / 2 + (LONG)(P.X);
       pts[i][j].y = GLB_Hs / 2 - (LONG)(P.Y);
     }
     
     SelectObject(hDC, GetStockObject(DC_BRUSH));
     SetDCBrushColor(hDC, RGB(0, 255, 255));
     for (i = 0; i < GRID_H; i++)
       for (j = 0; j < GRID_W; j++)
         Ellipse(hDC, pts[i][j].x - s, pts[i][j].y - s,
         pts[i][j].x + s, pts[i][j].y + s);
     SelectObject(hDC, GetStockObject(DC_PEN));
     SetDCPenColor(hDC, RGB(0, 255, 255));
     for (i = 0; i < GRID_H; i++)
       for (j = 1; j < GRID_W; j++)
       {
         MoveToEx(hDC, pts[i][0].x, pts[i][0].y, NULL);
         LineTo(hDC, pts[i][j].x, pts[i][j].y);
       }
}


