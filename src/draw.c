#include "GL/glut.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "draw.h"
#include "model.h"
#include "callbacks.h"

double sizeOfRoom = 200;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_content(World* world){
	Room roomToDraw = world -> room;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_left(roomToDraw);
		draw_right(roomToDraw);
		draw_back(roomToDraw);
		draw_front(roomToDraw);
		draw_top(roomToDraw);
		draw_ground(roomToDraw);
	glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_default);
}

void draw_bed_model(World* world){
	glPushMatrix();
		glTranslatef(world->bed.position.x, world->bed.position.y, world->bed.position.z);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->bed.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->bed.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->bed.model);
    glPopMatrix();
}

void draw_skull_model(World* world){
	glPushMatrix();
		glTranslatef(world->skull.position.x, world->skull.position.y, world->skull.position.z);
		glRotatef(250.0, 1.0, 0.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->skull.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->skull.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->skull.model);
    glPopMatrix();
}

void draw_sink_model(World* world){
	glPushMatrix();
		glTranslatef(world->sink.position.x, world->sink.position.y, world->sink.position.z);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->sink.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->sink.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->sink.model);
    glPopMatrix();
}

void draw_toilet_model(World* world){
	glPushMatrix();
		glTranslatef(world->toilet.position.x, world->toilet.position.y, world->toilet.position.z);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->toilet.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->toilet.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->toilet.model);
    glPopMatrix();
}

void draw_crib_model(World* world){
	glPushMatrix();
		glTranslatef(world->crib.position.x, world->crib.position.y, world->crib.position.z);
		glRotatef(140.0, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->crib.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->crib.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->crib.model);
    glPopMatrix();
}

void draw_hanginglight_model(World* world){
	glPushMatrix();
		glTranslatef(world->hanginglight1.position.x, world->hanginglight1.position.y, world->hanginglight1.position.z);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->hanginglight1.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->hanginglight1.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->hanginglight1.model);
    glPopMatrix();
	
	glPushMatrix();
		glTranslatef(world->hanginglight2.position.x, world->hanginglight2.position.y, world->hanginglight2.position.z);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->hanginglight2.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world->hanginglight2.texture);
		glScalef(10.0f, 10.0f, 10.0f);
		draw_model(&world->hanginglight2.model);
    glPopMatrix();
}

void draw_ground(Room room){
	glBindTexture(GL_TEXTURE_2D, room.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for(x = -sizeOfRoom; x < sizeOfRoom; x += 50){
		for(z = -sizeOfRoom; z < sizeOfRoom; z += 50){
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}

void draw_left(Room room){
	glBindTexture(GL_TEXTURE_2D, room.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
	glEnd();
}

void draw_right(Room room){
	glBindTexture(GL_TEXTURE_2D, room.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, 0, sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
	glEnd();
}

void draw_front(Room room){
	glBindTexture(GL_TEXTURE_2D, room.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glEnd();
}

void draw_back(Room room){
	glBindTexture(GL_TEXTURE_2D, room.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfRoom, 0, sizeOfRoom);
	glEnd();
}

void draw_top(Room room){
	glBindTexture(GL_TEXTURE_2D, room.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glEnd();
}

void draw_triangles(const struct Model* model){
	int i, k;
	int vertex_index, texture_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);
	for(i = 0; i < model->n_triangles; ++i){
		for(k = 0; k < 3; ++k){
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);
		}
	}
	glEnd();
}

void draw_quads(const struct Model* model){
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);
    for(i = 0; i < model->n_quads; ++i){
        for(k = 0; k < 4; ++k){
            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }
    glEnd();
}

void draw_normals(const struct Model* model, double length){
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	for(i = 0; i < model->n_vertices; ++i){
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * length;
		y2 = y1 + model->normals[i].y * length;
		z2 = z1 + model->normals[i].z * length;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}

void draw_model(const struct Model* model){
	draw_triangles(model);
	draw_quads(model);
}

void draw_help_and_sources(int texture){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}