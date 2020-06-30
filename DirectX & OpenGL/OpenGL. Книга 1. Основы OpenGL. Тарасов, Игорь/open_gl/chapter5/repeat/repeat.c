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
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



void CALLBACK display(void)
{
    
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );




 glEnable(GL_TEXTURE_2D);
 glColor3d(1,1,1);

 glBindTexture(GL_TEXTURE_2D, space_tex );
  glBegin(GL_QUADS);
     glTexCoord2d(0,0); glVertex3d(-5,-5, -0.1);
     glTexCoord2d(0,1); glVertex3d(-5, 5, -0.1);
     glTexCoord2d(1,1); glVertex3d( 5, 5, -0.1);
     glTexCoord2d(1,0); glVertex3d( 5,-5, -0.1);
  glEnd();



 glBindTexture(GL_TEXTURE_2D, photo_tex);
   glBegin(GL_QUADS);
     glTexCoord2d(0,0); glVertex2d(-4,-4);
     glTexCoord2d(0,2); glVertex2d(-4, 4);
     glTexCoord2d(3,2); glVertex2d( 4, 4);
     glTexCoord2d(3,0); glVertex2d( 4,-4);
 glEnd();




 glDisable(GL_TEXTURE_2D);

auxSwapBuffers();
}



void main()
{
float pos[4] = {3,3,3,1};
float dir[3] = {-1,-1,-1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Texture" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);
  
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    


    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	photo_image = auxDIBImageLoad("photo.bmp");
	space_image = auxDIBImageLoad("space.bmp");


	glGenTextures(1, &photo_tex);
	glGenTextures(1, &space_tex);

	glBindTexture(GL_TEXTURE_2D, photo_tex );
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


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
