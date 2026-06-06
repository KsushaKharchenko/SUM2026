/* Kharchenko Ksenia, 10-6, 04.06.2026 */

#include <stdio.h>

#include <windows.h>

typedef DOUBLE DBL;
#define MAX 10
 
INT mas[MAX];
 
DBL A[MAX][MAX];
INT N;
 
VOID LoadMatrix( CHAR *FileName )
{
  INT i, j;
  
  FILE *F;
 
  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return;
  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);
  fclose(F);
}

INT IsParity( VOID )
{
  INT j, k, invers = 0;
  
  for (j = 0; j < N - 1; j++)
    for (k = j + 1; k < N; k++)
      if (mas[j] > mas[k])
        invers++;
  if (invers % 2 == 0)
    return 1;
  else
    return 0;
}
VOID Swap( INT *a, INT *b )
{
  INT tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}

VOID Go( INT Pos, DBL *Det)
{
  INT i, j;
  DBL prod;
  
  if (Pos == N)
  {
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][mas[i]];
    if (IsParity())
      *Det += prod;
    else
      *Det -= prod;
    return;
  }
  else
    for (j = Pos; j < N; j++)
    {
      Swap(&mas[Pos], &mas[j]);
      Go(Pos + 1, Det);
      Swap(&mas[Pos], &mas[j]);
    }
}

VOID main( VOID )
{
  INT i;
  DBL Det = 0.0;

  LoadMatrix("DET.TXT");
  for (i = 0; i < N; i++)
    mas[i] = i;
  Go(0, &Det);
  printf("DET = %i", Det);
  getchar();
  getchar();
}

 
