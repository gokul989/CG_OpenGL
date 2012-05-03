#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;

struct hello 
{
       double a;
       double b;
       double c;
};

struct hello p[10][36];  //struct for storing read points from the inputted OFF file.
       
void drawline(double a,double b,double c,double d,double e,double f)    //drawline function
{ 
     glColor3f(1.0,0.7,0.5);
     glBegin(GL_LINES);
            glVertex3d(a,b,c);
            glVertex3d(d,e,f);
     glEnd();
}
void reshape(int w,int h) 
{
     glClearColor(0.0,0.0,0.0,1.0);
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(90,1,0.000,500);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0,300,500,0,0,-300,0,1,0);
     //gluLookAt(0,500,0,0,-500,0,0,0,1);
}

void display(void)
{
      int i,r;
      for(r=1;r<=36;r++)               //draw longitude
      {
          for(i=1;i<10;i++)
          {
              drawline(p[i-1][r-1].a,p[i-1][r-1].b,p[i-1][r-1].c,p[i][r-1].a,p[i][r-1].b,p[i][r-1].c);
              glFlush();
          }
      }
      glFlush();
      for(i=0;i<10;i++)             //draw latitude
      {
          for(r=1;r<36;r++)
          {
              drawline(p[i][r-1].a,p[i][r-1].b,p[i][r-1].c,p[i][r].a,p[i][r].b,p[i][r].c);
              glFlush();
          }
          drawline(p[i][35].a,p[i][35].b,p[i][35].c,p[i][0].a,p[i][0].b,p[i][0].c);
          glFlush();
      }
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    char ch[4];
    int count=0,k,l,m,i;
    int r;
    fp=fopen("test.off","r");   //openthe OFF file
    fscanf(fp,"%s",ch);
    printf("%s",ch);
    fscanf(fp,"%c",&ch[0]);
    printf("%c",ch[0]);
    fscanf(fp,"%d %d %d",&k,&l,&m);
    printf("%d",k);
    printf("%c",ch[0]);
    for(r=0;r<36;r++)                              //points inputting into the defined stucture
    {
        for(i=0;i<10;i++)
        {
            fscanf(fp,"%lf %lf %lf",&p[i][r].a,&p[i][r].b,&p[i][r].c);
            printf("%lf %lf %lf",p[i][r].a,p[i][r].b,p[i][r].c);
            printf(" ");
            fscanf(fp,"%c",&ch[0]);
        }
        printf("\n");
    }
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
