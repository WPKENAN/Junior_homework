#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h> 


void init();

void display();

int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(300,300);
	glutCreateWindow("First");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void init(){
	glClearColor(0.0,0.0,0.0,1.0);

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
