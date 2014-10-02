#include "gl_framework.hpp"
#include "common.h"
transformer t;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);glEnable(GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);/*
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if(t.sequence_number == -2) t.sequence_number = t.last_sequence_number;
		else {
			t.last_sequence_number = t.sequence_number;
			t.sequence_number = -2;
		}
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
		if(t.sequence_number == 22 || t.sequence_number == -1) t.sequence_number++;
		else if(t.sequence_number == -2) t.sequence_number = t.last_sequence_number;
		else t.sequence_number = 44 - t.sequence_number;
	}*/
  }
};  
  


