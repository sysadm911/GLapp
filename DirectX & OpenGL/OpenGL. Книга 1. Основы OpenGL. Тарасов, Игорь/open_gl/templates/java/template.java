/*
 * (c) Copyright 1995-1999, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * Inet: itarasov@rtuis.miem.edu.ru
 * Phone: (095)942-50-97
 */

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import com.hermetica.magician.*;
import com.hermetica.util3d.*;


public class template extends Applet implements GLEventListener
{
    private CoreGL gl_ = new CoreGL();
    private CoreGLU glu_ = new CoreGLU();
    private GLComponent glc = null;
 
    int width = 500;

public void init()
{  
        glc = (GLComponent)GLDrawableFactory.createGLComponent(width, width);
        add( "Center", glc );
	
        /** Setup the context capabilities */
        GLCapabilities cap = glc.getContext().getCapabilities();
        cap.setDoubleBuffered(GLCapabilities.DOUBLEBUFFER);


        /** Register the GLEventListener with the GLComponent */
        glc.addGLEventListener(this);

        /** Initialize the component */
        glc.initialize();
        glc.start();
}

    
    
public void initialize( GLDrawable component ) 
{
//	float pos[] = {3,3,3,1};
//	float dir[] = {-1,-1,-1};

        gl_.glClearColor( 1.0f, 1.0f, 0.796875f, 1.0f );
        gl_.glShadeModel( GL.GL_SMOOTH );
        gl_.glEnable(GL.GL_ALPHA_TEST);
        gl_.glEnable(GL.GL_DEPTH_TEST);     
        gl_.glEnable(GL.GL_COLOR_MATERIAL);
        gl_.glEnable(GL.GL_LIGHTING);
        gl_.glEnable(GL.GL_LIGHT0);
        gl_.glEnable(GL.GL_BLEND);
        gl_.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);

//    gl_.glLightfv(GL.GL_LIGHT0, GL.GL_POSITION, pos);
//    gl_.glLightfv(GL.GL_LIGHT0, GL.GL_SPOT_DIRECTION, dir);
}


boolean first=true;




public void reshape( GLDrawable component, int x, int y,
                         int width, int height) 
{

        gl_.glViewport( component, 0, 0, height, height);
        gl_.glMatrixMode( GL.GL_PROJECTION );
        gl_.glLoadIdentity();
	gl_.glOrtho(-5,5,-5,5,2,12);
        glu_.gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
        gl_.glMatrixMode( GL.GL_MODELVIEW );
}





public void display( GLDrawable component ) 
{
gl_.glClear( GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT );


//       gl_.glTranslated(0.01,0,0);
       gl_.glColor3d(0,1,0);
       shapes.solidSphere(0.6, 16, 16);
     
}



public void stop() 
{
if(glc.isRunning())
 glc.suspend();
}

public void start()
{
if(glc.isRunning())
 glc.resume();
}

public void destroy()
{
glc.destroy();
}
    
public GL getGL()
{
return gl_;
}

}




