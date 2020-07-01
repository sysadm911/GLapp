// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
#pragma comment (lib, "glaux.lib")
TForm1 *Form1;

GLint CNormal[3];
GLuint SelectBuf[4]; // ������ ��� ������ ������
GLint vp[4]; // ������ ������� �������
GLint hit;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {

	rotation = 0;
}

// ---------------------------------------------------------------------------
void TForm1::InitDisplay(HWND hwnd) {
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat = 0;
	hdc = GetDC(hwnd);
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);
}

// ---------------------------------------------------------------------------
void TForm1::OpenGL_Init() {

	glViewport(0, 0, RzPanel1->Width, RzPanel1->Height);
	glGetIntegerv(GL_VIEWPORT, vp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(-2, 2, -2.0*RzPanel1->Width / RzPanel1->Height, 2.0*RzPanel1->Width / RzPanel1->Height, -2, 2);
	// gluPerspective(45.0, RzPanel1->Width / RzPanel1->Height, 0.1, 100.0);
	// gluOrtho2D(-10., 10., -10., 10.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glSelectBuffer(4, SelectBuf); // �������� ������ ������

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	InitDisplay(RzPanel1->Handle);
	OpenGL_Init();

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender) {
	wglMakeCurrent(0, 0);
	wglDeleteContext(hrc);
	delete[]TextureData;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RzPanel1Resize(TObject *Sender) {
	glViewport(0, 0, RzPanel1->Width, RzPanel1->Height); // ����� ������� ������� ������ � ������������� ��������������
	glGetIntegerv(GL_VIEWPORT, vp);
	glRenderMode(GL_RENDER);
	InvalidateRect(Handle, 0, true);

}

// ---------------------------------------------------------------------------
void TForm1::OpenGL_Draw() {

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender) {
	OpenGL_Draw();
	glLoadIdentity;
	glClear(GL_COLOR_BUFFER_BIT);
	Render(GL_SELECT);
	SwapBuffers(hdc);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnExecuteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
	rotation += 5;
	InvalidateRect(Handle, 0, false);
}

// ---------------------------------------------------------------------------
void TForm1::Render(GLenum mode) {
	// ������� �����������
	if (mode == GL_SELECT)
		glLoadName(1); // ������� ��� ������ 1
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(-0.1, 0);
	glEnd();

	// ����� �����������
	if (mode == GL_SELECT)
		glLoadName(2); // ������� ��� ������ 2
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();
}

// ---------------------------------------------------------------------------
GLint TForm1::DoSelect(GLint x, GLint y) {

	GLint hits;

	glRenderMode(GL_SELECT); // �������� ����� ������
	// ����� ������ ����� ��� ������ ��������� ������
	glInitNames(); // ������������� ����� ����
	glPushName(0); // ��������� ����� � ���� ����

	glLoadIdentity();
	gluPickMatrix(x, RzPanel1->Height - y, 2, 2, vp);

	Render(GL_SELECT); // ������ ������� � ����������� ��������

	hits = glRenderMode(GL_SELECT);

	if (hits <= 0)
		return -1;
	else
		return SelectBuf[(hits - 1) * 4 + 3];
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RzPanel1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {

	hit = DoSelect(X, Y); // ����� ������� ��� ��������
	switch (hit) {
	case -1:
		ShowMessage("������ �����");
		break;
	case 1:
		ShowMessage("������� �����������");
		break;
	case 2:
		ShowMessage("����� �����������");
		break;
	}

}
// ---------------------------------------------------------------------------

void TForm1::FindNormal(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z) {
	const int x = 0, y = 1, z = 2;
	double temp_v1[3], temp_v2[3], temp_length;

	temp_v1[x] = v1x - v2x;
	temp_v1[y] = v1y - v2y;
	temp_v1[z] = v1z - v2z;

	temp_v2[x] = v2x - v3x;
	temp_v2[y] = v2y - v3y;
	temp_v2[z] = v2z - v3z;

	// calculate cross product
	CNormal[x] = temp_v1[y] * temp_v2[z] - temp_v1[z] * temp_v2[y];
	CNormal[y] = temp_v1[z] * temp_v2[x] - temp_v1[x] * temp_v2[z];
	CNormal[z] = temp_v1[x] * temp_v2[y] - temp_v1[y] * temp_v2[x];

	// normalize normal
	temp_length = (CNormal[x] * CNormal[x]) + (CNormal[y] * CNormal[y]) + (CNormal[z] * CNormal[z]);

	temp_length = temp_length * temp_length;

	// prevent n/0
	if (temp_length == 0)
		temp_length = 1;

	CNormal[x] /= temp_length;
	CNormal[y] /= temp_length;
	CNormal[z] /= temp_length;
}

// ---------------------------------------------------------------------------

void TForm1::Texture_Init() {
	int i = 0;
	TextureData = new GLubyte[128 * 128 * 3]; // make room for a 128x128 RGB texture
	while (i < 128 * 128 * 3) {
		TextureData[i] = 255;
		TextureData[i + 1] = 0;
		TextureData[i + 2] = 0;
		i = i + 3;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID); // now use it

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping of Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping of Texture

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);

	glBindTexture(GL_TEXTURE_2D, TextureID);

}

// ---------------------------------------------------------------------------
