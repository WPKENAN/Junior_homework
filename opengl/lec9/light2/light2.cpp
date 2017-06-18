#include<gl/glut.h>
void init()
{	
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable( GL_DEPTH_TEST );
}
void RenderScene()
{
		//设置材质的各种光的颜色成分反射率
	GLfloat no_mat[] ={0.0,0.0,0.0,1.0};
	GLfloat mat_ambient[] = {0.7,0.7,0.7,1.0};
	GLfloat mat_diffuse[] = {0.1,0.5,0.8,1.0};
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {5.0};
	GLfloat high_shininess[] = {100.0};
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glTranslated(0.0,0.0,-20.0);

	//仅有环境光
	glPushMatrix();
	glTranslated(-4.0,6.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//仅有漫反射光
	glPushMatrix();
	glTranslated(0.0,6.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();
	
	//有漫反射光和环境光
	glPushMatrix();
	glTranslated(4.0,6.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//有漫反射光和镜面光，并有低高光
	glPushMatrix();
	glTranslated(-4.0,2.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,low_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//有漫反射光和镜面光，并有很亮的高光
	glPushMatrix();
	glTranslated(0.0,2.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,high_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//有漫反射光,环境光和镜面光，并有低高光
	glPushMatrix();
	glTranslated(4.0,2.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,low_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();
	
	//有漫反射光,环境光和镜面光，并有很亮的高光
	glPushMatrix();
	glTranslated(-4.0,-2.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,high_shininess);
	glutSolidTeapot(1.0);
	glPopMatrix();
	
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
		glOrtho(-10,10,-10.0/aspecratio,10.0/aspecratio,10.0,40.0);
	else
		glOrtho(-10.0*aspecratio,10.0*aspecratio,-10.0,10.0,10.0,40.0);
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