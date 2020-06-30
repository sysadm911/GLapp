/*
 * (c) Copyright 1995-1999, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * Inet: itarasov@rtuis.miem.edu.ru
 * Phone: (095)942-50-97
 */


#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

int alpha=0, beta=0;

void CALLBACK mouse(AUX_EVENTREC *event)
{
static int x0,y0=-12345;

if(y0!=-12345)
{
alpha += event->data[AUX_MOUSEX] - x0;
beta += event->data[AUX_MOUSEY] - y0;
}

x0 = event->data[AUX_MOUSEX];
y0 = event->data[AUX_MOUSEY];
}

void CALLBACK Key_LEFT(void)
{
  alpha -= 5;
}

void CALLBACK Key_RIGHT(void)
{
  alpha += 5;
}


void CALLBACK Key_UP(void)
{
  beta += 5;
}

void CALLBACK Key_DOWN(void)
{
  beta -= 5;
}



void CALLBACK resize(int width,int height)
{
  glViewport(0,0,width,height);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(-5,5, -5,5, 2,12);   
  gluLookAt(0, 0, 5, 0,0,0, 0,1,0 );
  glMatrixMode( GL_MODELVIEW );
}    


void snowman()
{
  glPushMatrix();
    
	glColor3d(0.75,0.75,0.75);

	glTranslated(0,-3,0);
	auxSolidSphere(2.0);

    glTranslated(0,3,0);
	auxSolidSphere(1.5);
   
	glTranslated(0,2,0);
	auxSolidSphere(1);
   

	glColor3d(0,0,0);

	glTranslated(-0.3,0.3,1);
    auxSolidSphere(0.1); 

    glTranslated(0.6,0,0);
    auxSolidSphere(0.1); 

	glTranslated(-0.3,-0.3,0);
	glColor3d(1,0,0);
    auxSolidCone(0.3,0.5);

	glTranslated(0,0.75,-1);
    glColor3d(0,0,1);
	glRotated(-90,1,0,0);
    auxSolidCone(0.75,0.75);

  glPopMatrix();
}


void CALLBACK display(void)
{
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
  
 glPushMatrix();
   glRotated(alpha, 0,1,0);
   glRotated(beta, -1,0,0);
  //auxSolidTorus(0.5, 1);
   snowman();
 glPopMatrix();
  
  auxSwapBuffers();

}



void main()
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};
GLfloat mat_specular[] = {1,1,1,1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Controls" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

  
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    auxKeyFunc(AUX_LEFT, Key_LEFT);
    auxKeyFunc(AUX_RIGHT, Key_RIGHT);
    auxKeyFunc(AUX_UP, Key_UP);
    auxKeyFunc(AUX_DOWN, Key_DOWN);

	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSELOC, mouse);

    auxMainLoop(display);
}
