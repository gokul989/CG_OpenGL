#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DEGREE 20
#define radius 8
#define dt 0.1              // samplin ratio

int numcontrols;                               //number of control points 
int dragcontrol = -1;
double controls[MAX_DEGREE+1][3];              //control points
int g=0;
FILE *fp;

struct hello
{
      double a;
      double b;
      double c;
};

struct hello points[10][36];         // array for storing the surface points

void drawdot(double a,double b,double c)   //drawdot function
{
     glPointSize(5.0);
     glColor3f(0.5,0.5,0.5);
     glBegin(GL_POINTS);
     glVertex3i(a,b,c);
     glEnd();
}

void drawline(double a,double b,double c,double d,double e,double f)  //drawline function
{ 
     glColor3f(1.0,0.7,0.5);
     glBegin(GL_LINES);
         glVertex3d(a,b,c);
         glVertex3d(d,e,f);
     glEnd();
}
   
void allBernstein(int n, double t, double B[])        //Bernstein polynomial coefficents
{
     int j,k;
     double t1 = 1.0 - t;
     double saved;
     B[0] = 1.0;
     for (j = 1; j <= n; j++) 
     {
         saved = 0.0;
         for (k = 0; k < j; k++)
         {
             double temp = B[k];
             B[k] = saved + t1*temp;
             saved = t*temp;
         }
         B[j] = saved;
     }
}

void pointOnBezierCurve(int i,double P[][3], int n, double t, double C[3])   // points on bezier curve implicit form
{
     double B[n+1];
     int k;
     allBernstein(n, t, B);
     C[0] = C[1] = C[2] = 0.0;
     for (k = 0,i=0; k <= n; k++,i++) 
     {
         C[0] += B[k]*P[k][0];
         C[1] += B[k]*P[k][1];
         C[2] += B[k]*P[k][2];
      
     }            
}

void reshape(int w,int h)         //redraw function
{
     glClearColor(0.0,0.0,0.0,1.0);
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     //glOrtho(0,w-1, h-1,0, -1,1);  
     gluPerspective(90,1,0.000,500);       //setting up the projection matrix
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0,300,500,0,0,-300,0,1,0);  //setting up the camera & view
     //gluLookAt(0,500,0,0,-500,0,0,0,1);
}

void display(void) 
{
     int i,o,r;
     double t;
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.3, 0.3, 1.0);
     glBegin(GL_LINE_STRIP);                           //plotting control points(blue line)
         for (i = 0; i < numcontrols; i++)
             glVertex3dv(controls[i]);
     glEnd();
     glColor3f(1.0, 0.0, 0.0);
     glBegin(GL_LINE_STRIP);
         for (i=0,t=0.0; i<10;i++,t+=dt)                     //plotting bezier curve by sampling 10 points
         {
             double C[3];    //array for storing x,y,z coordinates of sampled initial bezier curve
             pointOnBezierCurve(i,controls,numcontrols-1,t,C);
             points[i][0].a=C[0];
             points[i][0].b=C[1];
             points[i][0].c=C[2];
             glVertex3dv(C);
             for(o=10,r=1;r<36;r++,o+=10)                     //transformartion of each point about y axis in 10 degree increment
             {
                 points[i][r].a=(points[i][0].a * cos((3.14/180)*o)) + (points[i][0].c * sin((3.14/180)*o) );
                 points[i][r].b=points[i][0].b;
                 points[i][r].c=(points[i][0].c * cos((3.14/180)*o)) - (points[i][0].a * sin((3.14/180)*o) );
                 drawdot(points[i][r].a,points[i][r].b,points[i][r].c);
            }
         }
     glEnd();
     fp=fopen("test.off","w");       // creating an OFF file for storing the model information
     fprintf(fp,"OFF\n");
     fprintf(fp,"%d %d %d\n",360,315,324);
     for(r=0;r<36;r++)              //writing info into OFF file
     {
         for(i=0;i<10;i++)
         {
             printf("( %lf,",points[i][0].a);
             printf("%lf,",points[i][0].b);
             printf("%lf )\t",points[i][0].c);
             fprintf(fp,"%lf ",points[i][r].a);
             fprintf(fp,"%lf ",points[i][r].b);
             fprintf(fp,"%lf ",points[i][r].c);
         } 
         fprintf(fp,"\n");
     }
     printf("\n");
     glFlush();     
}

void mouse(int button, int state, int x, int y)  //mouse control
{
     if (button == GLUT_MIDDLE_BUTTON)        
     {
         if (state == GLUT_DOWN) 
         {
             int i;
	         for (i = 0; i < numcontrols; i++)
	             if (fabs(controls[i][0] - x) + fabs(controls[i][1] - y) < radius) 
                 {
	                 dragcontrol = i;
	                 break;
                 }
                 else if (state == GLUT_UP)
                 {
                     dragcontrol = -1;
                 }
          }
     }
     else if(button == GLUT_LEFT_BUTTON)           //generate more control points
     {
         if (state == GLUT_DOWN) 
         {
             int i,r;
             glPointSize(5.0);
             controls[g][0]=x;
             controls[g][1]=y;
             controls[g][2]=0;
             g++;     
             numcontrols=g;
             glutPostRedisplay();
         }
     }
     else if(button== GLUT_RIGHT_BUTTON)              //generate wire MESH
     {
          if(state==GLUT_DOWN)
          {
              int i,r;
              for(r=1;r<=36;r++)                        //draw longitude
              {
                  for(i=1;i<10;i++)
                  {
                      drawline(points[i-1][r-1].a,points[i-1][r-1].b,points[i-1][r-1].c,points[i][r-1].a,points[i][r-1].b,points[i][r-1].c);
                      glFlush();
                  }
              }
              glFlush();
              for(i=0;i<10;i++)                       //draw latitude                                                                                
              {
                  for(r=1;r<36;r++)
                  {
                      drawline(points[i][r-1].a,points[i][r-1].b,points[i][r-1].c,points[i][r].a,points[i][r].b,points[i][r].c);
                      glFlush();
                  }
                  drawline(points[i][35].a,points[i][35].b,points[i][35].c,points[i][0].a,points[i][0].b,points[i][0].c);
                  glFlush();
              }
          }
     }
}

void mouseMotion(int x, int y) 
{
     if (dragcontrol != -1) 
     {
         controls[dragcontrol][0] = (double) x;
         controls[dragcontrol][1] = (double) y;
         glutPostRedisplay();
     }
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}


