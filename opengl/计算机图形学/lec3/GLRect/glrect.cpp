#include <gl/glut.h>
void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ�����ɫ�������
	glColor3f(1.0f,0.0f,0.0f);//�ѵ�ǰ�Ļ�ͼ��ɫ����Ϊ��ɫ
	glRectf(-25.0f,25.0f,25.0f,-25.0f);//�õ�ǰ��ɫ����һ��������
	glFlush();//ˢ�»�ͼ����
}
//�����ڸı��Сʱ��GLUT���������
void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	// ��ֹ��0��
	if(h==0)
		h=1;
	//���ӿ�����Ϊ���ڵĴ�С
	glViewport(0,0,w,h);
	//��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//�����ü��������ҡ��ס���������Զ��
	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
		glOrtho(-100.0,100.0,-100/aspectRatio,100.0/aspectRatio,1.0,-1.0);
	else
		glOrtho(-100.0*aspectRatio,100.0*aspectRatio,-100.0,100.0,1.0,-1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("GLRect");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}