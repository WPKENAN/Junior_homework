#coding:utf8
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


def init():
    glClearColor(0.0,0.0,0.0,0.0);#
    gluOrtho2D(-15.0,15.0,-15.0,15.0)

def RenderScene():
    glClear(GL_COLOR_BUFFER_BIT);#清除屏幕
    glColor3f(1.0,1.0,0.0);#设置颜色
    DrawMyObjects()
    glFlush();

def DrawMyObjects():
	#画点
        glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(-10.0,11.0);
	glColor3f(1.0,1.0,0.0);
	glVertex2f(-9.0,10.0);
	glColor3f(0.0,1.0,1.0);
	glVertex2f(-8.0,12.0);
	glEnd();
#        glPointSize(10);
	#画线段
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,0.0);
	
	glVertex2f(-11.0,8.0);
	glVertex2f(-7.0,7.0);
	glColor3f(1.0,0.0,1.0);
	glVertex2f(-11.0,9.0);
	glVertex2f(-8.0,6.0);
	glEnd();
	#画开折线
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0,1.0,0.0);
#	glPointSize(5);
	glVertex2f(-3.0,9.0);
	glVertex2f(2.0,6.0);
	glVertex2f(3.0,8.0);
	glVertex2f(-2.5,6.5);
	glEnd();
	#画闭折线
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,1.0,1.0);
	glVertex2f(7.0,7.0);
	glVertex2f(8.0,8.0);
	glVertex2f(9.0,6.5);
	glVertex2f(10.3,7.5);
	glVertex2f(11.5,6.0);
	glVertex2f(7.5,6.0);
	glEnd();
	#画填充多边形
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.3,0.7);
	glVertex2f(-7.0,2.0);
	glVertex2f(-8.0,3.0);
	glVertex2f(-10.3,0.5);
	glVertex2f(-7.5,-2.0);
	glVertex2f(-6.0,-1.0);
	glEnd();
	#画四边形
	glBegin(GL_QUADS);
	glColor3f(0.7,0.5,0.2);
	glVertex2f(0.0,2.0);
	glVertex2f(-1.0,3.0);
	glVertex2f(-3.3,0.5);
	glVertex2f(-0.5,-1.0);
	glColor3f(0.5,0.7,0.2);
	glVertex2f(3.0,2.0);
	glVertex2f(2.0,3.0);
	glVertex2f(0.0,0.5);
	glVertex2f(2.5,-1.0);
	glEnd();
	#画连接四边形
	glBegin(GL_QUAD_STRIP);
	glVertex2f(6.0,-2.0);
	glVertex2f(5.5,1.0);
	glVertex2f(8.0,-1.0);
	glColor3f(0.8,0.0,0.0);
	glVertex2f(9.0,2.0);
	glVertex2f(11.0,-2.0);
	glColor3f(0.0,0.0,0.8);
	glVertex2f(11.0,2.0);
	glVertex2f(13.0,-1.0);
	glColor3f(0.0,0.8,0.0);
	glVertex2f(14.0,1.0);
	glEnd();
	#画三角形
	glBegin(GL_TRIANGLES);
	glColor3f(0.2,0.5,0.7);
	glVertex2f(-10.0,-5.0);
	glVertex2f(-12.3,-7.5);
	glVertex2f(-8.5,-6.0);
	glColor3f(0.2,0.7,0.5);
	glVertex2f(-8.0,-7.0);
	glVertex2f(-7.0,-4.5);
	glVertex2f(-5.5,-9.0);
	glEnd();
	#画连续三角形
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-1.0,-8.0);
	glVertex2f(-2.5,-5.0);
	glColor3f(0.8,0.8,0.0);
	glVertex2f(1.0,-7.0);
	glColor3f(0.0,0.8,0.8);
	glVertex2f(2.0,-4.0);
	glColor3f(0.8,0.0,0.8);
	glVertex2f(4.0,-6.0);
	glEnd();
	#画扇形三角形
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(8.0,-6.0);
	glVertex2f(10.0,-3.0);
	glColor3f(0.8,0.2,0.5);
	glVertex2f(12.5,-4.5);
	glColor3f(0.2,0.5,0.8);
	glVertex2f(13.0,-7.5);
	glColor3f(0.8,0.5,0.2);
	glVertex2f(10.5,-9.0);
	glEnd();
glutInit();
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);

glutCreateWindow("Geometric Primitive Types");

init();
glutDisplayFunc(RenderScene);

#glutReshapeFunc(RenderScene);
#glutDisplayFunc(chaingeSize);

glutMainLoop();	

