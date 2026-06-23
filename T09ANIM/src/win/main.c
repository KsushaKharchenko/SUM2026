/* FILE NAME  : main.c
 * PROGRAMMER : KH6
 * LAST UPDATE: 11.06.2026
 */

#include "units/units.h"


#define WND_CLASS_NAME "LaLaLa"


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *Cmdline, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;
  INT i;
  CONSOLE_FONT_INFOEX cfi = {0};
  HWND hConWnd;


 
  /* Create console */
  AllocConsole();
 
  cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
  cfi.dwFontSize.Y = 18;
  cfi.FontWeight = FW_BOLD;
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
 
  freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  printf("\x1b[38;2;%d;%d;%dm \x1b[48;2;%d;%d;%dm", 255, 255, 0, 0, 102, 102);
  printf("Группа компьютерной графики ФМЛ № 30\n");
  printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", 0, 255, 0, 90, 90, 90);
  printf("Computer Graphics Support Group\n");
  printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", 255, 255, 255, 0, 0, 0);
  fflush(stdout);
 
  hConWnd = GetConsoleWindow();
  /* MoveWindow(hConWnd, 2560 + 1920 / 2, 0, 1920 / 2, 1080, FALSE); */
  SetWindowPos(hConWnd, HWND_TOP, 2560 + 1920 / 2, 0, 1920 / 2, 1000, 0);

  /* window class register */
 
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpfnWndProc = MyWindowFunc;
 
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  /* create window */
  hWnd = CreateWindow(WND_CLASS_NAME, "Animation", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);

    
  /* add animation object */
  KH6_AnimAddUnit(KH6_AnimUnitCreateControl());
  //for (i = 0; i < 30; i++)
   // KH6_AnimAddUnit(KH6_UnitCreateBall());
  //KH6_AnimAddUnit(KH6_AnimUnitCreateCow());
  //KH6_AnimAddUnit(KH6_AnimUnitCreateLand());
  //KH6_AnimAddUnit(KH6_AnimUnitCreateTexture());
  //KH6_AnimAddUnit(KH6_AnimUnitCreateG3DM());
  KH6_AnimAddUnit(KH6_AnimUnitCreateDOG());
  KH6_AnimAddUnit(KH6_AnimUnitCreateBOWL());
  KH6_AnimAddUnit(KH6_AnimUnitCreateHOUSE());
  KH6_AnimAddUnit(KH6_AnimUnitCreateTOY());
  KH6_AnimAddUnit(KH6_AnimUnitCreateLAND());


  /* main program loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 30, 0);
  return msg.wParam;
}
 

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  MINMAXINFO *minmax;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMinTrackSize.y += 100;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    KH6_AnimInit(hWnd);
    return 0;
  
  case WM_SIZE:
    KH6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:
    KH6_AnimRender();
    KH6_AnimCopyFrame();
    return 0;
   
  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    KH6_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;

  case WM_ACTIVATE:
    KH6_Anim.IsActive = LOWORD(wParam) != WA_INACTIVE;
    return 0;
  case WM_ENTERSIZEMOVE:
    KH6_Anim.IsActive = FALSE;
    return 0;
  case WM_EXITSIZEMOVE:
    KH6_Anim.IsActive = TRUE;
    return 0;

  case WM_MOUSEWHEEL:
    KH6_MouseWheel = KH6_MouseWheel + (SHORT)HIWORD(wParam);
    return 0;

  case WM_DESTROY:
    KH6_AnimClose();
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWindowFunc' function */
    
/* END OF 'main.c' FILE */
 