#include <gl/glut.h>
#include <math.h>
typedef struct {
	float x,y;
}point;
void init()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}
/*int LineDDA(int x0,int y0,int x1,int y1,point pixels[])
{
	/*int x,num=0;
	float dy,dx,y,m;
	dx = x1-x0;
	dy = y1-y0;
	m = dy/dx;
	y = y0;
	for(x=x0;x<=x1;x++)
	{
		pixels[num].x = x;
		pixels[num].y = y;
		y += m;
		num ++;
	}
	return num;
	int num,x,y,dx,dy;
	float k,xf,yf;
	dx = x1-x0;
	dy = y1-y0;
	num = 0;
	k = dy*1.0/dx;
	if(dx==0) //垂直线
	{
		for(y=y0;y<=y1;y++)
		{
			pixels[num].x = x0;
			pixels[num].y = y;
			num ++;
		}

	}
	else if(dy==0) //水平线
	{
		for(x=x0;x<=x1;x++)
		{
			pixels[num].x = x;
			pixels[num].y = y0;
			num ++;
		}
	}
	else if(fabs(k)<=1)//斜率在(0,45]和[135,180]之间的线
	{
		yf = y0;
		for(x=x0;x<=x1;x++)
		{
			pixels[num].x = x;
			pixels[num].y = yf;
			num ++;
			yf += k;
		}
	}
	else//斜率在(45,90）和(90,135)之间的线
	{
		xf = x0;
		for(y=y0;y<=y1;y++)
		{
			pixels[num].x = xf;
			pixels[num].y = y;
			num ++;
			xf += 1/k;
		}
	}
	return num;
}*/
void WritePixelline(int x,int y)
{
       glBegin(GL_POINTS);
			glVertex2f(x,y);
	 glEnd();
}
void MidpointLine (int x0,int y0,int x1, int y1)
{
	int a,b,d1,d2,d,x,y;
    a=y0-y1;
	b=x1-x0;
	double dx,dy,k;
	dx=a;dy=-1.0*b;
	k=dy/dx;
	d=2*a+b;
    d1=2*a;
	d2=2*(a+b);
    x=x0;y=y0;
    WritePixelline(x,y);
	if(a==0)//水平线
	{
		while(x<x1)
		{
			x++;
		    WritePixelline(x, y);
		}
	}
	else if(b==0)//垂直线
	{
		while(y<y1)
		{
			y++;
		    WritePixelline(x, y);
		}
	}
    else 
	{
		if(fabs(k)<=1)
		{
			while(x<x1)
			{ 
				if(d<0)
				{
					x++;
					y++;
					d+=d2;
				}
				else
				{
					x++;
					d+=d1;
				}
				WritePixelline(x, y);
			}
		
		}
		if(fabs(k)>1)
		{
			while(y<y1)
			{ 
				if(d<0)
				{
					x++;
					y++;
					d+=d2;
				}
				else
				{
					y++;
					d+=d1;
				}
				WritePixelline(x,y);
			}
		
		}
	}
 }
/*void drawLine(int x1,int y1,int x2,int y2)
{
	point pixels[100];
	int num;
	int i;
	num = LineDDA(x1,y1,x2,y2,pixels);
	glBegin(GL_POINTS);
		for(i=0;i<num;i++)
			glVertex2f(pixels[i].x,pixels[i].y);
	glEnd();
}*/
void  WritePixel(int x,int y)
{
     glBegin(GL_POINTS);
			glVertex2f(x,y);
			glVertex2f(y,x);
			glVertex2f(-x,y);
			glVertex2f(-y,x);
			glVertex2f(x,-y);
			glVertex2f(y,-x);
			glVertex2f(-x,-y);
			glVertex2f(-y,-x);
	glEnd();
}

void MidpointCircle3(int r)
 {
          int x,y,d;
          x=0; y=r; 
	      d=1-r;
          WritePixel(x,y);
          while(x<y)
	    {
		 if(d<0)
		 { 
			 d+=2*x+3;
			 x++;
		 }
          else
		  {
			  d+=2*(x-y)+5;
			  x++;y--;
		  }
		 WritePixel(x,y);
          }
 }

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,1.0f);
	//drawLine(10,10,80,-60);
    MidpointLine(10,10,60,80);
	MidpointCircle3(8);
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
		glOrtho(-100.0,100.0,-100.0/aspectRatio,100.0/aspectRatio,1.0,-1.0);
	else
		glOrtho(-100.0*aspectRatio,100.0*aspectRatio,-100.0,100.0,1.0,-1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("LineDDA");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}