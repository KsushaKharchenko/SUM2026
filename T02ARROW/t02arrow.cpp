/* Kharchenko Ksenia, 10-6, 02.06.2026 */

#include <windows.h>
#include <math.h>
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
  CreateWindow(WND_CLASS_NAME, "NaNaNa", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 30, 100, 500, 300, NULL, NULL, hInstance, NULL);
  /*main program loop */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void DrawArrow(HWND hWnd, HDC hDC, INT Xc, INT Yc, INT L)
{
  POINT pt;
  INT X, Y, i;
  DOUBLE cos, sin, len;
  POINT pts[7] = {{0,-5}, {-10, -15}, {-5, -15}, {-5, -25}, {5, -25}, {5, -15}, {10, -15}},
    pts_res[sizeof(pts)/sizeof(pts[0])];

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  X = (pt.x - Xc) * (INT)(L / hypot((pt.x - Xc),(pt.y - Yc))) + Xc;
  Y = (pt.y - Yc) * (INT)(L / hypot((pt.x - Xc),(pt.y - Yc))) + Yc;
  len = hypot((pt.x - Xc),(pt.y - Yc));
  sin = (pt.x - Xc) / len;
  cos = (pt.y - Yc) / len;

  for (i = 0; i < 7; i++)
  {
    pts_res[i].x = (INT)(X + pts[i].x * cos + pts[i].y * sin);
    pts_res[i].y = (INT)(Y + pts[i].y * cos - pts[i].x * sin);
  }
  Polygon(hDC, pts_res, 7);
  MoveToEx(hDC, Xc, Yc, NULL);
  /*LineTo(hDC, X, Y);*/
}
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  INT x, y, i;
  POINT pt;
  static INT W, H;

  switch (Msg)
  {
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    Rectangle(hDC, 0, 0, W, H);
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 200, 180));
    srand(70);
    for (i = 0; i < 70; i++)
    {
      pt.x = rand () % W;
      pt.y = rand () % H;
      DrawArrow(hWnd, hDC, pt.x, pt.y, 30);
    }
    /*for (x = 0; x < W; x = x + 80)
      for (y = 0; y < H; y = y + 80)
        DrawArrow(hWnd, hDC, x, y, 30);*/
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_DESTROY:
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}