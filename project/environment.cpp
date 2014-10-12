#include "Imageloader.hpp"
#include "environment.hpp"

// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {	
	
	//glEnable(GL_TEXTURE_2D);
}


void environment::setup(){
	glLoadIdentity();
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   
	
	set_ground();
}


void environment::set_ground(){
	glPushMatrix();
	glScalef(99, 1, 99);

	glDepthRange(1.0,1.0);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);

	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);

	glColor3f(0, 1, 0);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);

	glEnd();
	glDepthRange(0.0,1.0);

	glPopMatrix();
}

