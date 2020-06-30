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
GLUquadricObj *quadObj; 

 quadObj = gluNewQuadric(); 
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



glPushMatrix();
 
 // spheres
 glTranslated(-4,4,0);
 glColor3d(1,0,0);
 gluQuadricDrawStyle(quadObj, GLU_FILL); 
 gluSphere(quadObj, 0.5, 5, 5); 
 
 glTranslated(1.5,0,0);
 glColor3d(0,1,0);
 gluQuadricDrawStyle(quadObj, GLU_LINE); 
 gluSphere(quadObj, 0.75, 10, 10); 

 glTranslated(2,0,0);
 glColor3d(0,0,1);
 gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE); 
 gluSphere(quadObj, 1, 15, 15); 

 glTranslated(3,0,0);
 glColor3d(0,1,1);
 gluQuadricDrawStyle(quadObj, GLU_POINT); 
 gluSphere(quadObj, 1.25, 20, 20); 

 

  //cylinders
glPushMatrix(); 

 glTranslated(-6.5,-3.3,0);
 glRotated(45,-1,0,0);

 glColor3d(1,0,0);
 gluQuadricDrawStyle(quadObj, GLU_FILL); 
 gluCylinder(quadObj, 0.5, 1, 2, 5, 5); 
 
 glTranslated(2,0,0);
 glColor3d(0,1,0);
 gluQuadricDrawStyle(quadObj, GLU_LINE); 
 gluCylinder(quadObj, 1, 0.5, 2, 10, 10); 

 glTranslated(2.5,0,0);
 glColor3d(0,0,1);
 gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE); 
 gluCylinder(quadObj, 0.5, 1, 2, 15, 15); 

 glTranslated(3,0,0);
 glColor3d(0,1,1);
 gluQuadricDrawStyle(quadObj, GLU_POINT); 
 gluCylinder(quadObj, 1, 1.25, 1.5, 10, 10); 

glPopMatrix(); 



 //disks
 glTranslated(-6.5,-5,0);
 glColor3d(1,0,0);
 gluQuadricDrawStyle(quadObj, GLU_FILL); 
 gluDisk(quadObj, 0.3, 0.5, 5, 5); 
 
 glTranslated(1.5,0,0);
 glColor3d(0,1,0);
 gluQuadricDrawStyle(quadObj, GLU_LINE); 
 gluDisk(quadObj, 0.5, 0.75, 10, 10); 

 glTranslated(2,0,0);
 glColor3d(0,0,1);
 gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE); 
 gluDisk(quadObj, 0.75, 1, 15, 15); 

 glTranslated(3,0,0);
 glColor3d(0,1,1);
 gluQuadricDrawStyle(quadObj, GLU_POINT); 
 gluDisk(quadObj, 1, 1.25, 20, 20); 

 

 //partial disks
 glTranslated(-6.5,-2.8,0);
 glColor3d(1,0,0);
 gluQuadricDrawStyle(quadObj, GLU_FILL); 
 gluPartialDisk(quadObj, 0.3, 0.5, 5, 5, 30, 60); 
 
 glTranslated(1.5,0,0);
 glColor3d(0,1,0);
 gluQuadricDrawStyle(quadObj, GLU_LINE); 
 gluPartialDisk(quadObj, 0.5, 0.75, 10, 10, 60, 100); 

 glTranslated(2,0,0);
 glColor3d(0,0,1);
 gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE); 
 gluPartialDisk(quadObj, 0.75, 1, 15, 15, 90, 200); 

 glTranslated(3,0,0);
 glColor3d(0,1,1);
 gluQuadricDrawStyle(quadObj, GLU_POINT); 
 gluPartialDisk(quadObj, 1, 1.25, 20, 20, 180, 300); 



glPopMatrix();


gluDeleteQuadric(quadObj);
auxSwapBuffers();
}



void main()
{
	float pos[4] = {3,3,3,1};
	float dir[3] = {-1,-1,-1};

 
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);


    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Quadric" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);
    auxMainLoop(display);
}
