#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <deque>
#include <vector>
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
	double tree[15];
	vector<pair<double,double> > tree_cordinates;
	vector<int> tree_cordinates_map;
	public:
	
    environment(){
		no_of_textures=6;
		
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
		
		tree_cordinates.push_back(pair<double,double>(-15,-15));
	}
	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

	void LoadGenList();
	
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
	
	void draw_audience();
	
	void makeCylinder(float height, float base);
	
	void drawTree(int color);
	
	void drawTreehelp(int depth,float height,float x,float y ,float z,int color);
	
	void setTreeCordinates();
	void plantTrees();
	
    
};

extern environment Env;


