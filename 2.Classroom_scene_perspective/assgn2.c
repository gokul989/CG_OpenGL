#define GLUT_DISABLE_ATEXIT_HACK    //to disable makefile errors
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <windows.h>

GLsizei wh = 600,ww = 800;


int b=0,cl=0,r=0,l=0,cr=0,xl=0,xr=0,yu=0,yd=0,zf=0,zb=0,cxl=0,cxr=0,cyu=0,cyd=0,czf=0,czb=0,pf=0,cpf=0,pb=0,cpb=0,zi=0,zo=0,czi=1,czo=1;
int yf=0,yr=0,cyr=0,cyl=0;
void init();
void reshape(GLsizei w, GLsizei h);
void model();
void top();
void draw(int ,int ,int ,int,int,int,int);
void KeyDown(unsigned char key,int x,int y);
void clear();


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww,wh);
	glutInitWindowPosition(200,150);
	
	glutCreateWindow("class");
	glutReshapeFunc(reshape);
	glutDisplayFunc(model);
	glutKeyboardFunc(KeyDown);
	init();
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	return 0;
}


void init()
{
	glClearColor (0.0, 0.7, 1.0, 1.0);
	glColor3f(1.,1.,1.);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
//glOrtho(-2000.,2000.0,-2000.,2000.,-2000.,2000.); 
  gluPerspective(90,1,1,2500);
  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	 
}
void KeyDown(unsigned char key, int x, int y)               //response to keystrokes
{
     
	switch (key) 
	{
	case 27:		//ESC
		PostQuitMessage(0);
		break;
		
	case 'r':		                                         //roll right
	r++;
	while(r>0){
		clear();
        draw(cl+cr+10,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cr+=10;
		r--;}
		break;
		
	case 'l':		//roll left
		l++;
	while(l>0){
		clear();
        draw(cr+cl-10,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cl-=10;
		l--;}
		break;
		
	case 'a':		//translate x left
		xl++;
	while(xl>0){
		clear();
        draw(cr+cl,cxl+cxr-10,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cxl-=10;
		xl--;}
		break;
		
	case 'd':		//translate x right
		xr++;
	while(xr>0){
		clear();
        draw(cr+cl,cxl+cxr+10,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cxr+=10;
		xr--;}
		break;
		
	case 's':		//translate y down
		yu++;
	while(yu>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd+10,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cyu+=10;
		yu--;}
		break;
	
    case 'w':		//translate y up
		yd++;
	while(yd>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd-10,czf+czb,cpf+cpb,czi*czo,cyr+cyl);
		cyd-=10;
		yd--;}
		break;
	
    case 'k':		//translate z forward
		zf++;
	while(zf>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb-10,cpf+cpb,czi*czo,cyr+cyl);
		czf-=10;
		zf--;}
		break;
	
    case 'm':		//translate z backward
		zb++;
	while(zb>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb+10,cpf+cpb,czi*czo,cyr+cyl);
		czb+=10;
		zb--;}
		break;
	
    case 'p':       //pitch forward
		pf++;
	while(pf>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb+10,czi*czo,cyr+cyl);
		cpf+=10;
		pf--;}
		break;
	
    case 'o':       //pitch backward
		pb++;
	while(pb>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb-10,czi*czo,cyr+cyl);
		cpb-=10;
		pb--;}
		break;

	case 'z':      //zoom in
		zi++;
	while(zi>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo*1.2,cyr+cyl);
		czi*=1.2;
		zi--;}
		break;
		
	case 'x':    //zoom out
		zo++;
	while(zo>0){
		clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo/1.2,cyr+cyl);
		czo/=1.2;
		zo--;}
		break;
	case 'g':
         yf++;
         while(yf>0){
                     clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl+10);
		cyr+=10;
		yf--;}
		break;
	case 'h':
         yr++;
         while(yr>0){
                     clear();
        draw(cr+cl,cxl+cxr,cyu+cyd,czf+czb,cpf+cpb,czi*czo,cyr+cyl-10);
		cyr-=10;
		yr--;}
		break;

	
}
}
void clear()   //clear screen for redrawing
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    ///*
    gluLookAt(
	      0, 1200, 400,
		0, 1200,1800 ,
		0, 1, 0);
    }
void reshape(GLsizei w, GLsizei h) //reshaping the window & setting viewport
{
	/* adjust clipping box */

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glClearColor (0.0, 0.7, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();


/*	ww = w;
	wh = h;*/

}


void model()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    ///*
    gluLookAt(
	      0, 1200, 400,
		0, 1200,1800 ,
		0, 1, 0);
		//*/
		draw(0,0,0,0,0,1,0);
    }
    void draw(int j,int x,int y,int z,int p,int z1,int r)     //draw scene function 
    {
         glPushMatrix();
             glRotatef(j,0,0,1);
             glRotatef(p,1,0,0);
             glRotatef(r,0,1,0);
             glTranslatef(x,y,z);
             glScalef(z1,z1,z1);
		     //ceiling
             glPushMatrix();
                 glColor3f(0.5,0.5,0.5);
                 glTranslatef(0,1850,00.);
                 glScalef(17,1,25);
	             glutSolidCube(150);
		     glPopMatrix();
     	     //back wall
              glPushMatrix();
                 glColor3f(1,1,1);
		         glTranslatef(0,900,1850.);
	             glScalef(15,12,1);
	             glutSolidCube(150);
		     glPopMatrix();
             glPushMatrix();
                 glTranslatef(300,-300,00.);               
		         // bb wall
		         glPushMatrix();
		             glColor3f(1,1,1);
		             glTranslatef(-300,1200,-1750.);
	                 glScalef(15,12,1);
	                 glutSolidCube(150);
                 glPopMatrix();
                 // floor
                 glPushMatrix();
		             glColor3f(0.5,0.5,0.5);
		             glTranslatef(-300,250,00.);
	                 glScalef(17,1,25);
	                 glutSolidCube(150);
                 glPopMatrix();
                 //r wall
                 glPushMatrix();
		             glColor3f(1,1,0);
		             glTranslatef(900,1200,00.);
	                 glScalef(1,12,25);
	                 glutSolidCube(150);
                 glPopMatrix();
                 //l wall
                 glPushMatrix();
		             glColor3f(1,1,0);
		             glTranslatef(-1500,1200,00.);
	                 glScalef(1,12,25);
	                 glutSolidCube(150);
		         glPopMatrix();
                 
                //benches
                //1
                glPushMatrix();
                    //glScalef(0.05,0.05,0.05);
	                glTranslatef(800,0,00.);
                    glPushMatrix();
	                    glTranslatef(-1600,900,0.);
	                    glRotatef(-90,1.,0.,0.);
	                    glScalef(5,5,1);
	                    top();
	                   
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1900,600,-200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1900,600,200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1300,600,200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1300,600,-200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                glPopMatrix();
                //2
                glPushMatrix();
                    glTranslatef(1000,0,00.);
                    glPushMatrix();
	                    glTranslatef(-800,900,0.);
	                    glRotatef(-90,1.,0.,0.);
	                    glScalef(5,5,1);
	                    top();
	                    
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1100,600,-200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-1100,600,200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-500,600,200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
    	                glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-500,600,-200.);
	                    //glRotatef(90,1.,0.,0.);
	                    glColor3f(0.0,0.,.0);
	                    glScalef(1,4,1);
	                    glutSolidCube(150);
                    glPopMatrix();
                glPopMatrix();
                //3&4
                glPushMatrix();
	                glTranslatef(800,0,1200.);
	                glPushMatrix();
                        glTranslatef(-1600,900,0.);
	                    glRotatef(-90,1.,0.,0.);
	                    glScalef(5,5,1);
	                    top();
	                    
	                    glPopMatrix();
                        glPushMatrix();
                            glTranslatef(-1900,600,-200.);
	                        //glRotatef(90,1.,0.,0.);
	                        glColor3f(0.0,0.,.0);
	                        glScalef(1,4,1);
	                        glutSolidCube(150);
                        glPopMatrix();
                        glPushMatrix();
                            glTranslatef(-1900,600,200.);
	                        //glRotatef(90,1.,0.,0.);
	                        glColor3f(0.0,0.,.0);
	                        glScalef(1,4,1);
	                        glutSolidCube(150);
                        glPopMatrix();
                        glPushMatrix();
                            glTranslatef(-1300,600,200.);
	                        //glRotatef(90,1.,0.,0.);
	                        glColor3f(0.0,0.,.0);
	                        glScalef(1,4,1);
	                        glutSolidCube(150);
                        glPopMatrix();
                        glPushMatrix();
                            glTranslatef(-1300,600,-200.);
	                        //glRotatef(90,1.,0.,0.);
	                        glColor3f(0.0,0.,.0);
	                        glScalef(1,4,1);
	                        glutSolidCube(150);
                         glPopMatrix();
                     glPopMatrix();
                     //4
                     glPushMatrix();
                         glTranslatef(1000,0,1200.);
                         glPushMatrix();
                             glTranslatef(-800,900,0.);
	                         glRotatef(-90,1.,0.,0.);
	                         glScalef(5,5,1);
	                         top();
	                        
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1100,600,-200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1100,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-500,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-500,600,-200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                     glPopMatrix();
                     //end 3 &4
                     //5 &6
                     glPushMatrix();
	                     glTranslatef(800,00,-1200.);
                         glPushMatrix();
                             glTranslatef(-1600,900,0.);
	                         glRotatef(-90,1.,0.,0.);
	                         glScalef(5,5,1);
	                         top();
                             
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1900,600,-200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1900,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1300,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1300,600,-200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                     glPopMatrix();
                     //6
                     glPushMatrix();
                         glTranslatef(1000,00,-1200.);
                         glPushMatrix();
	                         glTranslatef(-800,900,0.);
	                         glRotatef(-90,1.,0.,0.);
	                         glScalef(5,5,1);
	                         top();
	                         
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1100,600,-200.);
    	                     //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-1100,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-500,600,200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                         glPushMatrix();
                             glTranslatef(-500,600,-200.);
	                         //glRotatef(90,1.,0.,0.);
	                         glColor3f(0.0,0.,.0);
	                         glScalef(1,4,1);
	                         glutSolidCube(150);
                         glPopMatrix();
                     glPopMatrix();
                     //end 5&6
                 glPopMatrix();
          glPopMatrix();
	glutSwapBuffers();
}


void top()
{
	glColor3f(1.0,0.,.0);
	glutSolidCube(150);
}


