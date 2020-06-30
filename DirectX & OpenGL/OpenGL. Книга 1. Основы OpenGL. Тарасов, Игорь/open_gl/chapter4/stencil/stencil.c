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
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


 // разрешаем тест трафарета
 glEnable(GL_STENCIL_TEST);

 // рисуем куб и заполняем буффер трафарета единицами
 // в том месте, где рисуется куб
 glStencilFunc(GL_ALWAYS, 1, 0);
 glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
 auxSolidCube(2.5);

 // заполняем буффер трафарета двойками
 // в том месте, где сфера закрывает куб
 glStencilFunc(GL_ALWAYS, 2, 0);
 glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
 auxSolidSphere(1.5);

 // очищаем буфферы цвета и глубины
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// запрещаем тест трафарета и рисуем красную сферу
glDisable(GL_STENCIL_TEST);
glColor3d(1,0,0);
auxSolidSphere(0.5);
//синий тор
glColor3d(0,0,1);
auxSolidTorus(0.15, 0.6);
// зеленый тор, повернутый на 90 градусов относительно синего
glColor3d(0,1,0);
glPushMatrix();
glRotated(90, 1,0,0);
auxSolidTorus(0.15, 0.6);
glPopMatrix();

 // разрешаем тест трафарета и рисуем дырявый куб
 glEnable(GL_STENCIL_TEST);
 glStencilFunc(GL_EQUAL, 1, 255);
 glColor3d(1,1,1);
 auxSolidCube(2.5);

 // вращаем сцену
glRotated(3, 1,0,0);
glRotated(5, 0,1,0);
glRotated(7, 0,0,1);

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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    /*
    * Enter your cod here
    */
    auxMainLoop(display);
}
