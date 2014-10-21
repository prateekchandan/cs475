#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

typedef unsigned char BYTE; 
using namespace std;

class environment{
	
	//! To hold world textures
	GLuint texture[100]; // Max 100 textures
	int no_of_textures;
	
	int sunlight,moonlight;
	
	public:
	
    environment(){
		no_of_textures=4;
		
		sunlight=1;
		moonlight=0;
	}
	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

	/// For setting up ground
	
	void set_ground();
	/// For Complete setup of environment
	void setup();
	
	void set_env_lightings();
	
	void toggle_Sunlight();

    
};

extern environment Env;


