/* FILE NAME: globe.h
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 06.06.2026
 */

#ifndef __globe_h_
#define __globe_h_

#include "mth.h"

#define GRID_W (18 * 8)
#define GRID_H (12 * 8)

VOID GlobalInit( DOUBLE r);

VOID GlobalResize( INT Ws, INT Hs);

VOID GlobalDraw( HDC hDC);

#endif /* __globe_h_ */