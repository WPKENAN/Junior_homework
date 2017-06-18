#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "math.h"
#include "bits/stdc++.h"
using namespace std;

int width=500,height=500;
float xx1=0.0,yy1=0.0,xx2=15.0,yy2=30.0,xx3=30.0,yy3=0;
int n=500;
int flag=1;
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	gluOrtho2D(0,width,-height/2,height/2);
}
void mydisplay(){
//	cout << xx1 << yy1 << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(xx1,yy1);
	glVertex2f(xx2,yy2);
	glVertex2f(xx3,yy3);
	glEnd();
	glFlush();
}


void myidle(){
	float det=1.0*width/n;
	cout << det << endl;
	if(flag==1){
		xx1+=det;
		xx2+=det;
		xx3+=det;
		if(xx3+det>width){
			flag=-1;
		}
	}else if(flag==-1){
		xx1-=det;
		xx2-=det;
		xx3-=det;
		if(xx1-det<0){
			flag=1;
		}
	}
	cout << xx1 << endl;
	mydisplay();
}

int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(height,width);
	glutCreateWindow("KeyboardFunc");
	init();
	glutDisplayFunc(mydisplay);
	glutIdleFunc(myidle);
//	glutReshapeFunc(ChangeSize);
//	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。	
//	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
}

