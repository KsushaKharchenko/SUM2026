/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: KH6
 * DATE: 21.06.2026
 */
 
#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <GL/glew.h>
 
#include "res/rndres.h"
 
extern HWND KH6_hRndWnd;        /* Work window handle */
extern HDC KH6_hRndDC;     /* Work window memory device context  */
extern INT KH6_RndFrameW, KH6_RndFrameH; /* Work window size */
extern HGLRC KH6_hRndGLRC;
extern INT KH6_MouseWheel;
 
extern DBL
  KH6_RndProjSize,     /* Project plane fit square */
  KH6_RndProjDist,     /* Distance to project plane from viewer (near) */
  KH6_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  KH6_RndMatrView, /* View coordinate system matrix */
  KH6_RndMatrProj, /* Projection coordinate system matrix */
  KH6_RndMatrVP;   /* Stored (View * Proj) matrix */
 
VOID KH6_RndInit( HWND hWnd );
VOID KH6_RndClose( VOID );
VOID KH6_RndResize( INT W, INT H );
VOID KH6_RndCopyFrame( VOID );
VOID KH6_RndStart( VOID );
VOID KH6_RndEnd( VOID );
VOID KH6_RndProjSet( VOID );
VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up );
 
 
extern VEC KH6_RndCamLoc, KH6_RndCamAt, KH6_RndCamRight, KH6_RndCamUp, KH6_RndCamDir; 
 
typedef struct tagkh6VERTEX
 {
  VEC P;   /* ïîçèöèÿ */
  VEC2 T;  /* òåêñòóðíàÿ êîîðäèíàòà */
  VEC N;   /* íîðìàëü */
  VEC4 C;  /* Öâåò (r,g,b,a) */
} kh6VERTEX;
 
/* Primitive type */
typedef enum tagkh6PRIM_TYPE
{
  KH6_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  KH6_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  KH6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
  KH6_RND_PRIM_TRISTRIP,
} kh6PRIM_TYPE;
 
/* Primitive representation type */
typedef struct tagkh6PRIM
{
  kh6PRIM_TYPE Type; /* Primitive type */
 
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
 
  INT NumOfElements; /* Number of indices/vecrtices */
 
  VEC MinBB, MaxBB;  /* Bound box */
 
  MATR Trans;   /* Additional transformation matrix */
  INT MtlNo; /* Material number at stock array */
  INT ShdNo;
} kh6PRIM;
 
/* Primitive collection data type */
typedef struct tagkh6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  kh6PRIM *Prims; /* Array of primitives */
  VEC MinBB, MaxBB; 
  MATR Trans;     /* Common transformation matrix */
} kh6PRIMS;
 
extern MATR KH6_RndPrimsLoadTransform;
 
/* Grid topology representation type */
typedef struct tagkh6GRID
{
  INT W, H;      /* Grid size (in vertices) */
  kh6VERTEX *V;  /* Array (2D) of vertex */
} kh6GRID;
 
extern INT KH6_RndShdAddonI[8]; 
extern FLT KH6_RndShdAddonF[8];
extern VEC KH6_RndShdAddonV[8];
 
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );
 
 
VOID KH6_RndPrimCreate( kh6PRIM *Pr, kh6PRIM_TYPE Type,
                        kh6VERTEX *V, INT NoofV, INT *Ind, INT NoofI );
VOID KH6_RndPrimFree( kh6PRIM *Pr );
VOID KH6_RndPrimDraw( kh6PRIM *Pr, MATR World );
BOOL KH6_RndPrimLoad( kh6PRIM *Pr, CHAR *FileName );
BOOL KH6_RndPrimCreateSphere( kh6PRIM *Pr, DBL R, INT W, INT H ); 
BOOL KH6_RndPrimCreateÑylinder( kh6PRIM *Pr, DBL R, INT W, INT H );
/* BOOL KH6_RndPrimCreateThor( kh6PRIM *Pr, DBL R, INT W, INT H ); */
BOOL KH6_RndPrimLoad( kh6PRIM *Pr, CHAR *FileName );
VOID KH6_RndPrimTriMeshAutoNormals( kh6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI);
 
 
BOOL KH6_RndGridCreate( kh6GRID *G, INT W, INT H );
VOID KH6_RndGridFree( kh6GRID *G ); 
VOID KH6_RndPrimFromGrid( kh6PRIM *Pr, kh6GRID *G );
VOID KH6_RndGridAutoNormals( kh6GRID *G );
BOOL KH6_RndGridCreateSphere( kh6GRID *G, FLT R, INT W, INT H );
 
 
BOOL KH6_RndPrimsCreate( kh6PRIMS *Prs, INT NumOfPrims );
VOID KH6_RndPrimsFree( kh6PRIMS *Prs );
VOID KH6_RndPrimsDraw( kh6PRIMS *Prs, MATR World );
BOOL KH6_RndPrimsLoad( kh6PRIMS *Prs, CHAR *FileName );

BOOL KH6_RndFntLoad( CHAR *FileName );
VOID KH6_RndFntInit( VOID );
VOID KH6_RndFntClose( VOID );
VOID KH6_RndFntDraw3D( CHAR *Str, VEC Pos, FLT Size );
VOID KH6_RndFntDrawBB( CHAR *Str, VEC Pos, FLT Size );
VOID KH6_RndFntDraw( CHAR *Str, VEC Pos, FLT Size );

#endif /* __rnd_h_ */