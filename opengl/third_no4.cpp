#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "math.h"
#include "bits/stdc++.h"
using namespace std;
int currentMode = 0;
const int ModeNums = 7;
float theta=0.0;
float PI=3.1415926;
float R=6.0,n=3;
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);	
	glColor3f(0.0,1.0,0.0);
	int i=0;
	for(int i=0;i<n;i++){
		glVertex2f(R*cos(theta+i*2*PI/n),R*sin(theta+i*2*PI/n));
	}
	glEnd();
	glFlush();
}

void myidle(){
	theta+=0.001;
	if(theta>=2*PI) theta-=2*PI;
	mydisplay();	
}



void ChangeSize(GLsizei w,GLsizei h)
{
	float ratio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (float)w/(float)h;
	if(w<=h)
		gluOrtho2D(-10.0,10.0,-10.0/ratio,10.0/ratio);
	else
		gluOrtho2D(-10.0*ratio,10.0*ratio,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}




int main(int argc,char *argv[])
{
	printf("%lf\n",sin(1/2.0*PI));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(360,360);
	glutCreateWindow("旋转");

	init();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(myidle);
	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
}
