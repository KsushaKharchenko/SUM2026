/* Kharchenko Ksenia, 10-6, 01.06.2026 */

#include <windows.h>

#define WND_CLASS_NAME "LaLaLa"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *Cmdline, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  /* window class register */

  wc.style = 
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
  hWnd = CreateWindow(WND_CLASS_NAME, "NaNaNa", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 30, 100, 500, 300, NULL, NULL, hInstance, NULL);
  CreateWindow("BUTTON", "Close the window", WS_CHILD | WS_VISIBLE, 290, 100, 150, 50, hWnd, NULL, hInstance, NULL);
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

  switch (Msg)
  {
  case WM_COMMAND:
    PostMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(170, 0, 160));
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(0, 200, 180));
    Ellipse(hDC, 0, 0, W / 2, H);

    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 200, 180));
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(170, 0, 160));
    Ellipse(hDC, W / 2, 0, W, H);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}