/* Kharchenko Ksenia, 10-6, 06.06.2026 */
#ifndef __globe_h_
#define __globe_h_

#include "mth.h"

#define GRID_W (18 * 8)
#define GRID_H (12 * 8)

VOID GLB_Init( DOUBLE r);

VOID GLB_Resize( INT Ws, INT Hs);

VOID GLB_Draw( HDC hDC);

#endif /* __globe_h_ */