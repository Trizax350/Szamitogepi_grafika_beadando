#include "model.h"
#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_
#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif

// Draw the content.
void draw_content(World* world);

// Draw the models.
void draw_bed_model(World* world);
void draw_sink_model(World* world);
void draw_toilet_model(World* world);
void draw_crib_model(World* world);
void draw_skull_model(World* world);
void draw_hanginglight_model(World* world);

// Draws the ground.
void draw_ground(Room room);

// Draws the room.
void draw_left(Room room);

void draw_right(Room room);

void draw_back(Room room);

void draw_front(Room room);

void draw_top(Room room);

// Draw the model.
void draw_model(const struct Model* model);

// Draw the help info and sources info texture.
void draw_help_and_sources(int texture);

#endif /* INCLUDE_DRAW_H_ */
