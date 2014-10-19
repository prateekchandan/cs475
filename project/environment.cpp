#include "Imageloader.hpp"
#include "environment.hpp"
#include <iostream>
#include <unistd.h>
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string.h>

// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {	
	
	glEnable(GL_TEXTURE_2D);
}


void environment::setup(){
	glLoadIdentity();
	
	
   
	
	set_ground();
}


void environment::set_ground(){
	
	
   
}

