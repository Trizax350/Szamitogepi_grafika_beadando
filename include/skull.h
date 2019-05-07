#ifndef INCLUDE_MOVE_H_
#define INCLUDE_MOVE_H_
#include "model.h"

int skull_can_move;

// Move skull object forward
void move_skull_forward(World* world);

// Move skull object backward
void move_skull_backward(World* world);

// Move skull object left
void move_skull_left(World* world);

// Move skull object right
void move_skull_right(World* world);

// Push or/and pull skull object with camera
void push_and_pull_skull(World* world);

// Check skull position
void check_skull_position(World* world);

// Returns the elapsed time since the program started.
double calc_elapsed_time();

// Refreshes the position of the camera.
void update_camera_position(struct Camera* camera, double elapsed_time);

// Moves skull object forward.
void move_skull_forward(World* world);

// Moves skull object backward.
void move_skull_backward(World* world);

// Moves skull object left.
void move_skull_left(World* world);

// Moves skull object right.
void move_skull_right(World* world);

// Push and pull skull object with camera.
void push_and_pull_skull(World* world);

#endif /* INCLUDE_MOVE_H_ */