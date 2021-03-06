#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include <iostream>

namespace csX75
{

  //! Initialize GL State
  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  
  void doTurnings(void);
  
  void setCamera();

  void importKeyframe();

  void exportKeyframe();

  void exportStateKeyframe();

  bool state_change();

  void store_past();
};

#endif
