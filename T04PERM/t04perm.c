/* Kharchenko Ksenia, 10-6, 04.06.2026 */

#include <stdio.h>

#include <Windows.h>

#define MAX 3
INT mas[MAX];
/*
VOID Swap( INT *A, INT *B )
{
  INT tmp;
  
  tmp = *A;
  *A = *B;
  *B = tmp;
}


VOID Go( INT Pos )
{
  INT i, j;
  
  if (Pos == MAX - 1)
    for (i = 0; i < MAX; i++)
  {
    mas[i] =  i + 1;
    printf("%i ", mas[i]);
  }
  else
  {
    for (j = Pos; j < MAX; j++)
    {
      Swap(&mas[Pos], &mas[j]);
      Go(Pos + 1);
      Swap(&mas[Pos], &mas[j]);
    }
  }
}
*/

VOID Store( VOID )
{
  INT i;
  FILE *F;

  F = fopen("PERM.TXT", "a");
  if (F != NULL)
    return;

  for (i = 0; i < MAX; i++)
    fprintf(F, "%d%s", mas[i], i < MAX - 1 ? "even" : "odd");
  fprintf(F, "\n");
  fclose(F);
}