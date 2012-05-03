/*
Bressenhams MPLA for any line 
K Sai Gokul
2008B3A7375H
*/

#define GLUT_DISABLE_ATEXIT_HACK    //to disable makefile errors
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <windows.h>
const int WIN_HEIGHT=480.0; // set the window 
const int WIN_WIDTH=640.0;  // dimensions
int a0=-320,b0=0,a1=320,b1=240;    //set the initial and final points x belongs to[-320,320] y=[-240,240]

void myInit(void)
{
     glClearColor(1.0,1.0,1.0,1.0); //set bg color
     glColor3f(0.0f,0.0f,0.0f);     //set RGB values for the pixel color
     glPointSize(3.0);              //set point sizze
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,(GLdouble) WIN_WIDTH,0.0,(GLdouble) WIN_HEIGHT);
}

void bressenhams(void)
{ 
     glClear(GL_COLOR_BUFFER_BIT);    //clear screen
     
     void drawLine(GLint p1,GLint q1,GLint p2,GLint q2) 	//draws the coordinate axis in +x,-x,+y,-y axes in order to allow easy viewing of negative values for x&y
     {
          glBegin(GL_LINES);
          glVertex2i(p1,q1);
          glVertex2i(p2,q2);
          glEnd();
          glFlush();
     
     }
     int W=WIN_WIDTH/2;
     int H=WIN_HEIGHT/2;
     drawLine(W,0,W,WIN_HEIGHT);				//draws the y axis
     drawLine(0,H,WIN_WIDTH,H);				//draws the x axis
     
     int x0,y0,x1,y1;
     float m;                            
     
     
     x0=a0+320;                          //sacling points p1 and p2
     x1=a1+320;
     y0=b0+240;
     y1=b1+240;
     if(x0>x1)						// checking if the initial point x0,y0 is to the left .and if not it swaps the points.
     {
             int temp=x1;
             x1=x0;
             x0=temp;
             temp=y1;
             y1=y0;
             y0=temp;
     
     }
     
     m=(float)(y1-y0)/(float)(x1-x0);  // calculates the slope m
      void drawDot(GLint x,GLint y)  //function definition for drawing a pixel at specified x and y values
     {
     glBegin(GL_POINTS);
          glVertex2i(x,y);
     glEnd();
     }
     
     if(m>0 && m<=1)                 //if slope lies b/w (0,1]
     {
            
     int dy,dx,d,dE,dNE;	
     dy=y1-y0;
     dx=x1-x0;
     d=2*dy-dx;
     dE=2*dy;
     dNE=2*(dy-dx);
          
     drawDot(x0,y0);               //draws the initial point
     drawDot(x1,y1); 
     int x=x0,y=y0;
     
     while(x < x1)					//loop starts for the algorithm
     {
                if(d<=0)          // select East 
                {
                        d=d+dE;
                        }
                else              //select North East
                {
                    d=d+dNE;
                    y++;
                    }
                x++;              //increment of x value after evry iteration
                drawDot(x,y);
     
     }
     }
     
     
     else if(m<=0 && m>-1)        //if slope lies b/w (-1,0]
     {
          int dy,dx,d,dE,dSE;	
     dy=y1-y0;
     dx=x1-x0;
     d=2*dy+dx;
     dE=2*dy;
     dSE=2*(dy+dx);
     
     drawDot(x0,y0);               //draws the initial point
     drawDot(x1,y1); 
     int x=x0,y=y0;
     
     while(x < x1)					//loop starts for the algorithm
     {
                if(d>=0)          // select East 
                {
                        d=d+dE;
                        }
                else              //select South East
                {
                    d=d+dSE;
                    y--;
                    }
                x++;              //increment of x value after evry iteration
                drawDot(x,y);
     
     }
     }
     
       else if(m<=-1)             //if slope lies less than equal to -1
     {
     int dy,dx,d,dS,dSE;	
     dy=y1-y0;
     dx=x1-x0;
     d=dy+2*dx;
     dS=2*dx;
     dSE=2*(dy+dx);
     
     drawDot(x0,y0);               //draws the initial point
     drawDot(x1,y1); 
     int x=x0,y=y0;
     
     while(y>y1)					//loop starts for the algorithm
     {
                if(d<0)          // select South
                {
                        d=d+dS;
                        }
                else              //select South East
                {
                    d=d+dSE;
                    x++;
                    }
                y--;              //decrement of y value after evry iteration
                drawDot(x,y);
     
     }
     }
     
       else if(m>1)               //if slope is greater than 1
     {
          int dy,dx,d,dN,dNE;	
     dy=y1-y0;
     dx=x1-x0;
     d=dy-2*dx;
     dN=-2*dx;
     dNE=2*(dy-dx);
     
     drawDot(x0,y0);               //draws the initial point
     drawDot(x1,y1); 
     int x=x0,y=y0;
     
     while(y < y1)					//loop starts for the algorithm
     {
                if(d>=0)          // select North 
                {
                        d=d+dN;
                        
                        }
                else              //select North East
                {
                    d=d+dNE;
                    x++;
                    
                    }
                y++;             //increment of y value after evry iteration
                drawDot(x,y);
     
     }
     }
       
     glFlush();
     
}


void main(int argc,char **argv)
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//intialising 
     glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);  //dimensions
     glutInitWindowPosition(100,150);           //window position on screen
     glutCreateWindow("Bressenhams MPLA");      //title
     glutDisplayFunc(bressenhams);              //registering the function    
     myInit();
     glutMainLoop();
     }
