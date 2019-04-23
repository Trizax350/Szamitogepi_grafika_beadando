#include "camera.h"
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define size 200

double degree_to_radian(double degree){
	return degree * M_PI / 180.0;
}

void can_move(struct Camera* camera){
    if(camera->position.x > size || camera->position.x < -size || camera->position.z < -size || camera->position.z > size){
		camera->position=camera->prev_position;
	}
	
	// Bed collision detection
	if(camera->position.x < -10 && 
	   camera->position.y < 60 &&
	   camera->position.z > 110){
		camera->position=camera->prev_position;
	}
	
	// Bed railing1 collision detection
	if(camera->position.x < -10 && 
	   camera->position.x > -20 && 
	   camera->position.y < 80 &&
	   camera->position.z > 110){
		camera->position=camera->prev_position;
	}
	
	// Bed railing2 collision detection
	if(camera->position.x < -185 && 
	   camera->position.x > -200 && 
	   camera->position.y < 80 &&
	   camera->position.z > 110){
		camera->position=camera->prev_position;
	}
	
	// Hanginglight1 collision detection
	if(camera->position.x > 75 &&
	   camera->position.x < 125 &&
	   camera->position.y > 150 && 
	   camera->position.y < 180 && 
	   camera->position.z > -60 &&
	   camera->position.z < 60){
		camera->position=camera->prev_position;
	}
	
	// Hanginglight2 collision detection
	if(camera->position.x < -75 &&
	   camera->position.x > -125 &&
	   camera->position.y > 150 && 
	   camera->position.y < 180 && 
	   camera->position.z > -60 &&
	   camera->position.z < 60){
		camera->position=camera->prev_position;
	}
	
	// Crib collision detection
	if(camera->position.x < -110 &&
	   camera->position.y < 80 && 
	   camera->position.z < -120){
		camera->position=camera->prev_position;
	}
	
	// Sink collision detection
	if(camera->position.x > 150 &&
	   camera->position.y < 70 &&
	   camera->position.z < 30 &&
	   camera->position.z > -20){
		camera->position=camera->prev_position;
	}
	
	// Toilet collision detection
	if(camera->position.x > 145 &&
	   camera->position.y < 50 &&
	   camera->position.z < 175 &&
	   camera->position.z > 150){
		camera->position=camera->prev_position;
	}
	
	// Toilet tank collision detection
	if(camera->position.x > 175 &&
	   camera->position.y < 80 &&
	   camera->position.z < 185 &&
	   camera->position.z > 140){
		camera->position=camera->prev_position;
	}
}

void init_camera(struct Camera* camera){
	camera->position.x = 0;
	camera->position.y = 100;
	camera->position.z = -150;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = 180;
}

void set_view_point(const struct Camera* camera){
	glRotatef(-(camera->pose.x), 1.0, 0, 0);
	glRotatef(-(camera->pose.z), 0, 1.0, 0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);

}

void rotate_camera(struct Camera* camera, double horizontal, double vertical){
	double fallbackPoseOfX;

	// Vertical
	if(camera->pose.x >= 0 && camera->pose.x <= 90){
		fallbackPoseOfX = 90;
	} else {
		fallbackPoseOfX = 270;
	}

	if(camera->pose.x + vertical > 90 && camera->pose.x + vertical < 270){
		camera->pose.x = fallbackPoseOfX;
	} else {
		camera->pose.x += vertical;
	}

	if(camera->pose.x  > 90 && camera->pose.x < 270){
		set_clear_camera_pose(camera);
	}

	// Horizontal
	camera->pose.z += horizontal;
	if(camera->pose.z < 0){
		camera->pose.z += 360.0;
	}

	if(camera->pose.z > 360.0){
		camera->pose.z -= 360.0;
	}

	if(camera->pose.x < 0){
		camera->pose.x += 360.0;
	}

	if(camera->pose.x > 360.0){
		camera->pose.x -= 360.0;
	}
}

void set_clear_camera_pose(struct Camera* camera){
	camera->pose.x = 0;
}

void move_camera_forward(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void move_camera_backward(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z += cos(angle) * distance;
	camera->position.x += sin(angle) * distance;
    can_move(camera);
}

void step_camera_left(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z + 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void step_camera_right(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z - 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void move_camera_up(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
    if(camera->position.y<size-10){
		camera->position.y += distance;
	}
    can_move(camera);
}

void move_camera_down(struct Camera* camera, double distance){
	camera->prev_position = camera->position;
	if(camera->position.y>10){
		camera->position.y -= distance;
	}
    can_move(camera);
}