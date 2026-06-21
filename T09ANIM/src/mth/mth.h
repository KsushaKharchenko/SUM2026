/* FILE NAME: mth.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */
#ifndef __mth_h_
#define __mth_h_

#include <math.h>
#include <stdio.h> 
#include <windows.h>
 
/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define DEG2RAD(a) D2R(a)
/* Convert radians to degrees */
#define R2D(A) ((A) * (180.0 / PI))
#define RAD2DEG(A) R2D(A)

#define VecAddVec3(A, B, C) VecAddVec(A, VecAddVec(B, C))
#define VecAddVec4(A, B, C, В) VecAddVec(VecAddVec(A, B), VecAddVec(C, D))

#define MatrMulMatr3(A, B, C) MatrMulMatr(A, MatrMulMatr(B, C))
#define MatrMulMatr4(A, B, C, В) MatrMulMatr(MatrMulMatr(A, B), MatrMulMatr(C, D))
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr3(A, B, MatrMulMatr3(C, D, E))

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
  FLT X, Y, Z;
}VEC;

typedef struct
{
  FLT X, Y;
}VEC2;

typedef struct
{
  FLT X, Y, Z, W;
}VEC4;
/* Transformation matrix representation type */
typedef struct tagMATR
{
  FLT A[4][4]; /* Matrix elements */
} MATR;

_inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}

_inline VEC4 VecSet4( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 r = {X, Y, Z, W};
 
  return r;
}

_inline VEC4 Vec4SetVec3( VEC V )
{
  VEC4 v;

  v.X = V.X;
  v.Y = V.Y;
  v.Z = V.Z;
  v.W = 1; return v;
}

_inline VEC VecSet1( FLT A )
{
  VEC r = {A, A, A};
 
  return r;
}

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
_inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

/* Sub two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
_inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

/* Mul Num vector function.
 * ARGUMENTS:
 *   - vector to be add:
 *       VEC V1;
 *   - number to be add:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
_inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

/* Div Num vector function.
 * ARGUMENTS:
 *   - vector to be add:
 *       VEC V1;
 *   - number to be add:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
_inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

/* Vector function.
 * ARGUMENTS:
 *   - vector to be add:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
_inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/* скалярное произведение векторов */
_inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z);
}
 
/* векторное произведение векторов */
_inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}
 
_inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

_inline FLT VecLen2( VEC V )
{
  return VecLen(V) * VecLen(V);
}

/* Obtain minimum of two vectors function.
 * ARGUMENTS:
 *   - vectors to be compare:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMinVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X < V2.X ? V1.X : V2.X,
                V1.Y < V2.Y ? V1.Y : V2.Y,
                V1.Z < V2.Z ? V1.Z : V2.Z);
} /* End of 'VecMinVec' function */

/* Obtain maximum of two vectors function.
 * ARGUMENTS:
 *   - vectors to be compare:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMaxVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X > V2.X ? V1.X : V2.X,
                V1.Y > V2.Y ? V1.Y : V2.Y,
                V1.Z > V2.Z ? V1.Z : V2.Z);
} /* End of 'VecMaxVec' function */

_inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);
 
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
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

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
 
_inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
              FLT A10, FLT A11, FLT A12, FLT A13,
              FLT A20, FLT A21, FLT A22, FLT A23,
              FLT A30, FLT A31, FLT A32, FLT A33 )
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
 
_inline MATR MatrTranslate( VEC T )
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
_inline MATR MatrRotateX( FLT AngleInDegree )
{
  MATR m = UnitMatrix;
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[1][1] = c;
  m.A[1][2] = s;
  m.A[2][1] = -s;
  m.A[2][2] = c;
  return m;
}

_inline MATR MatrRotateY( FLT AngleInDegree )
{
  MATR m = UnitMatrix;
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[0][2] = -s;
  m.A[2][0] = s;
  m.A[2][2] = c;
  return m;
}

_inline MATR MatrRotateZ( FLT AngleInDegree )
{
  MATR m = UnitMatrix;
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[0][1] = s;
  m.A[1][0] = -s;
  m.A[1][1] = c;
  return m;
}

_inline MATR MatrRotate( VEC P, FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  return MatrSet(        c + P.X * P.X * (1 - c),   P.Z * s + P.X * P.Y * (1 - c), - P.Y * s + P.X * P.Z * (1 - c), 0,
                 - P.Z * s + P.X * P.Y * (1 - c),         c + P.Y * P.Y * (1 - c),   P.X * s + P.Y * P.Z * (1 - c), 0,
                   P.Y * s + P.X * P.Z * (1 - c), - P.X * s + P.Y * P.Z * (1 - c),         c + P.Z * P.Z * (1 - c), 0,
                                               0,                               0,                               0, 0);
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

_inline MATR MatrTranspose( MATR M )
{
  INT i, j;
  MATR MT = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      MT.A[i][j] = M.A[j][i];
  return MT;
}
_inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                           FLT A21, FLT A22, FLT A23,
                           FLT A31, FLT A32, FLT A33 )
 {
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

_inline FLT MatrDeterm( MATR M )
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
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}

_inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);
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

/* Perspective (frustum) projection matrix setup function.
 * ARGUMENTS:
 *   - frustum side facets coordinates:
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  MATR m =
  {
    {
      {      2 * Near / (Right - Left),                               0,                              0,  0},
      {                              0,       2 * Near / (Top - Bottom),                              0,  0},
      {(Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),   -(Far + Near) / (Far - Near), -1},
      {                              0,                               0, -2 * Near * Far / (Far - Near),  0}
    }
  };
 
  return m;
} /* End of 'MatrFrustum' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
 
  return m;
} /* End of 'MatrView' function */
_inline VOID PrintMatrix( CHAR *Text, MATR M )
{
  INT i, j;
  
  printf("%s\n", *Text);

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      printf("%d ", M.A[i][j]);
}
 
_inline VOID PrintVector( CHAR *Text, VEC V )
{
  printf("%s\n", *Text);
  
  printf("X = %d, Y = %d, Z = %d", V.X, V.Y, V.Z);
}

/* Random number obtain in range [0.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (FLT) result random number.
 */
__inline FLT Rnd0( VOID )
{
  return (FLT)rand() / RAND_MAX;
} /* End of 'Rnd0' function */
 
/* Random number obtain in range [-1.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (FLT) result random number.
 */
__inline FLT Rnd1( VOID )
{
  return 2.0 * rand() / RAND_MAX - 1;
} /* End of 'Rnd1' function */


#endif /* __mth_h_ */
 
/* END OF 'mth.h' FILE */
