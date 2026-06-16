
#include <string.h>

#include "anim.h"

static BYTE OldKeys[256];

VOID KH6_KeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(KH6_Anim.Keys);
  for (i = 0; i < 256; i++)
    KH6_Anim.Keys[i]  >>= 7;
  memcpy(OldKeys, KH6_Anim.Keys, 256);
}
VOID KH6_KeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(KH6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    KH6_Anim.Keys[i]  >>= 7;
    KH6_Anim.KeysClick[i] = KH6_Anim.Keys[i] && !OldKeys[i];
  }
  memcpy(OldKeys, KH6_Anim.Keys, 256);
}

//VOID KH6_AnimMouseInit( HWND hWnd );
//VOID KH6_AnimMouseResponse( VOID );

//VOID KH6_AnimJoystickInit( VOID );
//VOID KH6_AnimJoystickResponse( VOID );

VOID KH6_AnimInputInit( VOID )
{
  KH6_KeyboardInit();
}
VOID KH6_AnimInputResponse( VOID )
{
  KH6_KeyboardResponse();
}