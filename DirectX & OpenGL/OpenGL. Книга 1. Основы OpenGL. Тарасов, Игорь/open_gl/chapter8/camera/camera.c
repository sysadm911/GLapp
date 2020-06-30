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


#define M_PI        3.14159265358979323846


float delta=0.1;
float x=0,y=0,z=5; 


void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( x,y,z, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    


void Polar2Normal(float a, float b, float r, 
				  float* x, float* y, float* z)
{
*x = r*cos(a)*cos(b);
*y = r*sin(a);
*z = -r*cos(a)*sin(b);
}

void Normal2Polar(float x, float y, float z, float pol[3]) 
{
pol[2] = sqrt(x*x+y*y+z*z);
pol[0] = asin(y/pol[2]);
pol[1] = acos(x/sqrt(x*x+z*z));
if(z>0)
 pol[1] = 2*M_PI - pol[1];
}


void CALLBACK Key_LEFT(void)
{
float pol[3];

  Normal2Polar(x, y, z, pol);
  pol[1] -= delta;
  Polar2Normal(pol[0], pol[1], pol[2], &x, &y, &z);
  resize(400,400);  
}

void CALLBACK Key_RIGHT(void)
{
float pol[3];

  Normal2Polar(x, y, z, pol);
  pol[1] += delta;
  Polar2Normal(pol[0], pol[1], pol[2], &x, &y, &z);
  resize(400,400);  
}

void CALLBACK Key_DOWN(void)
{
float pol[3];

  Normal2Polar(x, y, z, pol);
  pol[0] -= delta;
  Polar2Normal(pol[0], pol[1], pol[2], &x, &y, &z);
  resize(400,400);  
}

void CALLBACK Key_UP(void)
{
float pol[3];

  Normal2Polar(x, y, z, pol);
  pol[0] += delta;
  Polar2Normal(pol[0], pol[1], pol[2], &x, &y, &z);
  resize(400,400);  
}





void CALLBACK display(void)
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();

    glTranslated(0.5,4,0);
	glColor3d(0,0,1);
    auxSolidCube(1);      // куб

    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxSolidBox(1,0.75,0.5);  // коробка 

	glTranslated(0,-2,0);
	glColor3d(0,1,1);
    auxSolidTorus(0.2,0.5);         // тор

    glTranslated(0,-2,0);
	glColor3d(1,0,0);
    auxSolidCylinder(0.5,1); // цилиндер


    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxSolidCone(1,1);     // конус

    glTranslated(2,8,0);
	glColor3d(1,0,1);
    auxSolidIcosahedron(1); // многогранники

    glTranslated(0,-2,0);
	glColor3d(1,1,1);
    auxSolidOctahedron(1);

    glTranslated(0,-2,0);
	glColor3d(0,1,1);
    auxSolidTeapot(0.7);       // рисует чайник   

    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxSolidTetrahedron(1);

    glTranslated(0,-2,0);
	glColor3d(1,1,0);
    auxSolidDodecahedron(1);


	glTranslated(-6,8,0);
	glColor3d(0,0,1);
    auxWireCube(1);      // куб

    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxWireBox(1,0.75,0.5);  // коробка 

	glTranslated(0,-2,0);
	glColor3d(0,1,1);
    auxWireTorus(0.2,0.5);         // тор

    glTranslated(0,-2,0);
	glColor3d(1,0,0);
    auxWireCylinder(0.5,1); // цилиндер


    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxWireCone(1,1);     // конус

    glTranslated(2,8,0);
	glColor3d(1,0,1);
    auxWireIcosahedron(1); // многогранники

    glTranslated(0,-2,0);
	glColor3d(1,1,1);
    auxWireOctahedron(1);

    glTranslated(0,-2,0);
	glColor3d(0,1,1);
    auxWireTeapot(0.7);       // рисует чайник   

    glTranslated(0,-2,0);
	glColor3d(0,1,0);
    auxWireTetrahedron(1);

    glTranslated(0,-2,0);
	glColor3d(1,1,0);
    auxWireDodecahedron(1);

  glPopMatrix();


    auxSwapBuffers();
}



void main()
{
	float pos[4] = {3,3,3,1};
	float dir[3] = {-1,-1,-1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Shapes" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);

  
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    auxKeyFunc(AUX_LEFT, Key_LEFT);
    auxKeyFunc(AUX_RIGHT, Key_RIGHT);
    auxKeyFunc(AUX_UP, Key_UP);
    auxKeyFunc(AUX_DOWN, Key_DOWN);

    auxMainLoop(display);
}
