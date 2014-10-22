#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <time.h> 
#include <cmath>

typedef unsigned char BYTE; 
using namespace std;

class environment{
	
	//! To hold world textures
	GLuint texture[100]; // Max 100 textures
	int no_of_textures;
	// Variables to control roads
	deque<float> road_angles;
	int road_no;
	
	int sunlight,moonlight;
	
	public:
	
    environment(){
		no_of_textures=4;
		
		sunlight=1;
		moonlight=0;
		
		float a=0;
		road_angles.push_back(a);
		road_no=0;
		srand (time(NULL));
		for (int i = 0; i < 100; i++)
		{
			a=(rand()%40 - 20)*M_PI/180.0;
			road_angles.push_back(a);
		}
		a=0;
		for (int i = 0; i < 100; i++)
		{
			a=(rand()%40 - 20)*M_PI/180.0;
			road_angles.push_front(a);
		}
		
		
	}
	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

	/// For setting up ground
	
	void set_ground();
	/// For Complete setup of environment
	void setup();
	
	void set_env_lightings();
	
	void toggle_Sunlight();
	
	void set_roads();
	
	void draw_curved_road();
	void draw_curved_road_90();
	void draw_straight_road();
    
};

extern environment Env;


