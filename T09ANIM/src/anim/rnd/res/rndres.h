/* FILE NAME  : rndres.h
 * PROGRAMMER : KH6
 * LAST UPDATE: 13.06.2026
 */
 
#ifndef __rndres_h_
#define __rndres_h_
 
#include "def.h"
 
 
VOID KH6_RndResInit( VOID );
VOID KH6_RndResClose( VOID );
 
#define KH6_STR_MAX 3000
 
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
 
/* Textures stock maximum size */
#define KH6_MAX_TEXTURES 300
/* Textures program store type */
typedef struct tagkh6TEXTURES
{
  CHAR Name[KH6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */  
} kh6TEXTURES;
/* Array of textures */
extern kh6TEXTURES KH6_RndTextures[KH6_MAX_TEXTURES];
/* Textures array store size */
extern INT KH6_RndTexturesSize;  
 
/* Materials program store type */
typedef struct tagkh6MATERIAL
{
  CHAR Name[KH6_STR_MAX]; /* Material name */
 
  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
 
  FLT Trans;                /* Transparency factor */
 
  INT Tex[8];               /* Texture references from texture table (or -1) */
 
  INT ShdNo;                /* Shader number in shader table */ 
} kh6MATERIAL;
/* Materials stock maximum size */
#define KH6_MAX_MATERIALS 300
/* Array of materials */
extern kh6MATERIAL KH6_RndMaterials[KH6_MAX_MATERIALS]; 
/* Materials array store size */
extern INT KH6_RndMaterialsSize;
 
 
 
 
INT KH6_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID KH6_RndShdUpdate( VOID );
VOID KH6_RndShdInit( VOID );
VOID KH6_RndShdClose( VOID );
 
VOID KH6_RndTexInit( VOID );
VOID KH6_RndTexClose( VOID );
INT KH6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
INT KH6_RndTexAdd( CHAR *FileName );
 
kh6MATERIAL KH6_RndMtlGetDef( VOID );
VOID KH6_RndMtlInit( VOID ); 
VOID KH6_RndMtlClose( VOID );
INT KH6_RndMtlAdd( kh6MATERIAL *Mtl );
UINT KH6_RndMtlApply( INT MtlNo ); 
kh6MATERIAL * KH6_RndMtlGet( INT MtlNo );
 
#endif /* __rndres_h_ */