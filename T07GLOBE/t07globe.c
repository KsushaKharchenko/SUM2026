/* FILE NAME: t07globe.c
 * PURPOSE: 
 * PROGRAMMER: KH6
 * DATE: 06.06.2026
 */


#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "globe.h"
#include "timer.h"

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

  INT t;
  static DBL FPS = 30;
  static INT StartTime, FrameCount;
  static CHAR Buf[102];
  static INT W, H;
  static HBITMAP hBm;
  static HDC hMemDC;
  static BITMAP bm;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;

    minmax ->ptMinTrackSize.y += 100;
    minmax ->ptMinTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    GLB_TimerInit();
    SetTimer(hWnd, 30, 1, NULL);
    GLB_TimerInit();

    SetTimer(hWnd, 30, 2, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;

    GLB_Init(0.8);
    FrameCount = 0;
    StartTime = clock();
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    GLB_Resize(W, H);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:

    if (W > 0 && H > 0)
    {
      SelectObject(hMemDC, GetStockObject(DC_BRUSH));
      SelectObject(hMemDC, GetStockObject(DC_PEN));
      SetDCBrushColor(hMemDC, RGB(0, 0, 0));
      SetDCPenColor(hMemDC, RGB(0, 0, 0));
      Rectangle(hMemDC, 0, 0, W, H);

      GLB_Draw(hMemDC);
    }
    FrameCount++;
    GLB_TimerResponse();
    t = clock();
    /*if (t - StartTime > CLOCKS_PER_SEC)
    {
      FPS = FrameCount / ((t - StartTime) / (DBL)CLOCKS_PER_SEC);
      FrameCount = 0;
      StartTime = t;
    }*/
    if (W > 0 && H > 0)
    {
      /* Clear frame */
      SelectObject(hMemDC, GetStockObject(DC_BRUSH));
      SelectObject(hMemDC, GetStockObject(DC_PEN));
      SetDCBrushColor(hMemDC, RGB(255, 255, 255));
      SetDCPenColor(hMemDC, RGB(255, 255, 255));
      Rectangle(hMemDC, 0, 0, W, H);

      /* Draw frame contents */
      GLB_Draw(hMemDC);

      TextOut(hMemDC, 0, 0, Buf, sprintf(Buf, "FPS: %.5f", FPS));

      /* Copy frame to screen */

      hDC = GetDC(hWnd);
      BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
      ReleaseDC(hWnd, hDC);
    }
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);


    if (wParam == 'P')
      GlobalIsPause = !GlobalIsPause;
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    PostMessage(NULL, WM_QUIT, 0, 0);
    KillTimer(hWnd, 30);
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
 