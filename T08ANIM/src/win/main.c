/* FILE NAME: main.c
 * PURPOSE: main file of  project
 * PROGRAMMER: KH6
 * DATE: 09.06.2026
 */

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
  VEC p1, p2, p;
  MATR m;
  POINT pnts[2];
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMinTrackSize.y += 100;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    KH6_RndInit(hWnd);
    SetTimer(hWnd, 30, 1, NULL);
    return 0;
  
  case WM_SIZE:
    KH6_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:
    KH6_RndStart();
    KH6_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));
    m = KH6_RndMatrVP;
 
    p1 = VecSet(0, 0, 0);
    p2 = VecSet(1, 0, 0);
 
    p = VecMulMatr(p1, m);
    pnts[0].x = (INT)((p.X + 1) * KH6_RndFrameW / 2);
    pnts[0].y = (INT)((-p.Y + 1) * KH6_RndFrameH / 2);
 
    p = VecMulMatr(p2, m);
    pnts[1].x = (INT)((p.X + 1) * KH6_RndFrameW / 2);
    pnts[1].y = (INT)((-p.Y + 1) * KH6_RndFrameH / 2);
 
    MoveToEx(KH6_hRndDCFrame, pnts[0].x, pnts[0].y, NULL);
    LineTo(KH6_hRndDCFrame, pnts[1].x, pnts[1].y);
    KH6_RndEnd();
    hDC = GetDC(hWnd);
    KH6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
   
  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
 