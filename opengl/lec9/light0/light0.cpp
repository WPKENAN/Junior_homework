#include<gl/glut.h>
void init()
{
	//远光源照射
	GLfloat light_position[]={0.0,1.0,0.0,0.0};	
	GLfloat blackColor[]={0.0,0.0,0.0,1.0};
	GLfloat whilteColor[]={1.0,1.0,1.0,1.0};
	GLfloat redColor[]={1.0,0.0,0.0,1.0};

	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,blackColor);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,redColor);
	glLightfv(GL_LIGHT0,GL_SPECULAR,redColor);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//局部光源照射
/*	GLfloat light_position1[] = {2.0,0.0,3.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	glEnable( GL_DEPTH_TEST );
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glTranslated(0.0,0.0,-200.0);
//	glDisable(GL_LIGHTING);
	glutSolidTeapot(50.0);
	glFlush();
}
void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspecratio = (GLfloat)w/(GLfloat)h;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-100,100,-100/aspecratio,100/aspecratio,10.0,400.0);
	else
		glOrtho(-100*aspecratio,100*aspecratio,-100,100,10.0,400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("Simple Lighting");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	return 0;
}