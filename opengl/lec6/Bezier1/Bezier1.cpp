#include<GL/glut.h>
typedef struct{
	float x,y,z;
}Point;
Point ctrlpoints[4]= {{-4.0,-4.0,0.0},{-2.0,4.0,0.0},{2.0,-4.0,0.0},{4.0,4.0,0.0}};
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void DrawCurve(int n)
{
	Point p;
	double t,deltat,t2,t3,et,et2,et3;
	int i;
	deltat = 1.0/(n-1);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<100;i++)
		{
			t = i*deltat;
			et = 1-t;
			t2 = t*t;
			et2 = et*et;
			t3 = t*t2;
			et3 = et*et2;
			p.x = et3*ctrlpoints[0].x+3*t*et2*ctrlpoints[1].x+3*t2*et*ctrlpoints[2].x+t3*ctrlpoints[3].x;
			p.y = et3*ctrlpoints[0].y+3*t*et2*ctrlpoints[1].y+3*t2*et*ctrlpoints[2].y+t3*ctrlpoints[3].y;
			p.z = et3*ctrlpoints[0].z+3*t*et2*ctrlpoints[1].z+3*t2*et*ctrlpoints[2].z+t3*ctrlpoints[3].z;
			glVertex3f(p.x,p.y,p.z);
		}
	glEnd();
	
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex3f(ctrlpoints[i].x,ctrlpoints[i].y,ctrlpoints[i].z);
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
