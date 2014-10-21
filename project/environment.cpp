#include "environment.hpp"
#include <iostream>
#include <SOIL/SOIL.h>

// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {
	
	char a[100][100];
	
	strcpy(a[0],"img/road.jpg");
	strcpy(a[1],"img/grass.jpg");
	strcpy(a[2],"img/sky.jpg");
	strcpy(a[3],"img/horizon.jpg");
	
	for (int i = 0; i < no_of_textures; i++)
	{
		texture[i]=SOIL_load_OGL_texture(
			a[i],
			 SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
		if(texture[i] == 0)
		{
			cout<<"Failed to load "<<a[i]<<" : "<<SOIL_last_result()<<"\n";
		}
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	
	glEnable(GL_TEXTURE_2D);
};


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
    
	gluPerspective(50,1, 0.1, -1000);
	gluLookAt(0,5,2 , 0,0.5,0 , 0,1,0);
    glMatrixMode(GL_MODELVIEW);
    
}


void environment::set_ground(){
	
	glEnable(GL_TEXTURE_2D);
	
	// Drawing grass
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1,1,1);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+10*i,-0.1,-90+10*j);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(-90+10*i,-0.1,-90+10*j);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(-90+10*i,-0.1,-100+10*j);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+10*i,-0.1,-100+10*j);
			glEnd();
		}
	}
	
	// Drawing sky
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,5,100);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(100,5,100);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(100,5.1,-100);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,5,-100);
	glEnd();
	
	// Draeing horizon
	
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,5.2,80);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100,5.2,80);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100,-0.2,80);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,-0.2,80);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,5.2,-80);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100,5.2,-80);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100,-0.2,-80);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,-0.2,-80);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(80,5.2,-100);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(80,5.2,100);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(80,-0.2,100);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(80,-0.2,-100);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-80,5.2,-100);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-80,5.2,100);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-80,-0.2,100);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-80,-0.2,-100);
	glEnd();
	
	
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor3f(0.0,0.1,0.3);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2,0,5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(2,0,5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(2,0,-5);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-2,0,-5);
	glEnd();
	glPopMatrix();
}

