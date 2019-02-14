#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLUT32.lib")
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

using namespace std;

int Wi=640, He=480;

void myInit (void);
void display(void);
void reshape (int w, int h);

void myInit (void){
    glClearColor(0.0, 0.0, 0.0,1.0);
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D (-Wi/2, Wi/2-1, -He/2, He/2-1); // size of projection plane (origin at the center)
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

//void DrawMyCircle(float x, float y, float r)

void DrawMyLine(int x1, int y1, int i, int ii)
{
	glBegin(GL_LINE_LOOP);
    for ( ; i<x1 && ii<y1 ; i++,ii++)
	{
		glVertex2f(i,ii);
	}
    glEnd();
}


void midPointAlgo(int X1, int Y1, int X2, int Y2) 
{ 
    int dx = X2-X1; 
    int dy = Y2 - Y1; 
    int d = dy - (dx/2); 
    int x = X1, y = Y1; 
 
    while (x < X2) 
    { 
        x++; 
        if (d < 0) 
            d = d + dy; 
       else
        { 
            d += (dy - dx); 
            y++; 
        } 
        glVertex2f(x,y);
    } 
} 


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    //DrawCircle(0,15,20);
    //glVertex2i(20,30);
    //DrawMyLine(150,150,20,20);
    for (int i=0;i<50;i++)
    {
    	glColor3f(rand()%256, rand()%256, rand()%256);
      midPointAlgo(rand()%100,rand()%100,rand()%100,rand()%100);	
    }
    glEnd();
    glFlush();
}


int main (int argc, char **argv){
  glutInit (&argc, argv); // to initialize the toolkit;
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
  glutInitWindowSize (Wi, He); // sets the window size
  glutInitWindowPosition (0, 0); // sets the starting position for the window
  glutCreateWindow ("Line Drawing"); // creates the window and sets the title
  myInit(); // additional initializations as necessary
  glutReshapeFunc(reshape);
  glutDisplayFunc (display);
  glutMainLoop(); // go into a loop until event occurs
   return 0;
}

