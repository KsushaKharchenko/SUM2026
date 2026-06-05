/* Kharchenko Ksenia, 10-6, 04.06.2026 */

#include <stdio.h>

#include <windows.h>

#define MAX 3
INT mas[MAX];

VOID Store( VOID )
{
  INT i, j, k, invers = 0;
  FILE *F;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;

  for (j = 0; j < MAX - 1; j++)
    for (k = j + 1; k < MAX; k++)
      if (mas[j] > mas[k])
        invers++;

  for (i = 0; i < MAX; i++)
    fprintf(F, "%d ", mas[i]);
  if (invers % 2 == 0)
    fprintf(F, "even\n");
  else
    fprintf(F, "odd\n");
  fclose(F);
}

VOID Swap( INT *a, INT *b )
{
  INT tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}

VOID Go( INT Pos )
{
  INT j;
  
  if (Pos == MAX)
  {
    Store();
    return;
  }
  else
    for (j = Pos; j < MAX; j++)
    {
      Swap(&mas[Pos], &mas[j]);
      Go(Pos + 1);
      Swap(&mas[Pos], &mas[j]);
    }
}

VOID main( VOID )
{
  INT i;

  for (i = 0; i < MAX; i++)
    mas[i] = i + 1;
  Go(0);
}


