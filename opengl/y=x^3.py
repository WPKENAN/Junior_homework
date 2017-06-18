#-*- coding:utf8 -*-
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import sys

def init():
    glClearColor(1,1,1,1);
    gluOrtho2D(-5.0,5.0,-5.0,5.0);

def plotfunc():
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);

    #绘制坐标系
    glColor3f(0.0,0.0,0.0);    
    glBegin(GL_LINES);
    glVertex2f(-5.0,0.0);
    glVertex2f(5.0,0.0);
    glVertex2f(0.0,5.0);
    glVertex2f(0.0,-5.0);
    glEnd();

    #绘制图像
    glColor3f(0,0,0);
    glBegin(GL_LINES);

    for x in (i*0.01 for i in range(-500,500)):
        y=x*x*x
        glVertex2f(x,y);
    glEnd();

    glFlush();


def main():
    glutInit(sys.argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Function Plotter");
    init();
    glutDisplayFunc(plotfunc);
    glutMainLoop();

main()


