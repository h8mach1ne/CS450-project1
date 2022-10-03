#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>


#include "glew.h"
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include "glut.h"


#include <time.h>
#define INIT_VIEW_X 0.0    //Define initial camera position and viewing window values
#define INIT_VIEW_Y 0.0
#define INIT_VIEW_Z -4.5
#define VIEW_LEFT -2.0
#define VIEW_RIGHT 2.0
#define VIEW_BOTTOM -2.0
#define VIEW_TOP 2.0
#define VIEW_NEAR 1.0
#define VIEW_FAR 200.0
GLfloat AmbientLight[]={0.3,0.3,0.3,1.0};                  //Initialization values for lighting
//GLfloat DiffuseLight[] ={0.8,0.8,0.8,1.0};
//GLfloat SpecularLight[] ={1.0,1.0,1.0,1.0};
//GLfloat SpecRef[] = {0.7,0.7,0.7,1.0};
//GLfloat LightPos[] = {-50.0,50.0,100.0,1.0};
GLint Shine =128;
GLint walkX=0,walkY=0,lookX=0,lookY=0;
GLint world=1,oldX=-1,oldY=-1;
GLint guy=-1;

void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.20,1.1,.75);     //Specify the coordinates for the right eye
    glRotatef(-1,0,0,1);
    glScalef(.9,.7,.7);            //Specify the size of the right eye
    glColor3f(1.0,1.0,1.0);       //Specify the color of the eye
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.20,1.1,.75);     //Specify the position for the left eye
    glRotatef(1,0,0,1);
    glScalef(.9,.7,.7);
    glColor3f(1.0,1.0,1.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.20,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.20,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void sphere1()
{
    glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9 ,.9,.9 );
    glColor3f(1.0, 102.0/255.0, 204.0/255.0);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();
}


void sphere2()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glColor3f(1.0, 153.0/255.0, 152.0/255.0);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();
}

void nose()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(0.3,0.3,1.3);
    glColor3f(1.0, 128.0/255.0, 128.0/255.0);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();
}


void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the window
    glColor3ub(0,0,0);
    glPushMatrix();//Save viewing matrix state
    if(world==1)
    {
                 glTranslatef(walkX,-1,walkY);
                  glRotatef(lookY,0,1,0);
                  glRotatef(lookX,1,0,0);
    }


    //*******************Doll***********************
    glPushMatrix();
    glTranslatef(-1,0,-6);



     if(guy==1)
    {
      glTranslatef(walkX,-1,walkY);
      glRotatef(lookY,0,1,0);
      glRotatef(lookX,1,0,0);
    }
    eyeright();
    eyeleft();
    glColor3ub(255, 255, 0);
    sphere2();
    glColor3ub(0,100,0);
    sphere1();
    nose();
    glColor3f(0.0,0.0,0.0);
    pupilleft();
    pupilright();
    glPopMatrix();
    glPopMatrix();                                     //****Restore matrix state****
    glutSwapBuffers();                             //****Flush drawing commands****
}

void setBackgroundToBlack() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void SetupRend()
{
    setBackgroundToBlack();
    glEnable(GL_DEPTH_TEST);         //Enable depth testing
    glEnable(GL_LIGHTING);             //Enable lighting
    glLightfv(GL_LIGHT0,GL_AMBIENT,AmbientLight);//Set up and enable light zero
//    glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
//    glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);//Set material to follow
    //glMaterialfv(GL_FRONT,GL_SPECULAR,SpecRef);//Set specular reflectivity and shine
    glMateriali(GL_FRONT,GL_SHININESS,Shine);
}

void walk(int key,int x,int y)                                      //change positions using arrow keys
{
    if(key==GLUT_KEY_UP)    walkY+=1;
    if(key==GLUT_KEY_DOWN)  walkY-=1;
    if(key==GLUT_KEY_RIGHT) walkX+=1;
    if(key==GLUT_KEY_LEFT)  walkX-=1;
    if(key==GLUT_KEY_F10)   world=-world;
    if(key==GLUT_KEY_F9)    guy=-guy;
}

void gaze(int x,int y)
{
    if((oldX<0) || (oldY<0))
    {
      oldX=x;
      oldY=y;
    }
    lookX += y - oldY;
    lookY += x - oldX;
    oldX = x;
    oldY = y;
}

void myReshape(int w, int h)
{
    GLfloat Ratio;
    glViewport(0,0,w,h);
    Ratio=1.0*w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,Ratio,VIEW_NEAR,VIEW_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(INIT_VIEW_X,INIT_VIEW_Y,INIT_VIEW_Z);
    //glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}

int main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutCreateWindow("PROJECT1");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutSpecialFunc(walk);
    glutPassiveMotionFunc(gaze);
    SetupRend();
    glEnable(GL_NORMALIZE);
    glutMainLoop();
}
