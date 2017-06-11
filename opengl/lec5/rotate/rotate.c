/*
 * rotate.c
 *
 * 创建旋转三角形
 *
 *
 * 用途:
 *    按“r”键旋转
 *    按“s”键停止旋转
 *    上下箭头键控制旋转速度
 *	  按ESCAPE键退出
 *
 */
#include <stdlib.h>
#include <GL/glut.h>

int RunMode = 1;		//1为旋转模式，0为静止模式
float curAngle = 0.0;   //当前旋转角度
float angleStep = 3.0;  //每次的角度递增值

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
			glutPostRedisplay();    //通知GLUT刷新当前的窗口
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
	//定义三角形
	GLint nverts = 3;
	point verts[3] = {{50.0,25.0},{150.0,25.0},{100.0,100.0}};
	point centerP;  //中心点

	int k;
	float xsum=0,ysum=0;
	glClear(GL_COLOR_BUFFER_BIT);

	if(RunMode==1)
	{
		curAngle += angleStep;
		if(curAngle>360.0)
			curAngle -= 360.0;
	}

	//求中心点坐标

	for(k=0;k<nverts;k++)
	{
		xsum += verts[k].x;
		ysum += verts[k].y;
	}
	centerP.x = xsum/nverts;
	centerP.y = ysum/nverts;

	// 旋转图形
	glMatrixMode( GL_MODELVIEW );			// 当前矩阵会改变场景模型
	glLoadIdentity();						// 设置单位矩阵
	glTranslatef( centerP.x,centerP.y,0.0 );					// 从原点平移旋转中心
	glRotatef( curAngle, 0.0, 0.0, 1.0 );		// 绕z轴旋转
	glTranslatef(-centerP.x,-centerP.y,0.0 );				// 将旋转中心移回原点
	//绘制图形
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0, 0.0, 0.0 );
		for(k=0;k<nverts;k++)
			glVertex2f(verts[k].x,verts[k].y);
	glEnd();

   //强制执行绘图命令，交换缓冲区进行显示
    glFlush();
    glutSwapBuffers();

	if ( RunMode==1 ) {
		glutPostRedisplay();	// 触发窗口重绘
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