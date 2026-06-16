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
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateControl( VOID );

#endif /* __units_h_ */