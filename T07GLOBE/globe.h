/* Kharchenko Ksenia, 10-6, 06.06.2026 */
#ifndef __globe_h_
#define __globe_h_

#define GRID_W 30
#define GRID_H 20
typedef DOUBLE DBL;
typedef struct
{
  DBL X, Y, Z;
}VEC;
VOID GLB_Init( DOUBLE r);
VOID GLB_Resize( INT Ws, INT Hs);
VOID GLB_Draw( HDC hDC);

#endif /* __globe_h_ */