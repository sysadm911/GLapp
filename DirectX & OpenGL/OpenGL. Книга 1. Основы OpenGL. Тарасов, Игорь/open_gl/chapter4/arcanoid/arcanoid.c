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

#include <stdlib.h> 
#include <time.h>


#define racket_w 2
#define racket_delta racket_w/2
#define initial_vilocity 0.1
#define radius 1

double x, y;
double racket_x=0;
double vx, vy;
double right = 5, left = -5, top = 5, bottom = -5;

unsigned char array[] = {
0, 0, 0, 0, 
124, 15, 128, 248, 
126, 15, 128, 248, 
127, 15, 128, 248, 
127, 143, 128, 248, 
127, 207, 128, 248, 
127, 239, 128, 248, 
127, 255, 128, 248, 
127, 255, 128, 248, 
125, 255, 128, 248, 
124, 255, 128, 248, 
124, 127, 128, 248, 
124, 63, 128, 248, 
124, 31, 192, 248, 
124, 15, 224, 248, 
124, 15, 240, 248, 
124, 15, 248, 248, 
124, 15, 252, 248, 
124, 15, 254, 248, 
124, 15, 255, 248, 
124, 15, 191, 248, 
124, 15, 159, 248, 
124, 15, 143, 248, 
124, 15, 135, 248, 
124, 15, 131, 248, 
124, 15, 129, 248, 
124, 15, 128, 248, 
128, 15, 128, 4, 
128, 15, 128, 4, 
255, 255, 255, 252, 
255, 255, 255, 252, 
255, 255, 255, 252, 
};




void CALLBACK Key_LEFT(void )
{
 if(racket_x>left)
	 racket_x -= racket_delta;
}


void CALLBACK Key_RIGHT(void )
{
 if(racket_x+racket_w<right)
	 racket_x += racket_delta;
}



int Catched()
{
 if(x>racket_x && x<racket_x+racket_w)
	return 1;
 else 
	return 0;
}



void GetNextXY()
{

  x += vx;
  y += vy;
 

  if(x-radius<left || x+radius>right)
  {
      vx = -vx;
	  x += 2*vx;
  }

  
  if(y+radius>top || (y-radius<bottom && Catched()) )
  {
      vy = -vy;
	  y += 2*vy;
  }

}



void DrawRacket()
{
 glPushMatrix();
   glTranslated(racket_x+racket_w/2, bottom, 0);
   glColor3ub(0,0,255);
   auxSolidBox(racket_w, 1.65, racket_w);
 glPopMatrix();
}


void DrawBall()
{
	glPushMatrix();
        glTranslated(x,y,0);
	    glColor3d(1,0,0);
        auxSolidSphere(radius);
    glPopMatrix();
}




void CALLBACK display(void)
{

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


   GetNextXY();
   DrawBall();
   DrawRacket();

		if(y-radius<bottom)
			auxQuit();

  auxSwapBuffers();

}




void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    



void main()
{
//	float pos[4] = {3,3,3,1};
//	float dir[3] = {-1,-1,-1};


    srand(time(0));

    vx=initial_vilocity+((double)(rand()%50))/1000.0;
    vy=initial_vilocity+((double)(rand()%50))/1000.0;

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Game --- Arcanoid" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

    auxKeyFunc(AUX_LEFT, Key_LEFT);
    auxKeyFunc(AUX_RIGHT, Key_RIGHT);


  
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_STIPPLE);


    glPolygonStipple(array); 

//    glLightfv(GL_LIGHT0, GL_POSITION, pos);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	auxMainLoop(display);
}
