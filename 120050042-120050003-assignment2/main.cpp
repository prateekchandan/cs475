#include "gl_framework.hpp"
#include "common.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;






void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();			
	glRotatef(t.xrotate, 1, 0, 0);
	glRotatef(t.yrotate, 0, 1, 0);
	glRotatef(t.zrotate, 0, 0, 1);
	t.drawRobot();

}

int main(int argc, char** argv)
{

	cout <<	"Animation sequence can be toggled even while the transformation is in progress. ";
	cout << "Press <ENTER> to toggle animation.\n";
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 640, "CS475/CS675 OpenGL Framework", NULL, NULL);
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

	//Print and see what context got enabled
	//std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	//std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	//std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
	//std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;


	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();


	t.createDisplayLists();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{

		// Render here
		renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

