#coding:utf8
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from math import *


def init():
    glClearColor(1.0,1.0,1.0,1.0);
    gluOrtho2D(0,500,0,500)
#    glClear(GL_COLOR_BUFFER_BIT);

def MidPointLine(x0,y0,x1,y1):
    glClear(GL_COLOR_BUFFER_BIT);
    dx=x1-x0;
    dy=y1-y0;
    d=dx-2*dy;#初始化判别式
    incrE=-2*dy;#取像素E判别式增量,取下
    incrNE=2*(dx-dy);#取上
    
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(x0,y0);
    x=x0;y=y0;

    while x<x1:
        if d>0:
            d=d=incrE;
        else:
            d=d+incrNE;
            y=y+1;
        
        x=x+1;
        print x,y
        glVertex2f(x*1.0,y*1.0);
    glEnd();
    glFlush();
    

def drawline():
    MidPointLine(20,20,500,300);
    
glutInit();
glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
glutInitWindowSize(500,500);
glutCreateWindow("MidPointLine");
init();
glutDisplayFunc(drawline);
glutMainLoop();



    




