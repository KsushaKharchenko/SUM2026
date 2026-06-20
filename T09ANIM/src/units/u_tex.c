/* FILE NAME  : u_tex.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 20.06.2026
 */

#include "units.h"

typedef struct tagkh6UNIT_TEX
{
  KH6_UNIT_BASE_FIELDS;
  kh6PRIM Pr;               /*primitive simple*/ 
  INT Mtlno, TexId;         /* Material and texture number*/
}kh6UNIT_TEX;

static VOID KH6_UnitInit( kh6UNIT_TEX *Uni, kh6ANIM *Ani )
{
  kh6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
 
  FLT t[2][2] =
  {
    {0.8, 1},
    {1, 0.3}
  };
 
  kh6MATERIAL mtl = KH6_RndMtlGetDef();
   
  strncpy(mtl.Name, "Texture sample", KH6_STR_MAX - 1);
  mtl.ShdNo = KH6_RndShdAdd("textures");
  Uni->Mtlno = KH6_RndMtlAdd(&mtl);

  glGenTextures(1, &Uni->TexId);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);
  
  KH6_RndPrimCreate(&Uni->Pr, KH6_RND_PRIM_TRISTRIP, V, 4, NULL, 0);
} /* End of 'KH6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_TEX *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitClose( kh6UNIT_TEX *Uni, kh6ANIM *Ani )
{
  glDeleteTextures(1, &Uni->TexId);
  KH6_RndPrimFree(&Uni->Pr);
} /* End of 'KH6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_TEX *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitResponse( kh6UNIT_TEX *Uni, kh6ANIM *Ani )
{
} /* End of 'KH6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kh6UNIT_TEX *Uni;
 *   - animation context:
 *       kh6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KH6_UnitRender( kh6UNIT_TEX *Uni, kh6ANIM *Ani )
{
  /*INT loc;
 
  glUseProgram(KH6_RndProgId);
  if ((loc = glGetUniformLocation(KH6_RndProgId, "Tex")) != -1)
    glUniform1i(loc, 1);*/
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  KH6_RndPrimDraw(&Uni->Pr, MatrIdentity());
} /* End of 'KH6_UnitRender' function */

 
/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kh6UNIT *) pointer to created unit.
 */
kh6UNIT * KH6_UnitCreateTexture( VOID )
{
  kh6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = KH6_AnimUnitCreate(sizeof(kh6UNIT_TEX))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)KH6_UnitInit;
  Uni->Close = (VOID *)KH6_UnitClose;
  Uni->Response = (VOID *)KH6_UnitResponse;
  Uni->Render = (VOID *)KH6_UnitRender;
 
  return Uni;
} /* End of 'KH6_AnimUnitCreate' function */
