#include "bits/stdc++.h"
#include "omp.h"
#include "GL/glut.h"
using namespace std;

#define SIZE 1000
#define NUM_THREADS 4

int *matrix[SIZE];

enum color{
	RED,GREEN,BLUE,YELLOW,PURPLE,CYAN,BLACK
};

int inSet(double creal,double cimage)  
{  
    int iterations = 0;  
    double zreal=0,zimage=0;
	double freal=0,fimage=0;
    while ((freal*freal+fimage*fimage<4) && (iterations < 1000))  
    {  
		freal=zreal*zreal-zimage*zimage+creal;
		fimage=2*zreal*zimage+cimage;
		zreal=freal;
		zimage=fimage;
		iterations++;  
    }  
    return iterations;  
}  

void plotfunc(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);

	//绘制坐标系
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(-2.0,0.0);
	glVertex2f(2.0,0.0);
	glVertex2f(0.0,-2.0);
	glVertex2f(0.0,2.0);
	glEnd();

	//绘制图像
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			switch(matrix[i][j]%6){
				case 0:
					glColor3f(1.0,0.0,0.0);break;
				case 1:
					glColor3f(0.0,1.0,0.0);break;
				case 2:
					glColor3f(0.0,0.0,1.0);break;
				case 3:
					glColor3f(1.0,1.0,0.0);break;
				case 4:
					glColor3f(1.0,0.0,1.0);
					if(matrix[i][j]==1000)glColor3f(0.0,0.0,0.0);
					break;
				case 5:
					glColor3f(0.0,1.0,1.0);break;
			}
			glBegin(GL_POINTS);
			glVertex2f(((double)i -(SIZE/2)) / (SIZE/4),((double)j -(SIZE/2)) / (SIZE/4));
			glEnd();
		}
	}
	glFlush();
}

void draw(){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Mandelbrot");
	glutDisplayFunc(&plotfunc);
	glClearColor(1,1,1,1);
	gluOrtho2D(-2.0,2.0,-2.0,2.0);
	glutMainLoop();
//	gluOrtho2D(-SIZE/2,SIZE/2,-SIZE/2,SIZE/2);



}
int main(int argc, char *argv[]){
	for (int i = 0; i < SIZE; i++){	  
		matrix[i] = (int* )malloc( SIZE*sizeof(int) );  
	}

	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int id=omp_get_thread_num();
		double start=omp_get_wtime();
		for(int i=id;i<SIZE;i+=NUM_THREADS){
			for(int j=0;j<SIZE;j++){
				double x=((double)i -(SIZE/2)) / (SIZE/4);
				double y=((double)j -(SIZE/2)) / (SIZE/4);
				matrix[i][j]=inSet(x,y);

			}
		}
		double end=omp_get_wtime();
		cout << end-start << endl;
	}

//	for(int i=0;i<SIZE;i++){
//		for(int j=0;j<SIZE;j++){
//			if(matrix[i][j]>2&&matrix[i][j]<900)
//			cout << matrix[i][j] << ' ';
//		}
//		cout << endl;
//	}
//	
	glutInit(&argc,argv);
	draw();
	return 0;
}
