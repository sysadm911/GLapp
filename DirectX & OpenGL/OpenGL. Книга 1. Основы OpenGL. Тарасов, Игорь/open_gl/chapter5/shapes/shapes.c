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


AUX_RGBImageRec* photo_image;


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

glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

quadObj = gluNewQuadric(); 
gluQuadricTexture(quadObj, GL_TRUE);
gluQuadricDrawStyle(quadObj, GLU_FILL); 
glColor3d(1,1,1);

glRotated(5, 0,1,0);


glPushMatrix();
 glRotated(-90, 1,0,0);
  gluSphere(quadObj, 3, 16, 16); 
glPopMatrix(); 


 
gluDeleteQuadric(quadObj);
auxSwapBuffers();
}



void main()
{
    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Shapes" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);
  
    
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	photo_image = auxDIBImageLoad("photo.bmp");
	

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		         photo_image->sizeX,
				 photo_image->sizeY,
				 0, GL_RGB, GL_UNSIGNED_BYTE,
				 photo_image->data);


    auxMainLoop(display);
}
