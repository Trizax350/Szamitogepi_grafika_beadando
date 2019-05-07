#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_
#include "camera.h"
#include "skull.h"
#include <GL/glut.h>

int mouse_x, mouse_y;

struct Camera camera;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

struct Action {
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
	int increase_light;
	int decrease_light;
	int move_skull_forward;
	int move_skull_backward;
	int move_skull_left;
	int move_skull_right;
	int push_and_pull_skull;
	int isHelpOn;
	int isSourcesOn;
};

struct Action action;

// Set the callbacks for GLUT.
void set_callbacks();

// Call when need to display the graphical content.
void display();

// Call after windows resizing.
void reshape(GLsizei width, GLsizei height);

// Call after keyboard event.
void keyboard(unsigned char key, int x, int y);

// Call after key on keyboard backed up.
void keyboardUp(unsigned char key, int x, int y);

// Call when special key on keyboard is pressed. (F1 and F2)
void specialFunc(int key, int x, int y);

// Call after mouse event.
void mouse(int button, int state, int x, int y);

// Call when in motion.
void motion(int x, int y);

// Call when there is no other event.
void idle();

#endif /* INCLUDE_CALLBACKS_H_ */
