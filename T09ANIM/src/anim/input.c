#include "anim.h"

static BYTE OldKeys[256];

static VOID KH6_AnimKeyboardInit( VOID )
{
  INT i;

  GetKeboardState(KH6_Anim.Keys);
  for (i = 0; i < 256; i++)
    KH6_Anim.Keys[i]  >>= 7;
  memcpy(OldKeys, KH6_Anim.Keys, 256);
}
VOID KH6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeboardState(KH6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    KH6_Anim.Keys[i]  >>= 7;
    KH6_Anim.KeysClick[i] = KH6_Anim.Keys[i] && !OldKeys[i];
  }
  memcpy(OldKeys, KH6_Anim.Keys, 256);
}

VOID KH6_AnimMouseInit( HWND hWnd );
VOID KH6_AnimMouseResponse( VOID );

VOID KH6_AnimJoystickInit( VOID );
VOID KH6_AnimJoystickResponse( VOID );

VOID KH6_AnimInputInit( HWND hWnd )
{
  KeyboardInit();
}
VOID KH6_AnimInputResponse( VOID )
{
  KeyboardResponse();
}