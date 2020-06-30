
import gl4java.GLContext;
import gl4java.awt.GLCanvas;
import gl4java.awt.GLAnimCanvas;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import java.applet.*;


class BaseGL extends GLAnimCanvas
{

public BaseGL(int w, int h){super(w, h);}
public void preInit(){doubleBuffer = true;}

public void init() 
{
gl.glMatrixMode(GL_PROJECTION);
gl.glLoadIdentity();
gl.glOrtho(-5,5,-5,5,2,12);
glu.gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
gl.glMatrixMode(GL_MODELVIEW);
glj.gljCheckGL();
glj.gljMakeCurrent(false);
}


public void display()
{
 gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  
 gl.glRotated(5, 0,0,1);
 gl.glLineWidth(5);


 gl.glBegin(GL_LINES);

   gl.glColor3d(1,0,0);   
   gl.glVertex2d(-2,0);
   gl.glVertex2d(2,0);

   gl.glColor3d(0,1,0);   
   gl.glVertex2d(0,-2);
   gl.glVertex2d(0,2);

   gl.glColor3d(0,0,1);   
   gl.glVertex3d(0,0,-2);
   gl.glVertex3d(0,0,2);
 gl.glEnd();

glj.gljSwap();
}//display

}



public class BaseApp extends Applet // implements ActionListener
{
BaseGL baseGL = null;

String gljLib=null;
String glLib=null;
String gluLib=null;

public void init()
{
 if(GLContext.loadNativeLibraries(gljLib, glLib, gluLib)==false)
  System.out.println("could not load native libs:"+
		     gljLib + ", " + glLib + ", " + gluLib);
 else 
  System.out.println("load native libs:"+
	        gljLib + ", " + glLib + ", " + gluLib);


 setLayout(null);
 setSize(570,450);


 baseGL = new BaseGL(150,150);
 baseGL.setBounds(120,0,450,450);
 add(baseGL);
} 


public void start()
{
baseGL.start();
}

public void stop()
{
baseGL.stop();
}

public void destroy(){
		       baseGL.stop();
		       baseGL.cvsDispose();
                      }

}
