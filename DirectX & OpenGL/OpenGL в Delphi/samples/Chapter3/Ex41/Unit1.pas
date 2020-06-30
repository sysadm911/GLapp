{**********************************************************************}
{* ����������� � ����� "OpenGL � �������� Delphi"                     *}
{* ������� �.�. softgl@chat.ru                                        *}
{**********************************************************************}

{/*
 * (c) Copyright 1993, Silicon Graphics, Inc.
 *               1993-1995 Microsoft Corporation
 *
 * ALL RIGHTS RESERVED
 */}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OpenGL;

type
  TfrmGL = class(TForm)
    procedure FormCreate(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormResize(Sender: TObject);
  private
    DC : HDC;
    hrc: HGLRC;
  end;

var
  frmGL: TfrmGL;

implementation

{$R *.DFM}

const
 ctrlpoints : Array [0..3, 0..2] of GLfloat =
       (( -4.0, -4.0, 0.0), (-2.0, 4.0, 0.0),
	(2.0, -4.0, 0.0), (4.0, 4.0, 0.0));

{=======================================================================
����������� ����}
procedure TfrmGL.FormPaint(Sender: TObject);
var
 i : GLint;
begin
 glClear (GL_COLOR_BUFFER_BIT);      // ������� ������ �����

 glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_LINE_STRIP);
   For i := 0 to 30 do
     glEvalCoord1f(i / 30.0);
 glEnd;
 // The following code displays the control points as dots.
 glPointSize(5.0);
 glColor3f(1.0, 1.0, 0.0);
 glBegin(GL_POINTS);
   For i := 0 to 3 do
     glVertex3fv(@ctrlpoints[i][0]);
 glEnd;

 SwapBuffers(DC);
end;

{=======================================================================
������ �������}
procedure SetDCPixelFormat (hdc : HDC);
var
 pfd : TPixelFormatDescriptor;
 nPixelFormat : Integer;
begin
 FillChar (pfd, SizeOf (pfd), 0);
 pfd.dwFlags  := PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER;
 nPixelFormat := ChoosePixelFormat (hdc, @pfd);
 SetPixelFormat (hdc, nPixelFormat, @pfd);
end;

{=======================================================================
�������� �����}
procedure TfrmGL.FormCreate(Sender: TObject);
begin
 DC := GetDC (Handle);
 SetDCPixelFormat(DC);
 hrc := wglCreateContext(DC);
 wglMakeCurrent(DC, hrc);
 glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, @ctrlpoints);
 glEnable(GL_MAP1_VERTEX_3);
end;

{=======================================================================
����� ������ ����������}
procedure TfrmGL.FormDestroy(Sender: TObject);
begin
 wglMakeCurrent(0, 0);
 wglDeleteContext(hrc);
 ReleaseDC (Handle, DC);
 DeleteDC (DC);
end;

procedure TfrmGL.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
 If Key = VK_ESCAPE then Close;
end;

procedure TfrmGL.FormResize(Sender: TObject);
begin
 glViewport(0, 0, ClientWidth, ClientHeight);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity;
 If ClientWidth <= ClientHeight
   then glOrtho(-5.0, 5.0, -5.0*ClientHeight / ClientWidth,
               5.0*ClientHeight / ClientWidth, -5.0, 5.0)
   else glOrtho(-5.0*ClientWidth / ClientHeight,
               5.0*ClientWidth / ClientHeight, -5.0, 5.0, -5.0, 5.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity;

 InvalidateRect(Handle, nil, False);
end;


end.

