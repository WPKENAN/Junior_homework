#include <gl/glut.h>

//������Ⱦ״̬
void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
//���Ƴ���
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ�����ɫ�������
	glFlush();//ˢ�»�ͼ����
}

void main( )
{
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutCreateWindow("Simple");

  init();

  glutDisplayFunc( display );

  glutMainLoop();
}
