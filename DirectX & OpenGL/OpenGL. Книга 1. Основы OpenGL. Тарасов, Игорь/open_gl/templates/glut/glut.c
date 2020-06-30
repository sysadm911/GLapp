/*
 * (c) Copyright 1995-2000, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * email: igor@itsoft.miem.edu.ru itarasov@rtuis.miem.edu.ru
 * Phone: (095)916-89-51 916-89-63
 */



#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



void resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



void display(void)
{
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  	/* remove next tree lines
	 * and enter your code here
	 */
        glTranslated(0.01,0,0);
	    glColor3d(1,0,0);
        glutSolidSphere(1, 15,15);

  
  glutSwapBuffers();

}



void main()
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};

    GLfloat mat_specular[] = {1,1,1,1};

    glutInitWindowPosition(50, 10);
	glutInitWindowSize(400, 400);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    glutCreateWindow( "GLUT Template" );
    glutIdleFunc(display);
	glutDisplayFunc(display);
    glutReshapeFunc(resize);

  
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);


    /*
    * Enter your cod here
    */
    glutMainLoop();
}
