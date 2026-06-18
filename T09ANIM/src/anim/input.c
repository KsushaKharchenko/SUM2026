/* FILE NAME: input.c
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */
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

VOID KH6_AnimMouseInit( HWND hWnd )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  KH6_Anim.Mdx = pt.x - KH6_Anim.Mx;
  KH6_Anim.Mdy = pt.y - KH6_Anim.My;

  KH6_Anim.Mx = pt.x;
  KH6_Anim.My = pt.y;

  KH6_Anim.Mdz = KH6_MouseWheel;
  KH6_Anim.Mz += KH6_MouseWheel;
  KH6_MouseWheel = 0;
}

//VOID KH6_AnimMouseResponse( VOID )

//VOID KH6_AnimJoystickInit( VOID );
//VOID KH6_AnimJoystickResponse( VOID );

VOID KH6_AnimInputInit( VOID )
{
  KH6_KeyboardInit();
  KH6_AnimMouseInit(KH6_hRndWnd);
}
VOID KH6_AnimInputResponse( VOID )
{
  KH6_KeyboardResponse();
}