#include "gl_framework.hpp"
#include "common.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

float points[] = {
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};


float rtri = 0.0f;
float rall1 = 0.0f, rall2 = 0.0f, rall3 = 0.0f;



/*
double max_wheel3_rot = -90;
double wheel3_rot_speed = max_wheel3_rot/steps;
double cur_wheel3_rot = 0;

double max_wheel3_disp = -0.1;
double wheel3_disp_speed = max_wheel3_disp/steps;
double cur_wheel3_disp = 0;

void animateWheel3() {
	if(sequence_number >= 24) {
		if(sequence_number == 24) {
			glTranslatef(0, cur_wheel3_disp, 0);
			cur_wheel3_disp += wheel3_disp_speed;
			if(cur_wheel3_disp <= max_wheel3_disp) sequence_number++;
		}
		else glTranslatef(0, max_wheel3_disp, 0);
	}
	if(sequence_number >= 22) {
		if(sequence_number == 22) {
			glTranslatef(0.05,0,0.1);
			glRotatef(cur_wheel3_rot, 0, 1, 0);
			glTranslatef(-0.05,0,-0.1);
			cur_wheel3_rot += wheel3_rot_speed;
			if(cur_wheel3_rot <= max_wheel3_rot) sequence_number++;
		}
		else{
			glTranslatef(0.05,0,0.1);
			glRotatef(max_wheel3_rot, 0, 1, 0);
			glTranslatef(-0.05,0,-0.1);
		}
	}
}


double max_wheel4_rot = 90;
double wheel4_rot_speed = max_wheel4_rot/steps;
double cur_wheel4_rot = 0;

double max_wheel4_disp = -0.1;
double wheel4_disp_speed = max_wheel4_disp/steps;
double cur_wheel4_disp = 0;

void animateWheel4() {
	if(sequence_number >= 25) {
		if(sequence_number == 25) {
			glTranslatef(0, cur_wheel4_disp, 0);
			cur_wheel4_disp += wheel4_disp_speed;
			if(cur_wheel4_disp <= max_wheel4_disp) sequence_number++;
		}
		else glTranslatef(0, max_wheel4_disp, 0);
	}
	if(sequence_number >= 23) {
		if(sequence_number == 23) {
			glTranslatef(0.15,0,0.1);
			glRotatef(cur_wheel4_rot, 0, 1, 0);
			glTranslatef(-0.15,0,-0.1);
			cur_wheel4_rot += wheel4_rot_speed;
			if(cur_wheel4_rot >= max_wheel4_rot) sequence_number++;
		}
		else{
			glTranslatef(0.15,0,0.1);
			glRotatef(max_wheel4_rot, 0, 1, 0);
			glTranslatef(-0.15,0,-0.1);
		}
	}
}*/


void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();				// Reset The View
	glRotatef(rtri, 0.7, 1, 0.0);
	glScalef(0.2,0.2,0.2);
	glCallList(0);
	glScalef(5,5,5);
	rtri += 1;
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

