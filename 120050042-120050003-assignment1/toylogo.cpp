/*
 * CS475/CS675 - Computer Graphics
 *  ToyLOGO Assignment Base Code
 *
 * Copyright 2009-2011, Parag Chaudhuri, Department of CSE, IIT Bombay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

#include "parser.hpp"
#include "gl_framework.hpp"
#include "turtle.hpp"
#include "render_drawing.hpp"


turtle_com_list_t list;
turtle_t turt;
turtle_com_list_t::iterator liter;

std::string filename, progname;
bool file_flag=false;

//GLFW display callback
void renderGL( void )
{

	//If a filename was given on the command line
	if (file_flag)
	{
		//Execute the parsed commands
		turtle_com_t *com;
		for( liter = list.begin(); liter!=list.end(); liter++)
		{
			com = *liter;
			turt.exec(com);
		}
	}
	//Or draw the default
	else
		render_drawing(turt);

}

//Function to print the command line usage information
void usage(void) 
{
	std::cerr<< "usage: "<<progname<<" [-f filename]"<<std::endl<<std::endl;
	std::cerr<< "\t-f\t filename of the file with the ToyLOGO source program\n";
	std::cerr<< "\t\t If no filename is given then a default drawing is drawn.\n";
	exit(0);
}

//Parse the command line and .logo program
void setup(int argc, char *argv[])
{
	char c;
	while ((c = getopt(argc, argv, "?f:")) != EOF)
	{
		switch (c) 
		{
			case '?':
				usage();
				break;
			case 'f':
				filename = optarg;
				file_flag = true;
				break;
			default:
				usage();
		}
	}

	if (!file_flag) 
	{
		std::cerr<<"No filename specified. Rendering default drawing."<<std::endl;
	}
	else
	{
		//Construct a parser
		parser_t parser;

		//Open the file for reading
		std::ifstream inp(filename.c_str(), std::ios::in);

		if (inp) std::cerr<<std::endl<<"Parsing "<<filename<<"..."<<std::endl<<std::endl;

		//Parse the ToyLOGO program to a list of commands
		parser.parse(inp, list);

		inp.close();

		liter=list.begin();
	}
}

int main (int argc, char *argv[]) 
{
	progname=argv[0];

	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	setup(argc, argv);

	int win_width=512;
	int win_height=512;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(win_width, win_height, "ToyLOGO", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwGetFramebufferSize(window, &win_width, &win_height);
	csX75::framebuffer_size_callback(window, win_width, win_height);
	//Initialize GL state
	csX75::initGL();


	turt.window=window;
	while (glfwWindowShouldClose(window) == 0)
	{

		// Render here
		renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();



	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
