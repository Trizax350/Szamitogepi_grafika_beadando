#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"

#define size 175
int skull_can_move = 0;

void push_and_pull_skull(World* world){
	if(abs(camera.position.x) < size && abs(camera.position.z) < size){
		if(abs((int)(camera.position.x - world->skull.position.x)) < 50 && abs((int)(camera.position.z - world->skull.position.z)) < 50 && camera.position.y < 50){
			world->skull.position.x = camera.position.x + 10;
			world->skull.position.z = camera.position.z + 10;
		}
	}
}

void check_skull_position(World* world){
	if(world->skull.position.x > size || world->skull.position.x < -size || world->skull.position.z < -size || world->skull.position.z > size){
		skull_can_move = 1;
	} else if(world->skull.position.x < -10 && 
	   world->skull.position.z > 110){
		// Bed collision detection
		skull_can_move = 1;
	} else if(world->skull.position.x < -110 &&
	   world->skull.position.z < -120){
		// Crib collision detection
		skull_can_move = 1;
	} else if(world->skull.position.x > 150 &&
	   world->skull.position.z < 30 &&
	   world->skull.position.z > -20){
		// Sink collision detection
		skull_can_move = 1;
	} else if(world->skull.position.x > 145 &&
	   world->skull.position.z < 175 &&
	   world->skull.position.z > 150){
		// Toilet collision detection
		skull_can_move = 1;
	} else {
		skull_can_move = 0;
	}
}

void move_skull_forward(World* world) {
	check_skull_position(world);
	if(skull_can_move == 0){
		world->skull.position.x = world->skull.position.x + 5;
	} else {
		skull_can_move = 1;
		world->skull.position.x = 160;
		world->skull.position.z = -150;
	}
}

void move_skull_backward(World* world) {
	check_skull_position(world);
	if(skull_can_move == 0){
		world->skull.position.x = world->skull.position.x - 5;
	} else {
		skull_can_move = 1;
		world->skull.position.x = 160;
		world->skull.position.z = -150;
	}
}

void move_skull_left(World* world) {
	check_skull_position(world);
	if(skull_can_move == 0){
		world->skull.position.z = world->skull.position.z + 5;
	} else {
		skull_can_move = 1;
		world->skull.position.x = 160;
		world->skull.position.z = -150;
	}
}

void move_skull_right(World* world) {
	check_skull_position(world);
	if(skull_can_move == 0){
		world->skull.position.z = world->skull.position.z - 5;
	} else {
		skull_can_move = 1;
		world->skull.position.x = 160;
		world->skull.position.z = -150;
	}
}