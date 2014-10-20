#include "Imageloader.hpp"
#include "environment.hpp"

// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {	
	
}


void environment::setup(){
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
	gluPerspective(55,1, 0.1, 100);
	gluLookAt(0,5,2 , 0,0.5,0 , 0,1,0);
    glMatrixMode(GL_MODELVIEW);
}


void environment::set_ground(){
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(0,0,0);
	glVertex3f(0,0,3);
	glVertex3f(10,0,3);
	glVertex3f(10,0,0);
	glEnd();
}

