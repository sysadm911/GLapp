/*
 * (c) Copyright 1995-2000, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * email: igor@itsoft.miem.edu.ru itarasov@rtuis.miem.edu.ru
 * Phone: (095)916-89-51 916-89-63
 */


#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <math.h>


AUX_RGBImageRec* image;

void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( -2,3,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



#define dx 0.7
#define dy 0.8

void CALLBACK display(void)
{
static double t=0;
double x,y,z;

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 glColor3d(1,1,1);



 glPushMatrix();
 glTranslated(-3,-3.5,0);


for(y=0;y<9*dy;y+=dy)

  for(x=0;x<9*dx;x+=dx)
 {
 glBegin(GL_POLYGON);
  z = sin(x+t); 
  glTexCoord2d(x/10/dx, y/10/dy); 
  glVertex3d(x,y,z);
  glTexCoord2d(x/10/dx, (y+dy)/10/dy); 
  glVertex3d(x,y+dy,z);
  z = sin(x+dx+t);
  glTexCoord2d((x+dx)/10/dx, (y+dy)/10/dy); 
  glVertex3d(x+dx,y+dy,z);
  glTexCoord2d((x+dx)/10/dx, y/10/dy); 
  glVertex3d(x+dx,y,z);
 glEnd();
  }

glPopMatrix();


 t+=0.1;
  auxSwapBuffers();

}



void main()
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};

    GLfloat mat_specular[] = {1,1,1,1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Glaux Template" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

  
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);



	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	image = auxDIBImageLoad("photo.bmp");

	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		         image->sizeX,
				 image->sizeY,
				 0, GL_RGB, GL_UNSIGNED_BYTE,
				 image->data);



 glEnable(GL_TEXTURE_2D);
// glEnable(GL_TEXTURE_GEN_S);
// glEnable(GL_TEXTURE_GEN_T);
				 
				 /*
    * Enter your cod here
    */
    auxMainLoop(display);
}
