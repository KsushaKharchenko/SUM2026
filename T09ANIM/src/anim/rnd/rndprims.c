/* FILE NAME  : rndprims.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 18.06.2026
 * PURPOSE    : 3D animation project.
 *              Rendering primitives handle module.
 */
 
#include <stdio.h>
#include <string.h>
 
#include "rnd.h"
 
/***
 * Primitives support
 ***/
 
/* Load model transformation matrix */
MATR KH6_RndPrimsLoadTransform =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

INT KH6_RndShdAddonI[10];
 
/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL KH6_RndPrimsCreate( kh6PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(kh6PRIMS));
  if ((Prs->Prims = malloc(sizeof(kh6PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(kh6PRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'KH6_RndPrimsCreate' function */
 
/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 * RETURNS: None.
 */
VOID KH6_RndPrimsFree( kh6PRIMS *Prs )
{
  INT i;
 
  if (Prs->Prims != NULL)
  {
    for (i = 0; i < Prs->NumOfPrims; i++)
      KH6_RndPrimFree(&Prs->Prims[i]);
    free(Prs->Prims);
  }
  memset(Prs, 0, sizeof(kh6PRIMS));
} /* End of 'KH6_RndPrimsFree' function */
 
/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       kh6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID KH6_RndPrimsDraw( kh6PRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);

  KH6_RndShdAddonI[0] = Prs->NumOfPrims;
  /* Draw all nontransparent primitives */ 
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (KH6_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
      KH6_RndShdAddonI[1] = i, KH6_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);
 
  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (KH6_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      KH6_RndShdAddonI[1] = i, KH6_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (KH6_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      KH6_RndShdAddonI[1] = i, KH6_RndPrimDraw(&Prs->Prims[i], m);
  glDisable(GL_CULL_FACE);
} /* End of 'KH6_RndPrimsDraw' function */
 
/* Load primitives from '*.G3DM' file function.
 * ARGUMENTS:
 *   - pointer to primitives to create:
 *       kh6PRIMS *Prs;
 *   - '*.G3DM' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndPrimsLoad( kh6PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen;
  UINT p, m, t;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;
  struct tagG3DM_MATERIAL
  {
    CHAR Name[300]; /* Material name */
    /* Illumination coefficients */
    VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
    FLT Ph;             /* Phong power coefficient – shininess */
    FLT Trans;          /* Transparency factor */
    DWORD Tex[8];       /* Texture references 
                        * (8 time: texture number in G3DM file, -1 if no texture) */
    /* Shader information */
    CHAR ShaderString[300]; /* Additional shader information */
    DWORD Shader;       /* Shader number (uses after load into memory) */
  } *mtls;
  MATR trans_m = KH6_RndPrimsLoadTransform, trans_minv = MatrTranspose(MatrInverse(trans_m));
 
  KH6_RndPrimsLoadTransform = MatrIdentity();
 
  /* Read whole file to memory */
  memset(Prs, 0, sizeof(kh6PRIMS));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
 
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  rewind(F);
  fread(mem, 1, flen, F);
  fclose(F);
 
  ptr = mem;
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;
 
  if (!KH6_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
 
  /* Primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;
    DWORD MtlNo;
    kh6VERTEX *V;
    INT *Ind;
    UINT i;
 
    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;
    V = (kh6VERTEX *)ptr;
    ptr += sizeof(kh6VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;
 
    for (i = 0; i < NumOfVertexes; i++)
    {
      V[i].P = PointTransform(V[i].P, trans_m);
      V[i].N = VectorTransform(V[i].N, trans_minv);
    }
 
    KH6_RndPrimCreate(&Prs->Prims[p], KH6_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = KH6_RndMaterialSize + MtlNo;
  }
 
  /* Materials */
  mtls = (VOID *)ptr;
  ptr += sizeof(*mtls) * NumOfMaterials;
  for (m = 0; m < NumOfMaterials; m++)
  {
    kh6MATERIAL mtl = KH6_RndMtlGetDef();
 
    mtl.Ka = VecMinVec(mtls[m].Ka, VecSet1(0.1));
    mtl.Kd = mtls[m].Kd;
    mtl.Ks = mtls[m].Ks;
    mtl.Ph = mtls[m].Ph;
    mtl.Trans = mtls[m].Trans;
    for (t = 0; t < 8; t++)
      if (mtls[m].Tex[t] != -1 && mtls[m].Tex[t] >= 0 && mtls[m].Tex[t] < NumOfTextures)
        mtl.Tex[t] = KH6_RndTexturesSize + mtls[m].Tex[t];
    KH6_RndMtlAdd(&mtl);
  }
 
  /* Textures */
  for (t = 0; t < NumOfTextures; t++)
  {
    CHAR *Name = (CHAR *)ptr;
    DWORD W, H, C;
 
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;
    KH6_RndTexAddImg(Name, W, H, C, ptr);
    ptr += W * H * C;
  }
  free(mem);
  return TRUE;
} /* End of 'KH6_RndPrimsDraw' function */
 
/* END OF 'rndprims.c' FILE */