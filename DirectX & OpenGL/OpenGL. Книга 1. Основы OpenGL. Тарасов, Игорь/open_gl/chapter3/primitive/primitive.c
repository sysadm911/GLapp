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



void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



void CALLBACK display(void)
{
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

 glPointSize(2);  
  glBegin(GL_POINTS);  
	 glColor3d(1,0,0);  
	 glVertex3d(-4.5,4,0); // ������ �����  

     glColor3d(0,1,0);  
	 glVertex3d(-4,4,0);   // ������ �����  

     glColor3d(0,0,1);     //������
	 glVertex3d(-3.5,4,0);
  glEnd();
  
  glPointSize(5);  
  glBegin(GL_POINTS);  
	 glColor3d(1,0,0);  
	 glVertex3d(-2,4,0); // ������ �����  

     glColor3d(0,1,0);  
	 glVertex3d(-1,4,0);   // ������ �����  

     glColor3d(0,0,1);     //������
	 glVertex3d(0,4,0);
  glEnd();
  
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);  
  glBegin(GL_POINTS);  
	 glColor3d(1,0,0);  
	 glVertex3d(2,4,0); // ������ �����  

     glColor3d(0,1,0);  
	 glVertex3d(3,4,0);   // ������ �����  

     glColor3d(0,0,1);     //������
	 glVertex3d(4,4,0);
  glEnd();
  glDisable(GL_POINT_SMOOTH); 


glLineWidth(1); 
 glBegin(GL_LINES);
 
  glColor3d(1,0,0);
  glVertex3d(-4.5,3,0); 
  glVertex3d(-3,3,0); 

  glColor3d(0,1,0);
  glVertex3d(-3,3.3,0); 
  glVertex3d(-4,3.4,0); 
  
 glEnd();

 
 glLineWidth(3); 

 glBegin(GL_LINE_STRIP);
  glColor3d(1,0,0);
  glVertex3d(-2.7,3,0);
  glVertex3d(-1,3,0);

  glColor3d(0,1,0);
  glVertex3d(-1.5,3.3,0); 
  glColor3d(0,0,1);
  glVertex3d(-1,3.5,0); 
 
 glEnd();

 
 glLineWidth(5);
 glEnable(GL_LINE_SMOOTH); 
 glEnable(GL_LINE_STIPPLE); 
 glLineStipple(2,58360);


 glBegin(GL_LINE_LOOP);

  glColor3d(1,0,0);
  glVertex3d(1,3,0);
  glVertex3d(4,3,0);

  glColor3d(0,1,0);
  glVertex3d(3,2.7,0); 
  glColor3d(0,0,1);
  glVertex3d(2.5,3.7,0); 
 
  glEnd();

 glDisable(GL_LINE_SMOOTH);
 glDisable(GL_LINE_STIPPLE);



glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 glBegin(GL_TRIANGLES);
  glColor3d(1,0,0);
  glVertex3d(-4,2,0);
  glVertex3d(-3,2.9,0);
  glVertex3d(-2,2,0);
 glEnd();
 

glLineWidth(2);
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 glBegin(GL_TRIANGLE_STRIP);
  glColor3d(0,1,0);
  glVertex3d(1,2,0);
  glVertex3d(0,2.9,0);
  glVertex3d(-1,2,0);
  glVertex3d(0,1.1,0);
 glEnd();


 glEnable(GL_LINE_STIPPLE); 
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 glBegin(GL_TRIANGLE_FAN);
  glColor3d(0,0,1);
  glVertex3d(4,2,0);
  glVertex3d(2.6,2.8,0);
  glVertex3d(2,2,0);
  glVertex3d(3,1.1,0);
 glEnd();

 
 glDisable(GL_LINE_STIPPLE);
 
  auxSwapBuffers();

}



void main()
{
	float pos[4] = {3,3,3,1};
	float dir[3] = {-1,-1,-1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Primitives" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

  
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	auxMainLoop(display);
}
