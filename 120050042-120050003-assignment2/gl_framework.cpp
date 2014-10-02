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
    cout<<key<<endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == 328) {
		t.xrotate++;
	}
	if (key == 322) {
		t.xrotate--;
	}
	if (key == 324) {
		t.zrotate++;
	}
	if (key == 326) {
		t.zrotate--;
	}
	if (key == 327 || key == 321 ) {
		t.yrotate--;
	}
	if (key == 329 || key == 323) {
		t.yrotate++;
	}
	if (key == GLFW_KEY_UP){
		t.y_offset++;
	}
	if (key == GLFW_KEY_DOWN){
		t.y_offset--;
	}
	if (key == GLFW_KEY_RIGHT){
		t.x_offset++;
	}
	if (key == GLFW_KEY_LEFT){
		t.x_offset--;
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
		t.main_state++;
		t.main_state%=2;
	}
  }
};  
  


