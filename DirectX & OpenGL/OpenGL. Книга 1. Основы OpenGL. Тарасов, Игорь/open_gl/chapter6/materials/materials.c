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
GLfloat front_color[] = {0,1,0,1};
GLfloat back_color[] = {0,0,1,1};
GLfloat front_emission[] = {1,1,0,1};
GLfloat back_emission[] = {0,0,1,1};

quadObj = gluNewQuadric(); 

glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
glMaterialfv(GL_BACK, GL_DIFFUSE, back_color);

//glMaterialfv(GL_FRONT, GL_EMISSION, front_emission);
//glMaterialfv(GL_BACK, GL_EMISSION, back_emission);


glPushMatrix();
 glRotated(110, -1,1,0);
 gluCylinder(quadObj, 1, 0.5, 2, 10, 10); 
glPopMatrix();

gluDeleteQuadric(quadObj);
auxSwapBuffers();
}



void main()
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};

    GLfloat mat_specular[] = {1,1,1,1 };

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Glaux Template" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

  
    glEnable(GL_DEPTH_TEST);

//  glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);


	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


    auxMainLoop(display);
}
