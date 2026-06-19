/* FILE NAME  : rndmtl.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 17.06.2026
*/

#include "rnd.h" 
 
/* Create grid function.
 * ARGUMENTS:
 *   - grid data:
 *       kh6GRID *G;
 *   - grid size:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndGridCreate( kh6GRID *G, INT W, INT H )
{
  INT i, j;
  
  G->V = malloc(sizeof(kh6VERTEX) * W * H);
  if (G->V == NULL)
    return FALSE;

  memset(G->V, 0, sizeof(kh6VERTEX) * W * H);
  G->W = W;
  G->H = H;

  for (i = 0; i < H; i++)
    for (j = 0; j < W; j++)
    {
      G->V[i * W + j].N = VecSet(0, 1, 0);
      G->V[i * W + j].T.X = j / (W - 1.0);
      G->V[i * W + j].T.Y = i / (H - 1.0);
      G->V[i * W + j].P = VecSet(j, 1, -i);
      G->V[i * W + j].C = VecSet4(1, 1, 1, 1);
    }
  return TRUE;
}
 
/* Free grid function.
 * ARGUMENTS:
 *   - grid data:
 *       kh6GRID *G;
 * RETURNS: None.
 */
VOID KH6_RndGridFree( kh6GRID *G )
{
  free(G->V);
  memset(G, 0, sizeof(kh6GRID));
}
 
/* Create primitive from grid function.
 * ARGUMENTS:
 *   - primitive to be create:
 *       kh6PRIM *Pr;
 *   - grid data:
 *       kh6GRID *G;
 * RETURNS: None.
 */
VOID KH6_RndPrimFromGrid( kh6PRIM *Pr, kh6GRID *G )
{
  INT i, j, k, *Ind;

  memset(Pr, 0, sizeof(kh6PRIM));
  if ((Ind = malloc(sizeof(INT) * ((G->H - 1) * (G->W * 2 + 1) - 1))) == NULL)
    return;

  for (i = 0, k = 0; i < G->H - 1; i++)
  {
    for (j = 0; j < G->W - 1; j++)
    {
      Ind[k++] = (i + 1) * G->W + j;
      Ind[k++] = i * G->W + j
    }
    if (i != G->H - 2)
      Ind[k++] = -1;
  }
  KH6_RndPrimCreate(Pr, KH6_RND_PRIM_TRISTRIP, G->V, G->W * G->H,
                    Ind, (G->H - 1) * (G->W * 2 + 1) - 1);
  free(Ind);
}
 
/* Build grid normals function.
 * ARGUMENTS:
 *   - grid data:
 *       kh6GRID *G;
 * RETURNS: None.
 */
VOID KH6_RndGridAutoNormals( kh6GRID *G )
{
  INT i, j;

  for (i = 0; i < W * H; i++)
    G->V[i].N = VecSet(0, 0, 0);

  for (i = 0; i < H – 1; i++)
    for (j = 0; j < W – 1; j++)
    {
      kh6VERTEX
        *P00 = V + i * W + j,
        *P01 = V + i * W + j + 1,
        *P10 = V + (i + 1) * W + j,
        *P11 = V + (i + 1) * W + j + 1;
      VEC N;
 
      N = VecNormalize(VecCrossVec(VecSubVec(P00->P, P10->P),
                                   VecSubVec(P11->P, P10->P)));
      P00->N = VecAddVec(P00->N, N);
      P10->N = VecAddVec(P10->N, N);
      P11->N = VecAddVec(P11->N, N);
 
      N = VecNormalize(VecCrossVec(VecSubVec(P11->P, P01->P),
                                   VecSubVec(P00->P, P01->P)));
      P00->N = VecAddVec(P00->N, N);
      P01->N = VecAddVec(P01->N, N);
      P11->N = VecAddVec(P11->N, N);
    }
    for (i = 0; i < G->W * G->H; i++)
      V[i].N = VecNormalize(V[i].N);
}
 
/* Create sphere grid function.
 * ARGUMENTS:
 *   - grid data:
 *       kh6GRID *G;
 *   - sphere radius:
 *       FLT R;
 *   - grid size:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KH6_RndGridCreateSphere( kh6GRID *G, FLT R, INT W, INT H )
{
  INT i, j, k;
  DBL theta, phi, nl;

  if (!KH6_RndGridCreate(G, W, H))
    return FALSE;

  for (k = 0, i = 0, theta = 0; i < H; i++, theta += PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
    {
      G->V[k].N = VecSet(sin(theta) * sin(phi),
                         cos(theta),
                         sin(theta) * cos(phi));
           
      G->V[k].C = VecSet4(1, 1, 1, 1);
      G->V[k++].P = VecSet(R * sin(theta) * sin(phi),
                           R * cos(theta),
                           R * sin(theta) * cos(phi));
    
    }
  return TRUE;
}

 
