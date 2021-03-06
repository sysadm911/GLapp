{**********************************************************************}
{* ����������� � ����� "OpenGL � �������� Delphi"                     *}
{* ������� �.�. softgl@chat.ru                                        *}
{**********************************************************************}

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
    procedure FormMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
  private
    DC : HDC;
    hrc: HGLRC;
  end;

var
  frmGL: TfrmGL;
  wrkX, wrkY : Integer;
  down : Boolean = False;

implementation

{$R *.DFM}

const
 {��������� ������ ����������� (�������) ����� �����������}
 ctrlpoints : Array [0..3, 0..3, 0..2] of GLFloat =
 (
    (
        (-1.5, -1.5, 4.0),
        (-0.5, -1.5, 2.0),
        (0.5, -1.5, -1.0),
        (1.5, -1.5, 2.0)),
    (
        (-1.5, -0.5, 1.0),
        (-0.5, -0.5, 3.0),
        (0.5, -0.5, 0.0),
        (1.5, -0.5, -1.0)),
    (
        (-1.5, 0.5, 4.0),
        (-0.5, 0.5, 0.0),
        (0.5, 0.5, 3.0),
        (1.5, 0.5, 4.0)),
    (
        (-1.5, 1.5, -2.0),
        (-0.5, 1.5, -2.0),
        (0.5, 1.5, 0.0),
        (1.5, 1.5, -1.0))
 );

{=======================================================================
����������� ����}
procedure TfrmGL.FormPaint(Sender: TObject);
var
 i, j : Integer;
begin
 glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

 glPushMatrix;
 glRotatef(85.0, 1.0, 1.0, 1.0);
 glColor3f (0.0, 1.0, 1.0);

 glBegin (GL_LINE_STRIP);
 For i := 0 to 30 do
   For j := 0 to 30 do
       glEvalCoord2f(i / 30, j / 30);
 glEnd;

 glPopMatrix;

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
 glEnable(GL_DEPTH_TEST);

 glEnable(GL_AUTO_NORMAL);

 glEnable(GL_COLOR_MATERIAL);

 // �������� �����
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);

 glPointSize(5.0);

 // �����������
 glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, @ctrlpoints);
 glEnable(GL_MAP2_VERTEX_3);
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
     then glOrtho(-3.0, 3.0, -3.0 * ClientHeight / ClientWidth,
                   3.0 * ClientHeight / ClientWidth, -3.0, 3.0)
     else glOrtho(-3.0 * ClientWidth / ClientHeight,
                   3.0 * ClientWidth / ClientHeight, -3.0, 3.0, -3.0, 3.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity;

 InvalidateRect(Handle, nil, False);
end;


procedure TfrmGL.FormMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  Down := True;
  wrkX := X;
  wrkY := Y;
end;

procedure TfrmGL.FormMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  Down := False;
end;

procedure TfrmGL.FormMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  If Down then begin
     glRotatef (X - wrkX, 0.0, 1.0, 0.0);
     glRotatef (Y - wrkY, 1.0, 0.0, 0.0);
     InvalidateRect(Handle, nil, False);
     wrkX := X;
     wrkY := Y;
  end;
end;

end.

