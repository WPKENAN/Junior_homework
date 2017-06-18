/*
 * rotate.c
 *
 * ������ת������
 *
 *
 * ��;:
 *    ����r������ת
 *    ����s����ֹͣ��ת
 *    ���¼�ͷ��������ת�ٶ�
 *	  ��ESCAPE���˳�
 *
 */
#include <stdlib.h>
#include <GL/glut.h>

int RunMode = 1;		//1Ϊ��תģʽ��0Ϊ��ֹģʽ
float curAngle = 0.0;   //��ǰ��ת�Ƕ�
float angleStep = 3.0;  //ÿ�εĽǶȵ���ֵ

typedef struct  {
	float x,y;
}point;

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
}

void myKey(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'r':RunMode = 1;
			glutPostRedisplay();    //֪ͨGLUTˢ�µ�ǰ�Ĵ���
			break;
	case 's':RunMode = 0;
			glutPostRedisplay();
			break;
	case 27:
			exit(1);
	}
}
void RenderScene()
{
	//����������
	GLint nverts = 3;
	point verts[3] = {{50.0,25.0},{150.0,25.0},{100.0,100.0}};
	point centerP;  //���ĵ�

	int k;
	float xsum=0,ysum=0;
	glClear(GL_COLOR_BUFFER_BIT);

	if(RunMode==1)
	{
		curAngle += angleStep;
		if(curAngle>360.0)
			curAngle -= 360.0;
	}

	//�����ĵ�����

	for(k=0;k<nverts;k++)
	{
		xsum += verts[k].x;
		ysum += verts[k].y;
	}
	centerP.x = xsum/nverts;
	centerP.y = ysum/nverts;

	// ��תͼ��
	glMatrixMode( GL_MODELVIEW );			// ��ǰ�����ı䳡��ģ��
	glLoadIdentity();						// ���õ�λ����
	glTranslatef( centerP.x,centerP.y,0.0 );					// ��ԭ��ƽ����ת����
	glRotatef( curAngle, 0.0, 0.0, 1.0 );		// ��z����ת
	glTranslatef(-centerP.x,-centerP.y,0.0 );				// ����ת�����ƻ�ԭ��
	//����ͼ��
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0, 0.0, 0.0 );
		for(k=0;k<nverts;k++)
			glVertex2f(verts[k].x,verts[k].y);
	glEnd();

   //ǿ��ִ�л�ͼ�������������������ʾ
    glFlush();
    glutSwapBuffers();

	if ( RunMode==1 ) {
		glutPostRedisplay();	// ���������ػ�
	}
	
}

void ChangeSize(GLsizei w,GLsizei h)
{
	float ratio;
	if(h==0)
		h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0,0,w,h);
	ratio = (float)w/(float)h;
	if(w<=h)
		gluOrtho2D(0.0,200.0,-50.0/ratio,150.0/ratio);
	else
		gluOrtho2D(0.0*ratio,200*ratio,-50.0,150.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("rotate triangle");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);
	

	glutMainLoop();
}