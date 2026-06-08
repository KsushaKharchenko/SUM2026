/* Kharchenko Ksenia, 10-6, 08.06.2026 */
#ifndef __mth_h_
#define __mth_h_

#include <math.h>
 
#include <windows.h>
 
/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)
 
#define UnitMatrix \
{                  \
  {                \
    {1, 0, 0, 0},  \
    {0, 1, 0, 0},  \
    {0, 0, 1, 0},  \
    {0, 0, 0, 1}   \
  }                \
}
 
 
/* Base float point types */
typedef double DBL;
typedef float FLT;
 
/* Space vector/point representation type */
typedef struct
{
  DBL X, Y, Z;
}VEC;
 
/* Transformation matrix representation type */
typedef struct tagMATR
{
  DBL A[4][4]; /* Matrix elements */
} MATR;

_inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}

_inline VEC VecSet1( DBL A )
{
  VEC r = {A, A, A};
 
  return r;
}

_inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}
  
_inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

_inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

_inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

_inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/* скалярное произведение векторов */
_inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z);
}
 
/* векторное произведение векторов */
_inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}
 
_inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

_inline DBL VecLen2( VEC V )
{
  return VecLen(V) * VecLen(V);
}

_inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

_inline VEC PointTransform( VEC V, MATR M )
{
  return
    VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
           V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
           V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}

_inline VEC VectorTransform( VEC V, MATR M )
{
  return
    VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
           V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
           V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}
 
_inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return
    VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
           (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
           (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

_inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;
 
  return I;
}
 
_inline MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
 
  return m;
}
 
_inline MATR MatrTranlate( VEC T )
{
  MATR m = UnitMatrix;
 
  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}

_inline MATR MatrScale( VEC S )
{
  MATR m = UnitMatrix;
 
  m.A[0][0] = S.X;
  m.A[1][1] = S.Y;
  m.A[2][2] = S.Z;
  return m;
}
_inline MATR MatrRotateX( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[1][1] = c;
  m.A[1][2] = s;
  m.A[2][1] = -s;
  m.A[2][2] = c;
  return m;
}

_inline MATR MatrRotateY( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[0][2] = -s;
  m.A[2][0] = s;
  m.A[2][2] = c;
  return m;
}

_inline MATR MatrRotateZ( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[0][1] = s;
  m.A[1][0] = -s;
  m.A[1][1] = c;
  return m;
}

_inline MATR MatrRotate( VEC P, DBL AngleInDegree )
{
  DBL c = cos(AngleInDegree), s = sin(AngleInDegree);

  return MatrSet(c + P.X * P.X * (1 - c), P.Z * s + P.X * P.Y * (1 - c), - P.Y * s + P.X * P.Z * (1 - c), 0,
                 - P.Z * s + P.X * P.Y * (1 - c), c + P.Y * P.Y * (1 - c), P.X * s + P.Y * P.Z * (1 - c), 0,
                 P.Y * s + P.X * P.Z * (1 - c), - P.X * s + P.Y * P.Z * (1 - c), c + P.Z * P.Z * (1 - c), 0,
                 0, 0, 0, 0);
}

_inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  INT i, j, k;
  MATR r = {{{0}}};
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}

/*  MATR MatrTranspose( MATR M );    MT */
_inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                           DBL A21, DBL A22, DBL A23,
                           DBL A31, DBL A32, DBL A33 )
 {
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

_inline DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}

_inline MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
  MATR r;
  INT i, j, sign[2] = {1, -1}, P[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
 
  if (det == 0)
    return MatrIdentity();
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[j][i] = sign[(i + j) % 2] *
        MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                      M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                      M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
}
#endif /* __mth_h_ */
 
/* END OF 'mth.h' FILE */