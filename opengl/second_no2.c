#include <GL/glut.h>
void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
//	gluOrtho2D(-300,300,-200,200);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,1.0);
	glVertex2f(0,60);
	glVertex2f(0,150);
	glVertex2f(50,150);
	glVertex2f(50,60);
	glEnd();
	glColor3f(0.0,0.0,0.0);

	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(100,103);
	glEnd();
//	glRectf(0.0,10.0,50.0,100.0);
	

//	glColor3f(1.0,0.0,0.0);
//	glTranslatef(0.0,-5.0,0.0);
//	glRectf(50.0,100.0,200.0,150.0);
	
//	glRectf(50.0,100.0,200.0,150.0);
//	

//	glLoadIdentity();
//	glColor3f(0.0,1.0,0.0);
//	glTranslatef(0,50.0,0.0);
//	glRotatef(-90.0,0.0,0.0,1.0);
//
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(60,3);
	glVertex2f(150,3);
	glVertex2f(150,53);
	glVertex2f(60,53);
	glEnd();

	

//	glRectf(0.0,10.0,50.0,100.0);

//	glRotatef(-90,0,0,1);
//	glLoadIdentity();
//	glColor3f(1.0,1.0,0.0);
//	glScalef(0.5,1.0,1.0);
//	glRectf(50.0,100.0,200.0,150.0);

	glFlush();
}
void ChangeSize(GLsizei w,GLsizei h)
{
	float ratio;
	if(h==0)
		h = 1;
	ratio = (GLfloat)w/(GLfloat)h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<=h)
		gluOrtho2D(-200.0,200.0,-200.0/ratio,200.0/ratio);
	else
		gluOrtho2D(-200.0*ratio,200.0*ratio,-200.0,200);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(400,400);
	glutCreateWindow("Geometric transformation 2");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}
