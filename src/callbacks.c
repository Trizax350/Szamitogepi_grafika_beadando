#include <math.h>
#include "callbacks.h"
#include "init.h"
#include "draw.h"
#include "model.h"
#include "skull.h"
#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

void display(void){
	double elapsed_time = calc_elapsed_time();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	update_camera_position(&camera, elapsed_time);
	draw_content(&world);
	draw_bed_model(&world);
	draw_sink_model(&world);
	draw_skull_model(&world);
	draw_crib_model(&world);
	draw_toilet_model(&world);
	draw_hanginglight_model(&world);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.1, 20000.0);

	set_view_point(&camera);

	if(action.isHelpOn == TRUE){
		GLfloat torchForHelp[] = {0.8, 0.8, 0.8, 0.8};
		glLightfv(GL_LIGHT1, GL_AMBIENT, torchForHelp);

		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		draw_help_and_sources(world.helpTexture);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	} else if(action.isSourcesOn == TRUE){
		GLfloat torchForSources[] = {0.8, 0.8, 0.8, 0.8};
		glLightfv(GL_LIGHT1, GL_AMBIENT, torchForSources);

		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		draw_help_and_sources(world.sourcesTexture);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){
    int x, y;
	double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        WINDOW_WIDTH = (int)((double)height * VIEWPORT_RATIO);
        WINDOW_HEIGHT = height;
		x = (width - WINDOW_WIDTH) / 2;
        y = 0;
    } else {
        WINDOW_WIDTH = width;
        WINDOW_HEIGHT = (int)((double)width / VIEWPORT_RATIO);
		x = 0;
        y = (height - WINDOW_HEIGHT) / 2;
    }
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.1, 20000.0);
	glViewport(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	set_view_point(&camera);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'w':
		action.move_forward = TRUE;
		break;
	case 's':
		action.move_backward = TRUE;
		break;
	case 'a':
		action.step_left = TRUE;
		break;
	case 'd':
		action.step_right = TRUE;
		break;
	case 'c':
		action.move_down = TRUE;
		break;
	case 32:
		action.move_up = TRUE;
		break;
	case '+':
		action.increase_light = TRUE;
		break;
	case '-':
		action.decrease_light = TRUE;
		break;
	case 'j':
		action.move_skull_forward = TRUE;
		break;
	case 'l':
		action.move_skull_backward = TRUE;
		break;
	case 'i':
		action.move_skull_left = TRUE;
		break;
	case 'k':
		action.move_skull_right = TRUE;
		break;
	case 'e':
		action.push_and_pull_skull = TRUE;
		break;
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y){
	switch(key){
	case 'w':
		action.move_forward = FALSE;
		break;
	case 's':
		action.move_backward = FALSE;
		break;
	case 'a':
		action.step_left = FALSE;
		break;
	case 'd':
		action.step_right = FALSE;
		break;
	case 'c':
		action.move_down = FALSE;
		break;
	case 32:
		action.move_up = FALSE;
		break;
	case '+':
		action.increase_light = FALSE;
		break;
	case '-':
		action.decrease_light = FALSE;
		break;
	case 'j':
		action.move_skull_forward = FALSE;
		break;
	case 'l':
		action.move_skull_backward = FALSE;
		break;
	case 'i':
		action.move_skull_left = FALSE;
		break;
	case 'k':
		action.move_skull_right = FALSE;
		break;
	case 'e':
		action.push_and_pull_skull = FALSE;
		break;
	}
	glutPostRedisplay();
}

void specialFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_F1:
			if(action.isHelpOn == TRUE){
				action.isHelpOn = FALSE;
			} else {
				action.isHelpOn = TRUE;
			}
			
			if(action.isSourcesOn == TRUE){
				action.isSourcesOn = FALSE;
			}
		break;
		case GLUT_KEY_F2:
			if(action.isSourcesOn == TRUE){
				action.isSourcesOn = FALSE;
			} else {
				action.isSourcesOn = TRUE;
			}
			
			if(action.isHelpOn == TRUE){
				action.isHelpOn = FALSE;
			}
		break;
	}
}

void mouse(int button, int state, int x, int y){
	mouse_x = x;
	mouse_y = y;
}

void motion(int x, int y){
	rotate_camera(&camera, mouse_x - x, mouse_y - y);
    mouse_x = x;
	mouse_y = y;
    glutPostRedisplay();
}

void idle(){
    glutPostRedisplay();
}

double calc_elapsed_time(){
	static int last_frame_time = 0;
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - last_frame_time) / 1000.0;
	last_frame_time = current_time;

	return elapsed_time;
}

void update_camera_position(struct Camera* camera, double elapsed_time){
	float speed = 30;
	double distance;

	distance = elapsed_time * CAMERA_SPEED*speed;
	if(action.move_forward == TRUE){
		move_camera_forward(camera, distance);
	}

	if(action.move_backward == TRUE){
		move_camera_backward(camera, distance);
	}

	if(action.step_left == TRUE){
		step_camera_left(camera, distance);
	}

	if(action.step_right == TRUE){
		step_camera_right(camera, distance);
	}

	if(action.move_up == TRUE){
		move_camera_up(camera, distance);
	}

	if(action.move_down == TRUE){
		move_camera_down(camera, distance);
	}

	if(action.increase_light == TRUE){
		if(light_ambient[0] < 1){
			light_ambient[0] = light_ambient[1] = light_ambient[2] += 0.01;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		}
	}

	if(action.decrease_light == TRUE){
		if(light_ambient[0] > -0.60){
			light_ambient[0] = light_ambient[1] = light_ambient[2] -= 0.01;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		}
	}

	if(action.move_skull_forward == TRUE){
		move_skull_forward(&world);
	}
	
	if(action.move_skull_backward == TRUE){
		move_skull_backward(&world);
	}
	
	if(action.move_skull_left == TRUE){
		move_skull_left(&world);
	}
	
	if(action.move_skull_right == TRUE){
		move_skull_right(&world);
	}
	
	if(action.push_and_pull_skull == TRUE){
		push_and_pull_skull(&world);
	}
}