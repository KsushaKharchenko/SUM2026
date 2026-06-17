/* FILE NAME  : rndres.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 13.06.2026
*/

#include "anim/rnd/rnd.h"

VOID KH6_RndRestInit( VOID )
{
  KH6_RndShdInit();
  KH6_RndTexInit();
  KH6_RndMtlInit();
}

VOID KH6_RndRestClose( VOID )
{
  KH6_RndMtlClose();
  KH6_RndTexClose();
  KH6_RndShdClose();
}

/* END OF 'rndres.c' FILE */