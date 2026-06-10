/* FILE NAME: main.c
 * PURPOSE: main file of  project
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

#include <time.h>

#include "def.h"
#include "anim/rnd/rnd.h"

#define WND_CLASS_NAME "LaLaLa"


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *Cmdline, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;
 
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
  hWnd = CreateWindow(WND_CLASS_NAME, "Globe", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);

  /* main program loop */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    SendMessage(hWnd, WM_TIMER, 30, 0);
  }
  return 0;
}
 

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  MINMAXINFO *minmax;
  DBL t = clock() / 1000.0;
  
  static kh6PRIM Pr, Pr1;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMinTrackSize.y += 100;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    KH6_RndInit(hWnd);
    KH6_RndPrimCreateSphere(&Pr, 1, 15, 10);
    KH6_RndPrimLoad(&Pr1, "bin/models/cow.obj" );
    SetTimer(hWnd, 30, 1, NULL);
    return 0;
  
  case WM_SIZE:
    KH6_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:
    KH6_RndStart();
    
    KH6_RndCamSet(VecSet(20*3, 0, 10*3), VecSet(2, 5, 0), VecSet(0, 5, 0));

    Pr.Trans = MatrMulMatr(MatrMulMatr(MatrRotateY(8 * t), 
      MatrMulMatr(MatrRotateZ(fabs(sin(8*t))), MatrIdentity())), MatrTranslate(VecSet(0, 0, -3)));
    KH6_RndPrimDraw(&Pr1, MatrMulMatr(Pr.Trans, MatrTranslate(VecSet(0, fabs(sin(0.8*t)), 0))));
    
    KH6_RndEnd();
    hDC = GetDC(hWnd);
    KH6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 30, 0);
   
  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    KH6_RndCopyFrame(KH6_hRndDCFrame);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    KH6_RndPrimFree(&Pr);
    KH6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 30, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
 