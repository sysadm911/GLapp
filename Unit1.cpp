// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
#pragma comment (lib, "glaux.lib")
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void TForm1::InitDisplay(HWND hwnd) {
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat = 0;
	dc = GetDC(hwnd);
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	nPixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, nPixelFormat, &pfd);
	hrc = wglCreateContext(dc);
	wglMakeCurrent(dc, hrc);
	glClearColor(0, 0, 0, 1.0); // цвет фона
	glClear(GL_COLOR_BUFFER_BIT); // очистка буфера цвета
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	InitDisplay(Handle);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender) {
	wglMakeCurrent(0, 0);
	wglDeleteContext(hrc);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender) {
	glColor3d(0, 1, 0);
	glutSolidCube(1.0);
	auxSolidCube(0.5);
	SwapBuffers(dc);

}
// ---------------------------------------------------------------------------
