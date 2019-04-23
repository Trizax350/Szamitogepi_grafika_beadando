#include "callbacks.h"
#include "init.h"
#include <GL/glut.h>
#include <stdio.h>
#include "model.h"
#include <math.h>

// Sets the callbacks for GLUT.
void set_callbacks(){
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialFunc);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutIdleFunc(idle);
}

// Main function
int main(int argc, char* argv[]){
	int window;
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 750);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    window = glutCreateWindow("Szamitogepi grafika beadando: Horror szoba");
	glutSetWindow(window);
    init();
    glutMainLoop();
    return 0;
}