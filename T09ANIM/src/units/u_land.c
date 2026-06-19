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
  kh6GRID G;
 
  if ((hBm = LoadImage(NULL, "bin/heights/hf.bmp", IMAGE_BITMAP, 0, 0,
                       LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    INT w, h;

    GetObject(hBm, sizeof(bm), &bm);
    w = bm.bmWidth;
    h = bm.bmHeight;
    if (bm.bmBitsPixel == 8 && KH6_RndGridCreate(&G, w, h) != NULL)
    {
      BYTE *Bits = bm.bmBits;
      INT x, y;

      for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
        {
          INT hgt = Bits[(h – 1 - y) * bm.bmWidthBytes + x];
 
          G.V[y * w + x].P = VecSet(x / (w – 1.0),
                                    hgt / 255.0,
                                    1 - y / (h – 1.0))
        }
      KH6_RndPrimGridAutoNormals(&G);
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
  KH6_RndPrimDraw(&Uni->Land, MatrIdentity(), 0))));
} /* End of 'KH6_UnitRender' function */

 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateLand( VOID )
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
