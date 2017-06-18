#include <gl/glut.h>
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(0.0,0.0,-200.0);//把整个场景移到到视图中	
	glRotatef(45.0,1.0,1.0,1.0);//绕着向量（1,1,1）所指定的轴旋转45°	
	glutWireCube(100.0);

	glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
		glOrtho(-200.0,200.0,-200.0/aspectRatio,200.0/aspectRatio,10.0,400.0);
	else
		glOrtho(-200.0*aspectRatio,200.0*aspectRatio,-200.0,200.0,10.0,400.0);

//	gluPerspective(60.0,aspectRatio,1.0,400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Cube");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}