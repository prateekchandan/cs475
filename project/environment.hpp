#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

typedef unsigned char BYTE; 
using namespace std;

class environment{
	
	//! To hold world textures
	GLuint texture[100]; // Max 100 textures
	int no_of_textures;
	
	
	public:
	
    environment(){
		no_of_textures=4;
		
	}
	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

	/// For setting up ground
	
	void set_ground();
	/// For Complete setup of environment
	void setup();

    
};

extern environment Env;


