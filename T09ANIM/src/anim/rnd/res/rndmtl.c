/* FILE NAME  : rndmtl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 17.06.2026
*/

#include "anim/rnd/rnd.h"

kh6MATERIAL KH6_RndMaterials[KH6_MAX_MATERIALS];
INT KH6_RndMaterialSize;

VOID KH6_RndMtlInit( VOID )
{
  kh6MATERIAL def = KH6_RndMtlGetDef();
 
  KH6_RndMaterialSize = 0;
  KH6_RndMtlAdd(&def);
}

VOID KH6_RndMtlClose( VOID )
{
  KH6_RndMaterialSize = 0;
}

INT KH6_RndMtlAdd( kh6MATERIAL *Mtl )
{
  return -1;
}

UINT KH6_RndMtlApply( INT MtlNo )
{
  INT prg;
  kh6MATERIAL *mtl;

  if (MtlNo < 0 || MtlNo >= KH6_RndMaterialSize)
    MtlNo = 0;
  mtl = &KH6_RndMaterials[MtlNo];
}

kh6MATERIAL KH6_RndMtlGetDef( VOID )
{
  kh6MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.90, 0.90, 0.90},
    {0.30, 0.30, 0.30},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };
 
  return def_mtl;
}

//kh6MATERIAL * KH6_RndMtlGet( INT MtlNo )

/* END OF 'rndmtl.c' FILE */