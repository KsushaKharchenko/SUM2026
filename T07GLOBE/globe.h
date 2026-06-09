/* Kharchenko Ksenia, 10-6, 06.06.2026 */
#ifndef __globe_h_
#define __globe_h_

#define GRID_W 18
#define GRID_H 12
typedef DOUBLE DBL;
static DBL PI = 3.1415926535;

typedef struct
{
  DBL X, Y, Z;
}VEC;

VOID GLB_Init( DOUBLE r);

VOID GLB_Resize( INT Ws, INT Hs);

VOID GLB_Draw( HDC hDC);

#endif /* __globe_h_ */