/* FILE NAME  : units.h
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */


#ifndef __units_h_
#define __units_h_

#include "anim/anim.h"

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateBall( VOID );
\
/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateCow( VOID );

/* Unit control function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateControl( VOID );
/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateLand( VOID );
/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateTexture( VOID );

kh6UNIT * KH6_AnimUnitCreateG3DM( VOID );

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL KH6_RndPrimsCreate( kh6PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 * RETURNS: None.
 */
VOID KH6_RndPrimsFree( kh6PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID KH6_RndPrimsDraw( kh6PRIMS *Prs, MATR World );

/* Load primitives from '*.G3DM' file function.
 * ARGUMENTS:
 *   - pointer to primitives to create:
 *       kh6PRIMS *Prs;
 *   - '*.G3DM' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndPrimsLoad( kh6PRIMS *Prs, CHAR *FileName );



#endif /* __units_h_ */