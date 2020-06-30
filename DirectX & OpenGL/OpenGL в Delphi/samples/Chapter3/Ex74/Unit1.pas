{**********************************************************************}
{* ����������� � ����� "OpenGL � �������� Delphi"                     *}
{* ������� �.�. softgl@chat.ru                                        *}
{**********************************************************************}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OpenGL, ExtCtrls, StdCtrls;

type
  TfrmGL = class(TForm)
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);

  private
    DC : HDC;
    hrc: HGLRC;
    Angle : GLfloat;
    wrkX, wrkY : Array [0..49] of GLfloat;
    newCount, frameCount, lastCount : LongInt;
    fpsRate : GLfloat;
  protected
    procedure WMPaint(var Msg: TWMPaint); message WM_PAINT;
  end;

type
  TGLThread = class (TThread)
    protected
    procedure Execute; override;
    procedure Paint;
  end;

var
  frmGL: TfrmGL;
  GLThread : TGLThread;

implementation

uses DGLUT;

{$R *.DFM}

procedure TGLThread.Paint;
begin
  With frmGL do begin
     Angle := Angle + 0.1;
     If Angle >= 360.0 then Angle := 0.0;
     InvalidateRect(Handle, nil, False);
  end;
end;

procedure TGLThread.Execute;
begin
  repeat
     Synchronize (Paint);
  until Terminated;
end;

{=======================================================================
��������� ��������}
procedure TfrmGL.WMPaint(var Msg: TWMPaint);
var
 ps : TPaintStruct;
 i : 0..49;
begin
 BeginPaint(Handle, ps);

 // ������� ������ ����� � ������ �������
 glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

 glPushMatrix;
 glRotatef(2 * Angle, 0.0, 1.0, 0.0);  // ������� �� ����
 glRotatef(Angle, 0.0, 0.0, 1.0);  // ������� �� ����
 {���� ��������� ����� �������}
 For i := 0 to 49 do begin
  glPushMatrix;                    // ��������� �����

  glTranslatef(wrkX [i], wrkY [i], 0.0);
  glRotatef(-7.2 * i, 0.0, 0.0, 1.0); // ������� ������

  glScalef (1.0, 7.0, 1.0);
  glutSolidCube (0.1);

  glPopMatrix;                     // ��������� � �����
 end;

 glPopMatrix;

 SwapBuffers(DC);

 EndPaint(Handle, ps);

 // ���������� � ������� ���������� ������ � �������
 newCount := GetTickCount;
 Inc(frameCount);
 If (newCount - lastCount) > 1000 then  begin // ������ �������
    fpsRate := frameCount * 1000 / (newCount - lastCount);
    Caption := 'FPS - ' + FloatToStr (fpsRate);
    lastCount := newCount;
    frameCount := 0;
 end;
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
var
 i : 0..49;
begin
 DC := GetDC (Handle);
 SetDCPixelFormat(DC);
 hrc := wglCreateContext(DC);
 wglMakeCurrent(DC, hrc);
 For i := 0 to 49 do begin
      wrkX [i] := sin (Pi / 25 * i);
      wrkY [i] := cos (Pi / 25 * i);
 end;
 glClearColor (1.0, 1.0, 1.0, 1.0);

 glEnable(GL_DEPTH_TEST);// ��������� ���� �������
 // ��������� �������� ����� 0
 glEnable(GL_LIGHTING); // ��������� ������ � �������������
 glEnable(GL_LIGHT0);   // �������� �������� ����� 0
 glEnable (GL_COLOR_MATERIAL);
 glColor3f (0.0, 0.0, 1.0);
 Angle := 0;
 lastCount := GetTickCount;
 frameCount := 0;
 GLThread := TGLThread.Create (False);
end;

{=======================================================================
����� ������ ����������}
procedure TfrmGL.FormDestroy(Sender: TObject);
begin
 GLThread.Suspend;
 GLThread.Free;
 wglMakeCurrent(0, 0);
 wglDeleteContext(hrc);
 ReleaseDC (Handle, DC);
 DeleteDC (DC);
end;

procedure TfrmGL.FormResize(Sender: TObject);
begin
 glViewPort (0, 0, ClientWidth, ClientHeight);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity;
 gluPerspective(18.0, ClientWidth / ClientHeight, 7.0, 13.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity;
 glTranslatef(0.0, 0.0, -9.0);
 glRotatef(60.0, 1.0, 0.0, 1.0);
 InvalidateRect(Handle, nil, False);
end;

procedure TfrmGL.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  If Key = VK_ESCAPE then Close;
end;

end.

