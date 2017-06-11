#include <gl/glut.h>
//����ĳ�ʼλ�úʹ�С
GLfloat x1=0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;
//��x��y����Ĳ�����С
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
//׷�ٴ��ڿ�Ⱥ͸߶ȵı仯
GLfloat windowWidth;
GLfloat windowHeight;

void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ�����ɫ�������
	glColor3f(1.0f,0.0f,0.0f);//�ѵ�ǰ�Ļ�ͼ��ɫ����Ϊ��ɫ
	glRectf(x1,y1,x1+rsize,y1-rsize);//�õ�ǰ��ɫ����һ��������
	glutSwapBuffers();//ˢ�»�ͼ������н���
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
	{
		windowWidth = 100;
		windowHeight = 100/aspectRatio;
		glOrtho(-100.0,100.0,-windowHeight,windowHeight,1.0,-1.0);
	}
	else
	{
		windowWidth = 100*aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth,windowWidth,-100.0,100.0,1.0,-1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//������ʱ��GLUT��������ã�����δ�ı��С���ƶ�ʱ��
void TimerFunction(int value)
{
	//�ڵ�����߻��ұ�ʱ��ת����
	if(x1>windowWidth-rsize||x1<-windowWidth)
		xstep = -xstep;
	//�ڵ��ﶥ�߻�ױ�ʱ��ת����
	if(y1>windowHeight||y1<-windowHeight+rsize)
		ystep = -ystep;
	//ʵ���ƶ�����
	x1 += xstep;
	y1 += ystep;

	//���߽硣����Ϊ�˷�ֹ�����ڷ���ʱ���ڱ�С��ʹ����������µĲü�����֮��
	if(x1>(windowWidth-rsize+xstep))
		x1 = windowWidth-rsize-1;
	else if(x1<-(windowWidth+xstep))
		x1 = -windowWidth-1;

	if(y1>(windowHeight+ystep))
		y1 = windowHeight-1;
	else if(y1<-(windowHeight-rsize+ystep))
		y1 = -windowHeight+rsize-1;
	//���µ��������»��Ƴ���
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction,1);
}
void main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutCreateWindow("GLRectFlash");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunction,1);

	glutMainLoop();
}