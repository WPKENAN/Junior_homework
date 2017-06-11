#include <gl/glut.h>
void myinit()
{
	glClearColor(0.0,0.0,0.0,0.0);

}

void changeSize(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<=h)
		glOrtho(-20.0,20.0,-20.0*(GLfloat)h/(GLfloat)w,20.0*(GLfloat)h/(GLfloat)w,-50.0,50.0);
	else
		glOrtho(-20.0*(GLfloat)h/(GLfloat)w,20.0*(GLfloat)h/(GLfloat)w,-20.0,20.0,-50.0,50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawMyObjects()
{	
	
	//���ĸ���
	glBegin(GL_POINTS);
		glColor3f(1.0,0.5,0.6);
		glVertex2f(-7.0,10.0);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(-11.0,10.0);
		glColor3f(0.0,1.0,1.0);
		glVertex2f(-8.0,12.0);
		glColor3f(0.8,0.5,0.6);
		glVertex2f(-8.0,11.0);
	glEnd();
	//�������߶�
	glBegin(GL_LINES);
		glColor3f(1.0,0.8,0.9);
		glVertex2f(-10.0,9.0);
		glVertex2f(-7.0,7.0);


		glColor3f(1.0,0.0,1.0);
		glVertex2f(-11.0,9.0);
		glVertex2f(-8.0,6.0);

		glColor3f(1.0,0.0,0.0);
		glVertex2f(-13.0,7.0);
		glVertex2f(-9.0,8.0);

		glColor3f(0.0,1.0,0.0);
		glVertex2f(-12.0,5.0);
		glVertex2f(-10.0,8.0);
	glEnd();
	//���������߶���ɵĿ�����
	glBegin(GL_LINE_STRIP);
		glColor3f(0.5,1.0,1.0);
	//	glPointSize(5);
		glVertex2f(-3.0,9.0);
		glVertex2f(2.0,6.0);
		glVertex2f(3.0,8.0);
		glVertex2f(-2.5,6.5);
		glVertex2f(-4.0,5.5);
	glEnd();
	//���������߶���ɵı�����
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0,0.0,1.0);
		glVertex2f(6.0,6.0);
		glVertex2f(8.0,7.0);
		glVertex2f(9.0,6.5);
		glVertex2f(10.3,7.5);
		glVertex2f(12.5,6.0);
		glVertex2f(7.5,8.0);
	glEnd();
	//���������
	glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(-8.0,3.0);
		glVertex2f(-9.0,4.0);
		glVertex2f(-11.0,0.8);
		glVertex2f(-7.5,-2.0);
		glVertex2f(-6.0,-1.0);
	glEnd();
	//�������ı���
	glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(0.0,2.0);
		glVertex2f(0.0,3.0);
		glVertex2f(-3.0,3.0);
		glVertex2f(-3.0,2.0);
		
		glColor3f(0.0,1.0,0.0);
		glVertex2f(3.0,2.0);
		glVertex2f(3.0,3.0);
		glVertex2f(4.0,3.0);
		glVertex2f(4.0,2.0);
	glEnd();
	//���������ı�����ɵ������ı���
	glBegin(GL_QUAD_STRIP);
	    glColor3f(1.0,0.0,0.0);
		glVertex2f(6.0,-2.0);
		glVertex2f(5.5,1.0);
		glVertex2f(8.0,-1.0);
		
		glColor3f(0.0,1.0,0.0);
		glVertex2f(9.0,2.0);
		glVertex2f(11.0,-2.0);
		
		glColor3f(0.0,0.0,1.0);
		glVertex2f(11.0,2.0);
		glVertex2f(13.0,-1.0);
		
		glColor3f(0.0,0.0,1.0);
		glVertex2f(14.0,1.0);
	glEnd();
	//������������
	glBegin(GL_TRIANGLES);
		glColor3f(0.2,0.5,0.0);
		glVertex2f(-10.0,-5.0);
		glVertex2f(-10.0,-8.0);
		glVertex2f(-6.0,-8.0);
	
		glColor3f(1.0,1.0,0.5);
		glVertex2f(-6.0,-7.0);
		glVertex2f(-4.0,-7.0);
		glVertex2f(-5.5,-9.0);
	glEnd();
	//�����ĸ���������ɵ�����������
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-1.0,-8.0);
		glVertex2f(-2.5,-5.0);
		glColor3f(0.8,0.0,0.0);
		glVertex2f(1.0,-7.0);
		glColor3f(1.0,0.8,0.8);
		glVertex2f(2.0,-4.0);
		glColor3f(0.8,1.0,0.8);
		glVertex2f(4.0,-6.0);
	glEnd();
	//������������
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(8.0,-6.0);
		glVertex2f(10.0,-3.0);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(12.5,-4.5);
		glColor3f(0.2,0.5,0.8);
		glVertex2f(13.0,-7.5);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(10.5,-9.0);
	glEnd();
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	DrawMyObjects();
	glFlush();
}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);//���ڴ�СΪ500*500
	glutInitWindowPosition(0,0);
    glutCreateWindow("��һ���ϻ���ҵ��һ��");

	myinit();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);

	glutMainLoop();
	return 0;
}
