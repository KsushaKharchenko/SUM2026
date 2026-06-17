/* FILE NAME  : rndres.h
 * PROGRAMMER : KH6
 * LAST UPDATE: 13.06.2026
*/

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"

#define KH6_STR_MAX 300

VOID KH6_RndRestInit( VOID );
VOID KH6_RndRestClose( VOID );

/* SHADERS GROUP */

/* Shaders stock maximum size */
#define KH6_MAX_SHADERS 30

/* Shader program store type */
typedef struct tagkh6SHADER
{
  CHAR Name[KH6_STR_MAX]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} kh6SHADER;

/* Array of shaders */
extern kh6SHADER KH6_RndShaders[KH6_MAX_SHADERS];
/* Shadres array store size */
extern INT KH6_RndShadersSize;

VOID KH6_RndShdInit( VOID );

VOID KH6_RndShdClose( VOID );

INT KH6_RndShdAdd( CHAR *ShaderFileNamePrefix );

VOID KH6_RndShdUpdate( VOID );

/* TEXTURE GROUP */

/* Textures stock maximum size */
#define KH6_MAX_TEXTURES 102

/* Texture program store type */
typedef struct tagkh6TEXTURE
{
  CHAR Name[KH6_STR_MAX]; /*Texture name*/
  INT W, H;              /*Texture size in pixels */
  UINT TexId;           /*OpenGL texture id */
}kh6TEXTURE;

/* Array of textures */
extern kh6TEXTURE KH6_RndTextures[KH6_MAX_TEXTURES];
/* Textures array store size */
extern INT KH6_RndTexturesSize;

VOID KH6_RndTexInit( VOID );

VOID KH6_RndTexClose( VOID );

INT KH6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

INT KH6_RndTexAddFromFile( CHAR *FileName );

/* MATERIALS GROUP */

/* Materials stock maximum size */
#define KH6_MAX_MATERIALS 30

/* Material program store type */
typedef struct tagkh6MATERIAL
{
  CHAR Name[KH6_STR_MAX]; /*Texture name*/
  /* illumination coefficients */
  VEC Ka, Kd, Ks;        /*Ambient, diffuse, specular coefficients */
  FLT Ph;               /*Phong power coefficient */
  FLT Trans;           
  INT Tex[8];
  INT ShdNo;
}kh6MATERIAL;

/* Array of shaders */
extern kh6MATERIAL KH6_RndMaterials[KH6_MAX_MATERIALS];
/* Shadres array store size */
extern INT KH6_RndMaterialSize;

VOID KH6_RndMtlInit( VOID );

VOID KH6_RndMtlClose( VOID );

INT KH6_RndMtlAdd( kh6MATERIAL *Mtl );

UINT KH6_RndMtlApply( INT MtlNo );

kh6MATERIAL KH6_RndMtlGetDef( VOID );

kh6MATERIAL * KH6_RndMtlGet( INT MtlNo );

#endif /* __rndres_h_ */