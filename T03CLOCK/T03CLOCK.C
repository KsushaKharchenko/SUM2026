/* Kharchenko Ksenia, 10-6, 02.06.2026 */

#include <windows.h>
#include <math.h>
#include <time.h>
#define WND_CLASS_NAME "LaLaLa"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *Cmdline, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

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
  CreateWindow(WND_CLASS_NAME, "Time", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);
  /*main program loop */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  static HBITMAP hBmClock, hBm;
  static HDC hMemDCClock, hMemDC;
  static BITMAP bm;
  SYSTEMTIME st;
  INT X, Y, t;
  CHAR Buf[100];

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);

    hMemDCClock = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);

    hBmClock = LoadImage(NULL, "47c27fc2083854f03e6b1981f656c42d.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(hBmClock, sizeof(BITMAP), &bm);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBmClock);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_TIMER:
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDCClock, hBmClock);

    BitBlt(hMemDC, W, H, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);
    SetStretchBltMode(hMemDCClock, COLORONCOLOR);
    StretchBlt(hMemDC, 0, 0, W, H, hMemDCClock, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    GetLocalTime(&st);
    t = st.wSecond / 60 * 2 * 3.14;
    X = sin(t) * 50 + sin(t) * W / 10 * cos(t) + sin(t) * H / 10 * sin(t);
    Y = cos(t) * 50 + cos(t) * H / 10 * sin(t) - cos(t) * W / 10 * sin(t);
    //- sin(t) * W / 10 * cos(t) + sin(t) * H / 10 * sin(t)
    //- cos(t) * H / 10 * sin(t) + cos(t) * W / 10 * sin(t)
    MoveToEx(hDC, W/2, H/2, NULL);
    LineTo(hDC, X, Y);
    TextOut(hDC, 130, 30, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond));
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    DeleteDC(hMemDCClock);
    DeleteObject(hBmClock);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
