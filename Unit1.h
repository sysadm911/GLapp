// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
// #include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <GL/glut.h>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>


struct OGL_Coord {
	float X, Y;
} mouse_OGL_Coord;


// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TRzStatusBar *RzStatusBar1;
	TRzToolbar *RzToolbar1;
	TRzPanel *RzPanel1;
	TImageList *ImageList1;
	TRzToolButton *BtnExecute;

	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnExecuteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall RzPanel1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall RzPanel1Paint(TObject *Sender);
	void __fastcall RzPanel1Resize(TObject *Sender);
	void __fastcall RzPanel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall BtnExecuteClick(TObject *Sender);

private: // User declarations
	void AddPoint(OGL_Coord P);
	void Render(GLenum mode);
	GLint DoSelect(GLint x, GLint y);
	void Texture_Init();
	void FindNormal(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z);
	void OpenGL_Draw();
	void OpenGL_Init();

	HWND hwnd;
	HDC hdc;
	HGLRC hrc;

	GLint CNormal[3];
	GLuint SelectBuf[4]; // ������ ��� ������ ������
	GLint vp[4]; // ������ ������� �������
	GLint hit;

	GLuint TextureID;
	GLubyte *TextureData;
	float rotation;

	void InitDisplay(HWND hwnd);

public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
