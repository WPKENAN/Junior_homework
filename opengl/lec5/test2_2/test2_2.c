/*#include <GL/glut.h>
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(-100,0);
		glVertex2i(100,0);
		glVertex2i(0,-100);
		glVertex2i(0,100);
		glColor3f(1.0,0.0,0.0);
		glVertex2i(-80,-75);
		glVertex2i(80,85);
	glEnd();
	
	glColor3f(0.0,1.0,0.0);
	glRecti(-50,20,-30,40);

	glTranslatef(0.0,5.0,0.0);
	glRotatef(-45,0.0,0.0,1.0);
	
	glScalef(-1.0,1.0,1.0);
	glRotatef(45,0.0,0.0,1.0);
	glTranslatef(0.0,-5.0,0.0);
	glRecti(-50,20,-30,40);
	
	glFlush();

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
		gluOrtho2D(-100.0,100.0,-100.0/ratio,100.0/ratio);
	else
		gluOrtho2D(-100.0*ratio,100.0*ratio,-100.0,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("y=x+5");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}

*/

//复合矩阵变换
#include <GL/glut.h>
#include <math.h>
typedef struct
{
	GLfloat x,y;
}point;

typedef float mat3x3 [3][3];
//GLfloat matComb[3][3];
mat3x3 matComb;
const double pi = 3.14159;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void quad(point *verts)  
{
	int k;
	glBegin(GL_QUADS);
		for(k=0;k<4;k++)
			glVertex2f(verts[k].x,verts[k].y);
	glEnd();
}
void matIdentity(mat3x3 mat)
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			mat[i][j] = (i==j);
}
void matMultiply(mat3x3 m1,mat3x3 m2)
{
	int i,j;
	mat3x3 matTemp;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			matTemp[i][j] = m1[i][0]*m2[0][j] + m1[i][1]*m2[1][j]+m1[i][2]*m2[2][j];

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			m2[i][j] = matTemp[i][j];
}
void Translate2D(float tx,float ty)
{
	//float matTrans[3][3];
	mat3x3 matTrans;
	matIdentity(matTrans);

	matTrans[0][2] = tx;
	matTrans[1][2] = ty;

	matMultiply(matTrans,matComb);
}
void Symmetry()
{
	mat3x3 matSym;
	matIdentity(matSym); 

	matSym[0][0] = 0;
	matSym[0][1] = 1;
	matSym[1][0] = 1;
	matSym[1][1] = 0;

	matMultiply(matSym,matComb);
}
void transformVerts(int nverts,point *verts)
{
	int k;
	float temp;
	for(k=0;k<nverts;k++)
	{
		temp = matComb[0][0]*verts[k].x + matComb[0][1]*verts[k].y + matComb[0][2];
		verts[k].y = matComb[1][0]*verts[k].x + matComb[1][1]*verts[k].y + matComb[1][2];
		verts[k].x = temp;
	}

}
void RenderScene()
{
	// 定义四边形
	int nverts = 4;
	point verts[4] = {{-50,40},{-30,40},{-30,20},{-50,20}};

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);  //画坐标轴和对称轴
		glColor3f(0.0,0.0,0.0);
		glVertex2i(-100,0);
		glVertex2i(100,0);
		glVertex2i(0,-100);
		glVertex2i(0,100);
		glColor3f(1.0,0.0,0.0);
		glVertex2i(-80,-75);
		glVertex2i(80,85);
	glEnd();	

	//画原始四边形
	glColor3f(0.0,1.0,0.0);
	quad(verts);
	

	matIdentity(matComb);
	Translate2D(0.0,-5.0); //将对称轴平移过原点
	Symmetry();//关于y=x对称
	Translate2D(0.0,5.0);//反向平移
	
	transformVerts(nverts,verts);//将复合矩阵乘以四边形顶点

	//画对称后的四边形
	quad(verts);
	
	glFlush();

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
		gluOrtho2D(-100.0,100.0,-100.0/ratio,100.0/ratio);
	else
		gluOrtho2D(-100.0*ratio,100.0*ratio,-100.0,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("y=x+5");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}