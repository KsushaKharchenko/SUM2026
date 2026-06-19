/* FILE NAME  : rndmtl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 17.06.2026
*/

#include "anim/rnd/rnd.h"

kh6MATERIAL KH6_RndMaterials[KH6_MAX_MATERIALS];
INT KH6_RndMaterialSize;

static struct
{
  char *Name;
  float amb[3], dif[3], spec[3], shin;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};
#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))

VOID KH6_RndMtlInit( VOID )
{
  INT i;
  kh6MATERIAL mtl = KH6_RndMtlGetDef();
 
  KH6_RndMaterialSize = 0;
  KH6_RndMtlAdd(&mtl);

  for (i = 0; i < MTL_N; i++)
  {
    strcpy(mtl.Name, "std::");
    strcat(mtl.Name, MtlLib[i].Name);
    mtl.Ka = MtlLib[i].amb;
    mtl.Kd = MtlLib[i].diff;
    mtl.Ks = MtlLib[i].spec;
    mtl.Ph = MtlLib[i].shin;
    KH6_RndMtlAdd(&mtl);
  }
}

VOID KH6_RndMtlClose( VOID )
{
  KH6_RndMaterialSize = 0;
}

INT KH6_RndMtlAdd( kh6MATERIAL *Mtl )
{
  if (KH6_RndMaterialSize >= KH6_MAX_MATERIALS)
    return -1;

  KH6_RndMaterials[KH6_RndMaterialSize] = *Mtl;
  return KH6_RndMaterialSize++;
}

UINT KH6_RndMtlApply( INT MtlNo )
{
  UINT prg;
  kh6MATERIAL *mtl;
 
  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= KH6_RndMaterialSize)
    MtlNo = 0;
  mtl = &KH6_RndMaterials[MtlNo];
 
  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= KH6_RndShadersSize)
    prg = 0;
  prg = KH6_RndShaders[prg].ProgId;
 
  if (prg == 0)
    return 0;
 
  glUseProgram(prg);

  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, KH6_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, KH6_Anim.GlobalTime);
 
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);
} 

kh6MATERIAL KH6_RndMtlGetDef( VOID )
{
  INT i;
  kh6MATERIAL mtl;

  memset(&mtl, 0, sizeof(mtl));
  strncpy(mtl.Name, "Default", KH6_STR_MAX - 1);
  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(0.9);
  mtl.Ks = VecSet1(0.2);
  mtl.Ph = 30;
  mtl.Trans = 1;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;
  return mtl;
}

kh6MATERIAL * KH6_RndMtlGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo >= KH6_RndMaterialSize)
    MtlNo = 0;
  return &KH6_RndMaterials[MtlNo];
}

/* END OF 'rndmtl.c' FILE */