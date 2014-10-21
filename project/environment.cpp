#include "Imageloader.hpp"
#include "environment.hpp"
#include <iostream>

// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {
	
	// Load Texture
	Image *image[100];
	
	for (int i = 0; i < no_of_textures; i++)
	{
		image[i] = (Image *) malloc(sizeof(Image));
		if(image[i]==NULL){
			printf("Error allocating space for image\n");
			exit(0);
		}
	}
	
	Imageloader img_loader;
	char image_name[100][100];
	
	strcpy(image_name[0],"./img/skin.bmp");
	
	for (int i = 0; i < no_of_textures; i++)
	{
		if (!img_loader.ImageLoad(image_name[i], image[i])) {
			//exit(0);
		} 
	}
	
	for (int i = 0; i < no_of_textures; i++)
	{
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);   // 2d texture (x and y size)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image[i]->sizeX, image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->data);
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
    
	gluPerspective(55,1, 0.1, 100);
	gluLookAt(0,5,2 , 0,0.5,0 , 0,1,0);
    glMatrixMode(GL_MODELVIEW);
}


void environment::set_ground(){
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(-2,0,5);
	glVertex3f(2,0,5);
	glVertex3f(2,0,-5);
	glVertex3f(-2,0,-5);
	glEnd();
}

