/* FILE NAME: rnd.h
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>

#include "res/rndres.h"


extern HWND KH6_hRndWnd;
extern HDC KH6_hRndDC;
extern HGLRC KH6_hRndGLRC;
extern INT KH6_RndFrameW, KH6_RndFrameH;

extern DBL
  KH6_RndProjSize,     /* Project plane fit square */
  KH6_RndProjDist,     /* Distance to project plane from viewer (near) */
  KH6_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  KH6_RndMatrView, /* View coordinate system matrix */
  KH6_RndMatrProj, /* Projection coordinate system matrix */
  KH6_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC 
  KH6_RndCamLoc,
  KH6_RndCamAt,
  KH6_RndCamDir,
  KH6_RndCamUp,
  KH6_RndCamRight;

VOID KH6_RndProjSet( VOID );
VOID KH6_RndResize( INT W, INT H );
VOID KH6_RndInit( HWND hWnd );
VOID KH6_RndClose( VOID );
VOID KH6_RndEnd( VOID );
VOID KH6_RndCopyFrame( VOID );
VOID KH6_RndStart( VOID );
VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up );


/***
 * Primitive handle
 ***/
 
/* Vertex representation type */
typedef struct tagkh6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinates */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} kh6VERTEX;


/* Primitive type */
typedef enum tagkh6PRIM_TYPE
{
  KH6_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  KH6_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  KH6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
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

  INT MtlNo;    /*Material number of shader */
} kh6PRIM;
 
/* Create primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       kh6PRIM *Pr;
 *   - primitive type:
 *       kh6PRIM_TYPE Type;
 *   - vertex attributes array:
 *       kh6VERTEX *V;
 *   - vertex attributes array size:
 *       INT NoofV;
 *   - primitive vertex index array:
 *       INT *Ind;
 *   - primitive vertex index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID KH6_RndPrimCreate( kh6PRIM *Pr, kh6PRIM_TYPE Type,
                        kh6VERTEX *V, INT NoofV, INT *Ind, INT NoofI );
 
/* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be free:
 *       kh6PRIM *Pr;
 * RETURNS: None.
 */
VOID KH6_RndPrimFree( kh6PRIM *Pr );
 
/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive to be draw:
 *       kh6PRIM *Pr;
 *   - transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID KH6_RndPrimDraw( kh6PRIM *Pr, MATR World );
 
/* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be load:
 *       kh6PRIM *Pr;
 *   - primitve filename (.OBJ):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL KH6_RndPrimLoad( kh6PRIM *Pr, CHAR *FileName );
 
/* Create sphere primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       kh6PRIM *Pr;
 *   - sphere radius:
 *       DBL R;
 *   - split parts counts:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndPrimCreateSphere( kh6PRIM *Pr, DBL R, INT W, INT H );

/* Create cilinder primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       kh6PRIM *Pr;
 *   - cilinder radius:
 *       DBL R;
 *   - split parts counts:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndPrimCilinder( kh6PRIM *Pr, DBL R, INT W, INT H );

VOID KH6_RndPrimTriMeshAutoNormals( kh6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI);

VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );

#endif /* __rnd_h_ */