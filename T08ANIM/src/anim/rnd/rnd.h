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
VOID KH6_RndCopyFrame( HDC hDC );
VOID KH6_RndStart( VOID );
VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up );


/***
 * Primitive handle
 ***/
 
/* Vertex representation type */
typedef struct tagkh6VERTEX
{
  VEC P;  /* Vertex position */
} kh6VERTEX;
 
/* Primitive representation type */
typedef struct tagkh6PRIM
{
  kh6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
 
  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */
 
  MATR Trans;   /* Additional transformation matrix */
} kh6PRIM;
 
/* Primitive create function.
 * ARGUMENTS:
 *   - primitive to be create:
 *       kh6PRIM *Pr;
 *   - number of vertecis and indices:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL KH6_RndPrimCreate( kh6PRIM *Pr, INT NoofV, INT NoofI );
 
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
