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

void drawPixel(int x, int y){
    glVertex2i(x, y);
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


void midPointAlgo(int X1, int Y1, int X2, int Y2,int zone) 
{ 
    int dx= X2-X1; 
    int dy= Y2-Y1; 
    int d= 2*dy-(dx); 
    int de=2*d;
    int dne=2*(dy-dx);
    int x= X1,y=Y1; 
    drawPixel(x, y, zone);
    while (x<X2) 
    { 
        
        if (d<0) 
        	{
            x++; 
            	d+=dne;
            } 
       else
        { 
            d+= de; 
            y++; 
        } 
        drawPixel(x, y, zone);
    } 
} 


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    //DrawCircle(0,15,20);
    //glVertex2i(20,30);
    //DrawMyLine(150,150,20,20);
    drawLine(rand()%100, rand()%100, rand()%100, rand()%100);
   
    
    glEnd();
    glFlush();
    //glutSwapBuffer();
}
void drawPixel(int x, int y){
    glVertex2i(x, y);
}

int getZone(int x0, int y0, int x1, int y1){
        int dx = x1 - x0, dy = y1 - y0;
        
        if(dx>=0 && dy>=0){
            if(dx>=dy) return 0;
            else return 1;
        }
        else if(dx<0 && dy>=0){
            if(abs(dx)>=dy) return 3;
            else return 2;
        }
        else if(dx<0 && dy<0){
            if(abs(dx)>=abs(dy)) return 4;
            else return 5;
        }
        else{
            if(dx>=abs(dy)) return 7;
            else return 6;
        }
}

void drawLine(int x0, int y0, int x1, int y1){
    int zone = getZone(x0, y0, x1, y1);
   // cout<<"zone = " <<zone<<endl;
    if(zone == 0) midPointAlgo(x0, y0, x1, y1, zone);
    else if(zone == 1) midPointAlgo(y0, x0, y1, x1, zone);
    else if(zone == 2) midPointAlgo(y0, -x0, y1, -x1, zone);
    else if(zone == 3) midPointAlgo(-x0, y0, -x1, y1, zone);
    else if(zone == 4) midPointAlgo(-x0, -y0, -x1, -y1, zone);
    else if(zone == 5) midPointAlgo(-y0, -x0, -y1, -x1, zone);
    else if(zone == 6) midPointAlgo(-y0, x0, -y1, x1, zone);
    else if(zone == 7) midPointAlgo(x0, -y0, x1, -y1, zone);
}


int main (int argc, char **argv){
  glutInit (&argc, argv); // to initialize the toolkit;
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
 //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
  glutInitWindowSize (Wi, He); // sets the window size
  glutInitWindowPosition (0, 0); // sets the starting position for the window
  glutCreateWindow ("Line Drawing"); // creates the window and sets the title
  myInit(); // additional initializations as necessary
  glutReshapeFunc(reshape);
  glutDisplayFunc (display);
  glutMainLoop(); // go into a loop until event occurs
   return 0;
}

