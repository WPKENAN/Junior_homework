#include<gl/glut.h>
void init()
{
	//设置材质的各种光的颜色成分反射率
	GLfloat mat_ambient[] = {0.8,0.8,0.8,1.0};
	GLfloat mat_diffuse[] = {0.8,0.0,0.8,1.0};
	GLfloat mat_specular[] = {1.0,0.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};
	
	GLfloat light_position[]={1.0,1.0,1.0,0.0};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);



	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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