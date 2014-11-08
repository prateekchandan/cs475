#include "gl_framework.hpp"
#include "environment.hpp"
#include "transformer.hpp"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

transformer t;
environment Env;
int key;
bool recording = false;
int SCREEN_HEIGHT=640 , SCREEN_WIDTH=640;
unsigned char *pRGB;
unsigned int framenum=0;


struct keyframe{
	
};

void capture_frame(unsigned int framenum);

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();
	csX75::setCamera();
	Env.set_environment();
	t.drawRobot();
	key++;
	if(t.continuous || !recording)t.frame_index++;
	if(!recording) csX75::importKeyframe(); 
	if(t.state_export && recording) csX75::exportStateKeyframe();
	if(t.continuous) csX75::exportKeyframe();
	csX75::store_past();
	glPopMatrix();

	
	if(!recording)
	capture_frame(framenum++);

}

void capture_frame(unsigned int framenum)
{
  pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"./frames/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

 
  delete pRGB;
}



int main(int argc, char** argv)
{
	while(1){
		cerr<<"Recording or Not (y/n) : ";
		char c;
		cin>>c;
		if(c=='y'||c=='Y')
		{
			recording=true;
			break;
		}
		else if(c=='n' || c=='N')
		{
			recording=false;
			break;
		}
	}


	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CS475/CS675 OpenGL Framework", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cerr<<"GLEW Init Failed : %s"<<std::endl;
	}

	
	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();
	
	// Load the textures required in the drawings
	Env.LoadGLTextures();
	t.LoadGLTextures();
	
	// GEnerates all display lists required for rigid structures
	t.createDisplayLists();
	Env.setup();
	if(!recording) t.keyfile.open("keys.txt" , ios::in);
	else t.keyfile.open("keys.txt" , ios::out);



	
	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{

		// Render here
		renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		csX75::doTurnings();

	}

	glfwTerminate();
	return 0;
}

