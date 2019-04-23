#ifndef INCLUDE_MOVE_H_
#define INCLUDE_MOVE_H_
#include "model.h"

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

#endif /* INCLUDE_MOVE_H_ */
