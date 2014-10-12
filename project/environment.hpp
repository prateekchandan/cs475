#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string.h>

typedef unsigned char BYTE; 
using namespace std;

class environment{
	
	public:
	
    environment(){
	}
	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

	/// For setting up ground
	
	void set_ground();
	/// For Complete setup of environment
	void setup();
    
};

extern environment Env;


