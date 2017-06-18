#include<GL/glut.h>
float ctrlpoints[4][3]= {{-4.0,-4.0,0.0},{-2.0,4.0,0.0},{2.0,-4.0,0.0},{4.0,4.0,0.0}};
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void DrawCurve(int n)
{
	double t,deltat;
	int i;
	glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);	
	deltat = 1.0/(n-1);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<n;i++)
		{
			t = i*deltat;
			glEvalCoord1f(t);
		}
	glEnd();
	
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex3f(ctrlpoints[i][0],ctrlpoints[i][1],ctrlpoints[i][2]);
	glEnd();
	
}
void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	DrawCurve(100);
	
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
		glOrtho(-5.0,5.0,-5.0/aspectRatio,5.0/aspectRatio,1.0,-1.0);
	else
		glOrtho(-5.0*aspectRatio,5.0*aspectRatio,-5.0,5.0,1.0,-1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("DrawBezier");
	
	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}
