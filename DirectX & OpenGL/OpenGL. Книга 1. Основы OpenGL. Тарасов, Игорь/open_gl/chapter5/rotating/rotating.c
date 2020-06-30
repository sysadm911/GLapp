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


unsigned int photo_tex;
AUX_RGBImageRec* photo_image;


unsigned int space_tex;
AUX_RGBImageRec* space_image;




void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glFrustum(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



void CALLBACK display(void)
{
static double xRotate=0, yRotate=0, zRotate=0, radius=0;
static double dr = 0.1;
    
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );




 glEnable(GL_TEXTURE_2D);
 glColor3d(1,1,1);

 glBindTexture(GL_TEXTURE_2D, space_tex );
  glBegin(GL_QUADS);
     glTexCoord2d(0,0); glVertex3d(-5,-5, 3);
     glTexCoord2d(0,1); glVertex3d(-5, 5, 3);
     glTexCoord2d(1,1); glVertex3d( 5, 5, 3);
     glTexCoord2d(1,0); glVertex3d( 5,-5, 3);
  glEnd();



glPushMatrix();
glTranslated(0,0, radius);
glRotated(xRotate, 1, 0, 0 );
glRotated(yRotate, 0, 1, 0 );
glRotated(zRotate, 0, 0, 1 );                

 glBindTexture(GL_TEXTURE_2D, photo_tex);
   glBegin(GL_QUADS);
     glTexCoord2d(0,0); glVertex2d(-4,-4);
     glTexCoord2d(0,1); glVertex2d(-4, 4);
     glTexCoord2d(1,1); glVertex2d( 4, 4);
     glTexCoord2d(1,0); glVertex2d( 4,-4);
 glEnd();


    xRotate +=  1;
    yRotate += 10;
    zRotate +=  5;
    radius -= dr;
    if(radius<-7 || radius>3)
    {
     dr = -dr;
     radius -= 2*dr;
    }

glPopMatrix();



 glDisable(GL_TEXTURE_2D);

auxSwapBuffers();
}



void main()
{
    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Texture" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);
  
    
//    glEnable(GL_DEPTH_TEST);
    

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	photo_image = auxDIBImageLoad("photo.bmp");
	space_image = auxDIBImageLoad("space.bmp");


	glGenTextures(1, &photo_tex);
	glGenTextures(1, &space_tex);

	glBindTexture(GL_TEXTURE_2D, photo_tex );
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		         photo_image->sizeX,
				 photo_image->sizeY,
				 0, GL_RGB, GL_UNSIGNED_BYTE,
				 photo_image->data);

/*	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
		         photo_image->sizeX,
				 photo_image->sizeY,
				 GL_RGB, GL_UNSIGNED_BYTE,
				 photo_image->data);
	
*/




	glBindTexture(GL_TEXTURE_2D, space_tex );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		         space_image->sizeX,
				 space_image->sizeY,
				 0, GL_RGB, GL_UNSIGNED_BYTE,
				 space_image->data);

    auxMainLoop(display);
}
