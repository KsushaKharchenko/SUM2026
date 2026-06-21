/* FILE NAME  : u_land.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 12.06.2026
 */

#include "units.h"

typedef struct tagkh6UNIT_LAND
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIM Land;               /*land primitive*/            
}kh6UNIT_LAND;

static VOID KH6_UnitInit( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
 
  HBITMAP hBm;
  BITMAP bm;

 
  if ((hBm = LoadImage(NULL, "bin/height/hf.bmp", IMAGE_BITMAP, 0, 0,
                       LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    INT w, h;
    kh6GRID G;

    GetObject(hBm, sizeof(bm), &bm);
    w = bm.bmWidth;
    h = bm.bmHeight;
    if (KH6_RndGridCreate(&G, w, h))
    {
      BYTE *Bits = bm.bmBits;
      INT x, y;
      FLT size = 100;

      for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
        {
          INT hgt = Bits[(h - 1 - y) * bm.bmWidthBytes + x];

          G.V[y * G.W + x].P = VecSet((2 * x / (w - 1.0) - 1) * size,
                                    10 * hgt / 255.0, 
                                    (1 - 2 * y / (h - 1.0)) * size);
        }
      KH6_RndGridAutoNormals(&G);
      KH6_RndPrimFromGrid(&Uni->Land, &G);
      KH6_RndGridFree(&G);
    }
  }
} /* End of 'KH6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_LAND *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitClose( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimFree(&Uni->Land);
} /* End of 'KH6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_LAND *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitResponse( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
} /* End of 'KH6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_LAND *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitRender( kh6UNIT_LAND *Uni, kh6ANIM *Ani )
{
  KH6_RndPrimDraw(&Uni->Land, MatrIdentity());
} /* End of 'KH6_UnitRender' function */

 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_AnimUnitCreateLand( VOID )
{
  kh6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_LAND))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
 
  return Uni;
} /* End of 'KH6_AnimUnitCreate' function */
