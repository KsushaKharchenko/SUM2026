/* FILE NAME  : rndfnt.h
 * PROGRAMMER : KH6
 * LAST UPDATE: 18.06.2026
 */

#include "anim/rnd/rnd.h"

/* Current font description */
/* Font data */
static kh6FONT KH6_RndFntFont;
 
/* Font characters primitives */
static kh6PRIM KH6_RndFntChars[256];
 
/* Font material */
static INT KH6_RndFntMtlNo;
 
/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndFntLoad( CHAR *FileName )
{
  DWORD Sign, W, H, *Tex;
  kh6VERTEX Chars[256][4];
  kh6MATERIAL mtl;
  FILE *F;
  INT i;
 
  KH6_RndFntClose();
 
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;
 
  if (fread(&Sign, 4, 1, F) != 1 || Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }
 
  fread(&KH6_RndFntFont, sizeof(kh6FONT), 1, F);
  fread(Chars, sizeof(kh6VERTEX), 4 * 256, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);
  if ((Tex = malloc(W * H * 4)) == NULL)
  {
    memset(&KH6_RndFntFont, 0, sizeof(KH6_RndFntFont));
    memset(&KH6_RndFntFont, 0, sizeof(KH6_RndFntFont));
    fclose(F);
    return FALSE;
  }
  fread(Tex, 4, W * H, F);
  fclose(F);
 
  /* Material */
  mtl = KH6_RndMtlGetDef();
  strncpy(mtl.Name, FileName, KH6_STR_MAX - 1);
  mtl.Tex[0] = KH6_RndTexAddImg(FileName, W, H, 4, Tex);
  mtl.ShdNo = KH6_RndShdAdd("font");
  KH6_RndFntMtlNo = KH6_RndMtlAdd(&mtl);
 
  for (i = 0; i < 256; i++)
  {
    KH6_RndPrimCreate(&KH6_RndFntChars[i], KH6_RND_PRIM_TRISTRIP, Chars[i], 4, NULL, 0);
    KH6_RndFntChars[i].MtlNo = KH6_RndFntMtlNo;
  }
  free(Tex);
  return TRUE;
} /* End of 'KH6_RndFntLoad' function */
 
/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID KH6_RndFntInit( VOID )
{
  KH6_RndFntLoad("bin/fonts/book.g3df");
} /* End of 'KH6_RndFntInit' function */
 
/* Deinit font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID KH6_RndFntClose( VOID )
{
  INT i;
 
  for (i = 0; i < 256; i++)
    KH6_RndPrimFree(&KH6_RndFntChars[i]);
  memset(KH6_RndFntChars, 0, sizeof(KH6_RndFntChars));
  memset(&KH6_RndFntFont, 0, sizeof(KH6_RndFntFont));
} /* End of 'KH6_RndFntInit' function */
 
/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 *   - draw position:
 *       VEC Pos;
 *   - font size:
 *      FLT Size;
 * RETURNS: None.
 */
VOID KH6_RndFntDraw( CHAR *Str, VEC Pos, FLT Size )
{
  FLT startx = Pos.X;
 
  while (*Str != 0)
  {
    if (*Str == '\n')
    {
      Pos.X = startx;
      Pos.Y -= Size;
    }
    else
    {
      if (KH6_RndFntFont.AdvanceX[(BYTE)*Str] != 0)
      {
        //DrawLetterCode(x0, y0, *str, r, g, b)  KH6_RndFntChars[(BYTE)*Str];
        KH6_RndPrimDraw(&KH6_RndFntChars[(BYTE)*Str],
          MatrMulMatr(MatrScale(VecSet(Size, Size, 1)), MatrTranslate(Pos)));
        Pos.X += KH6_RndFntFont.AdvanceX[(BYTE)*Str] * Size;
      }
    }
    Str++;
  }
} /* End of 'KH6_RndFntDraw' function */
 