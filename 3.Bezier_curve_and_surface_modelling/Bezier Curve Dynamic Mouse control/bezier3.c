
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DEGREE 20
#define radius 8
#define dt 0.01

int numcontrols;                               //number of control points 
int dragcontrol = -1;
double controls[MAX_DEGREE+1][3];              //control points
int g=0;

void drawdot(double a,double b)
{
     glPointSize(5.0);
     glColor3f(0.5,0.5,0.5);
     glBegin(GL_POINTS);
     glVertex2d(a,b);
     glEnd();
}

void allBernstein(int n, double t, double B[])
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

void pointOnBezierCurve(double P[][3], int n, double t, double C[3]) 
{
     double B[n+1];
     int k;
     allBernstein(n, t, B);
     C[0] = C[1] = C[2] = 0.0;
     for (k = 0; k <= n; k++) 
     {
         C[0] += B[k]*P[k][0];
         C[1] += B[k]*P[k][1];
         C[2] += B[k]*P[k][2];
     }
}

void reshape(int w, int h) 
{
     glClearColor(0.0,0.0,0.0,1.0);
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0,w-1, h-1,0, -1,1);  
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void display(void) 
{
     int i;
     double t;
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.3, 0.3, 1.0);
     glBegin(GL_LINE_STRIP);
         for (i = 0; i < numcontrols; i++)
             glVertex3dv(controls[i]);
     glEnd();
     glColor3f(1.0, 0.0, 0.0);
     glBegin(GL_LINE_STRIP);
         for (i=0,t=0.0; i<=100;i++,t+=dt) 
         {
             double C[3];
             pointOnBezierCurve(controls,numcontrols-1,t,C);
             glVertex3dv(C);
         }
     glEnd();
     glFlush();
}

void mouse(int button, int state, int x, int y)
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
     else if(button == GLUT_LEFT_BUTTON) 
     {
         if (state == GLUT_DOWN) 
         {
             glPointSize(5.0);
             controls[g][0]=x;
             controls[g][1]=y;
             controls[g][2]=0;
             drawdot(controls[g][0],controls[g][1]);
             g++;     
             numcontrols=g;
             glutPostRedisplay();
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
