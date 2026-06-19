/* FILE NAME: rndbase.c
 * PROGRAMMER: KH6
 * DATE: 11.06.2026
 */                                    

#include "rnd.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

VOID KH6_RndInit( HWND hWnd )
{
  INT i, nums;
  HGLRC hRC;
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                               /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };
 
  KH6_hRndWnd = hWnd;
 
  /* Prepare frame compatible device contesxt */
  KH6_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(KH6_hRndDC, &pfd);
 
  DescribePixelFormat(KH6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(KH6_hRndDC, i, &pfd);
 
  /* OpenGL init: rendering context setup */
  KH6_hRndGLRC = wglCreateContext(KH6_hRndDC);
  wglMakeCurrent(KH6_hRndDC, KH6_hRndGLRC);
 
  /* Enable a new OpenGL profile support */
  if(glewInit() != GLEW_OK)
    exit(0);

  wglChoosePixelFormatARB(KH6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(KH6_hRndDC, NULL, ContextAttribs);
  if (hRC != NULL)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(KH6_hRndGLRC);
    KH6_hRndGLRC = hRC;
    wglMakeCurrent(KH6_hRndDC, KH6_hRndGLRC);
  }

#ifndef NDEBUG
  OutputDebugString(glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_RENDERER));
  OutputDebugString("\n");

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
#endif /* NDEBUG */

  /* Render parameters setup */
  glEnable(GL_DEPTH_TEST);
  wglSwapIntervalEXT(0);

  KH6_RndResize(47, 47);
  KH6_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));
  
  KH6_RndRestInit();
}

VOID KH6_RndClose( VOID )
{
  KH6_RndRestClose();

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(KH6_hRndGLRC);
  ReleaseDC(KH6_hRndWnd, KH6_hRndDC);
}

VOID KH6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
 
  /* Setup projection */
  KH6_RndFrameW = W;
  KH6_RndFrameH = H;
 
  KH6_RndProjSet();
}

VOID KH6_RndCopyFrame( VOID )
{
  SwapBuffers(KH6_hRndDC);
}

VOID KH6_RndStart( VOID )
{

  VEC4 ClearColor = {0.3, 0.47, 0.8, 1};
  FLT DepthClearValue = 1;
 
  KH6_RndShdUpdate();

  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
}

VOID KH6_RndEnd( VOID )
{
  glFinish();
}
 
 VOID KH6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  KH6_RndMatrView = MatrView(Loc, At, Up);
  KH6_RndMatrVP = MatrMulMatr(KH6_RndMatrView, KH6_RndMatrProj);
  
  KH6_RndCamLoc = Loc;
  KH6_RndCamAt = At;
  KH6_RndCamRight = VecSet(KH6_RndMatrView.A[0][0],
                           KH6_RndMatrView.A[1][0],
                           KH6_RndMatrView.A[2][0]);
  KH6_RndCamUp = VecSet(KH6_RndMatrView.A[0][1],
                        KH6_RndMatrView.A[1][1],
                        KH6_RndMatrView.A[2][1]);
  KH6_RndCamDir = VecSet(-KH6_RndMatrView.A[0][2],
                         -KH6_RndMatrView.A[1][2],
                         -KH6_RndMatrView.A[2][2]);
}

VOID KH6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = KH6_RndProjSize;
  /* Correct aspect ratio */
  if (KH6_RndFrameW > KH6_RndFrameH)
    rx *= (DBL)KH6_RndFrameW / KH6_RndFrameH;
  else
    ry *= (DBL)KH6_RndFrameH / KH6_RndFrameW;
  KH6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      KH6_RndProjDist, KH6_RndProjFarClip);
  KH6_RndMatrVP = MatrMulMatr(KH6_RndMatrView, KH6_RndMatrProj);
}

 
 