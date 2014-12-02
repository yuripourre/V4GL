#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "Camera.h"
#include "Camera.cpp"

#include "filtros/FiltroT.hpp"
#include "filtros/FiltroFake.hpp"
#include "filtros/FiltroSkin.hpp"
#include "filtros/FiltroFloodFill.hpp"

Camera* cam;

Filtro* filtro;

void moveMouse(int x, int y){
    
    Display* dpy;
    Window root_window;
    
    dpy = XOpenDisplay(0);
    
    root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);

    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);

    XFlush(dpy);
    
}

void display()
{
    cam->mainLoop();
      
    filtro->setImage(cam->dst);
    filtro->filtra();
    
    glDrawPixels(cam->width,cam->height,GL_RGB,GL_FLOAT,filtro->getPixels());

    glFlush();

    glutSwapBuffers();
  
}

int main(int argc, char** argv) {
	
	cam = new Camera(640, 480,"/dev/video0");
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(cam->width, cam->height);
	glutCreateWindow("OpenGL V4l demo");
	
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouse_button);
	//glutMotionFunc(mouse_motion);
	//glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	  
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	//filtro = new FiltroFake(cam->width,cam->height);
	//filtro = new FiltroSkin(cam->width,cam->height);
	//filtro = new FiltroT(cam->width,cam->height);
	filtro = new FiltroFloodFill(cam->width,cam->height);
	  
	cam->deviceOpen();
	cam->deviceInit();
	// start capturing
	cam->captureStart();
	
	//moveMouse(300,200);
	
	//display();
	glutMainLoop();
	
	// stop capturing
	cam->captureStop();
	// close device
	cam->deviceUninit();
	cam->deviceClose();


	delete cam;
	delete filtro;

}
