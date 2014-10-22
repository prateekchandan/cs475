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

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();
	csX75::setCamera();
	Env.set_ground();
	t.drawRobot();
	glPopMatrix();


}

int main(int argc, char** argv)
{

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

