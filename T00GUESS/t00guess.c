/* Kharchenko Ksenia, 10-6, 01.06.2026 */

#include <stdio.h>
#include <windows.h>

void main( void )
{
  char s[100];
  int a = 0, b = 100, m, res;

  MessageBox( NULL, "number 0 -100", "Guess number", MB_OK);
  while (b >= a)
  {
    m = (a + b) / 2;
    sprintf(s,"%i", m);
    res = MessageBox( NULL, s, "Question", MB_YESNOCANCEL);

    if (res == IDYES)
      a = m + 1;
    else if (res == IDNO)
        b = m - 1;
    else
    {
      MessageBox(NULL, s, "info", MB_OK | MB_ICONINFORMATION);
      break;
    }
  }
}