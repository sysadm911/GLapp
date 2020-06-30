/*
 * (c) Copyright 1995-1999, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * Inet: itarasov@rtuis.miem.edu.ru
 * Phone: (095)942-50-97
 */

#include<windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

HWND hWnd;
HGLRC hGLRC;
HDC hDC;



int SetWindowPixelFormat()
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;


    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;

    pfd.dwFlags   = PFD_DRAW_TO_WINDOW | 
                    PFD_SUPPORT_OPENGL | 
                    PFD_DOUBLEBUFFER;

    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 32;
    pfd.cRedBits       = 8;
    pfd.cRedShift      = 16;
    pfd.cGreenBits     = 8;
    pfd.cGreenShift    = 8;
    pfd.cBlueBits      = 8;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 64;    
    pfd.cAccumRedBits  = 16;
    pfd.cAccumGreenBits   = 16;
    pfd.cAccumBlueBits    = 16;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 8;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;



    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;    
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
       return 0;
    }


    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
        return 0;


    return 1;
}




void resize(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-5,5, -5,5, 2,12);    
    gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
    glMatrixMode( GL_MODELVIEW );
}    



void display()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  	/* remove next tree lines
	 * and enter your code here
	 */
        glTranslated(0.01,0,0);
	    glColor3d(1,0,0);
        auxSolidSphere( 1 );


  glFinish();
  SwapBuffers(wglGetCurrentDC());
}




LRESULT CALLBACK WindowFunc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};
PAINTSTRUCT ps;

switch(msg)
	{

	case WM_CREATE:
	hDC = GetDC(hWnd);
	SetWindowPixelFormat();
	hGLRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hGLRC);

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

        break; 

    
	case WM_DESTROY:
	if (hGLRC) 
	{
	    wglMakeCurrent(NULL, NULL);
	    wglDeleteContext(hGLRC);
	}
	ReleaseDC(hWnd, hDC);
	PostQuitMessage(0);
	break;

	
	
	case WM_PAINT:
	BeginPaint(hWnd, &ps);
	display();
	EndPaint(hWnd, &ps);
	break;
	

    
	case WM_SIZE:
	resize( LOWORD(lParam), HIWORD(lParam) );
	break;  


       default:
	return DefWindowProc(hWnd,msg,wParam,lParam);
	}

return 0;
}




int WINAPI WinMain(HINSTANCE hThisInst,
				   HINSTANCE hPrevInst,
				   LPSTR str,int nWinMode)
{
MSG msg;
WNDCLASS wcl;


wcl.hInstance=hThisInst;
wcl.lpszClassName = "OpenGLWinClass";
wcl.lpfnWndProc = WindowFunc;
wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

wcl.hIcon = NULL;
wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
wcl.lpszMenuName = NULL;

wcl.cbClsExtra = 0;
wcl.cbWndExtra = 0;

wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
RegisterClass(&wcl);


hWnd = CreateWindow("OpenGLWinClass", "Win API Template", 
					 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
					 200,
					 150,
					 400,
					 420,
					 HWND_DESKTOP, NULL,
					 hThisInst, NULL);


ShowWindow(hWnd,nWinMode);
UpdateWindow(hWnd);


while(1)
{
  while( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) ) 
    if(GetMessage(&msg,NULL,0,0))
     { 
      TranslateMessage(&msg);
      DispatchMessage(&msg);
     }
    else
      return 0;

  display();
} 


return 0;
}
