#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef unsigned char BYTE; 
using namespace std;

class environment{
	
	//! To hold world textures
	GLuint texture[3];
	
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


