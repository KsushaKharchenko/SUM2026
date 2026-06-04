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
 
void DrawArrow(HWND hWnd, HDC hMemDC, DOUBLE t, INT W, INT H, INT L)
{
  POINT pt;
  INT i;
  POINT pts[4] = {{0, 0}, {-1.5, -3}, {0, -30}, {1.5, -3}},
    pts_res[sizeof(pts)/sizeof(pts[0])];
 
  for (i = 0; i < 4; i++)
  {
    pts[i].x = pts[i].x * L;
    pts[i].y = pts[i].y * L;
    pts_res[i].x = (INT)(W/2 + pts[i].x * cos(t) - pts[i].y * sin(t));
    pts_res[i].y = (INT)(H/2 + pts[i].y * cos(t) + pts[i].x * sin(t));
  }
  Polygon(hMemDC, pts_res, 4);
  MoveToEx(hMemDC, W/2, H/2, NULL);
  //LineTo(hMemDC, (INT)(W/2 + X), (INT)(H/2 - Y));
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
  INT i;
  DOUBLE t, m, o;
  CHAR Buf[100];
 
  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
 
    hMemDCClock = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);
 
    hBmClock = LoadImage(NULL, "47c27fc2083854f03e6b1981f656c42d.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
 
    GetObject(hBmClock, sizeof(bm), &bm);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 3, 8, NULL);
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
 
    BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, 0, 0, W, H, hMemDCClock, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    GetLocalTime(&st);
 
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 133, 187));
    t = (st.wSecond + st.wMilliseconds / 1000.0) / 60.0 * 2 * 3.14;
    DrawArrow(hWnd, hMemDC, t, W, H, 10);
 
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(230, 140, 0));
    m = (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) / 60.0 * 2 * 3.14;
    DrawArrow(hWnd, hMemDC, m, W, H, 8);
 
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(250, 10, 10));
    o = (st.wHour + st.wMinute / 60.0) / 12.0 * 2 * 3.14;
    DrawArrow(hWnd, hMemDC, o, W, H, 6);
 
    TextOut(hMemDC, 130, 30, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond));
 
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
 
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
 