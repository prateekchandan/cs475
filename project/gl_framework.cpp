#include "gl_framework.hpp"
#include "environment.hpp"
#include "transformer.hpp"

namespace csX75
{
	int camera_state=1;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
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
      glfwSetWindowShouldClose(window, GL_TRUE);
    
	
	//! Changes the main state upon pressing of Enter Key
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
		t.main_state++;
		t.main_state%=2;
		t.flap_toggle=0;
		t.sequence_number_head_flap = 0;
		t.sequence_number_legs = 0;
        t.sequence_number_wheels = 0;
        t.sequence_number_flaps=0;
        t.sequence_number_hands=0;
	}
	
	
	if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
		t.turning_state = -1;
		t.turnRobotLeft();
	}
	if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
		t.turning_state = 0;
	}
	if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		t.turning_state = 1;
		t.turnRobotRight();
	}
	if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
		t.turning_state = 0;
	}

	if(key == GLFW_KEY_UP && action == GLFW_PRESS){
		if(t.motion_state!=1)
		t.speed/=3.0;
		t.motion_state = 1;
	}
	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
		if(t.motion_state!=-1)
		t.speed/=3.0;
		t.motion_state = -1;
	}

	if((key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE) {
		t.motion_state = 0;
	}
	
	if(key == GLFW_KEY_L && action == GLFW_PRESS){
		Env.toggle_Sunlight();
	}
	
	
	if(key == GLFW_KEY_C && action == GLFW_PRESS){
		camera_state++;
		camera_state%=4;
	}
	
	if(key == GLFW_KEY_H && action == GLFW_PRESS){
		t.headlight++;
		t.headlight%=2;
	}
	
	if(key == GLFW_KEY_B && action == GLFW_PRESS){
		t.speed=0;
	}
		
  }
  
  void setCamera(){
	 if(camera_state==0)
		gluLookAt(t.position_x-10*t.dir_x, 9.1, t.position_z-10*t.dir_z, t.position_x, 2, t.position_z, 0,1,0);
	else if(camera_state==1)
		gluLookAt(t.position_x-4*t.dir_x, 2.1, t.position_z-4*t.dir_z, t.position_x, 2, t.position_z, 0,1,0);
	else if(camera_state==2)
	{
		gluLookAt(t.position_x+1*t.dir_x, 0.8, t.position_z+1*t.dir_z, t.position_x+4*t.dir_x, 1, t.position_z+4*t.dir_z, 0,1,0);
	}
	else if(camera_state==3)
	{
		gluLookAt(t.position_x-30*t.dir_x, 29.1, t.position_z-30*t.dir_z, t.position_x, 2, t.position_z, 0,1,0);
	}
}

    void doTurnings(){
	  if(t.turning_state < 0) {
		  t.turnRobotLeft();
	  }
	  if(t.turning_state > 0) {
		  t.turnRobotRight();
	  }
	  
	
	if(t.position_x>=280)
	{
		if(t.speed*(t.dir_x)<0)
			t.position_x += t.speed*(t.dir_x);
		
	}
	else if(t.position_z >= -25 && t.position_z<=25 && t.position_x>=35&& t.position_x<=45)
	{
		if(t.speed*(t.dir_x)<0)
			t.position_x += t.speed*(t.dir_x);
	}
	else if(t.position_z >= -25 && t.position_z<=25 && t.position_x<=210&& t.position_x>=200)
	{
		if(t.speed*(t.dir_x)>0)
			t.position_x += t.speed*(t.dir_x);
	}
	else if(t.position_x<=-20)
	{
		if(t.speed*(t.dir_x)>0)
			t.position_x += t.speed*(t.dir_x);
	}
	else{
		t.position_x += t.speed*(t.dir_x);
	}
	
	if(t.position_z>=60)
	{
		if(t.speed*(t.dir_z)<0)
			t.position_z += t.speed*(t.dir_z);	
	}
	else if(t.position_x >= 35&& t.position_x<=205 && t.position_z<=25 && t.position_z>20)
	{
		if(t.speed*(t.dir_z)>0)
			t.position_z += t.speed*(t.dir_z);	
	}
	else if(t.position_x >= 35&& t.position_x<=205 && t.position_z>-25 && t.position_z<-20)
	{
		if(t.speed*(t.dir_z)<0)
			t.position_z += t.speed*(t.dir_z);	
	}
	else if(t.position_z <= -190)
	{
		if(t.speed*(t.dir_z)>0)
			t.position_z += t.speed*(t.dir_z);
	}
	else{
		t.position_z += t.speed*(t.dir_z);
	}
	
	if(t.speed < 0) t.angle-=5*t.speed*(t.turning_factor/24);
	else if (t.speed > 0) t.angle-=5*t.speed*(t.turning_factor/24);
	  if(t.motion_state < 0) {
		if(t.speed > -0.5) t.speed -= 0.005;
	  }
	  else if(t.motion_state > 0) {
		if(t.speed < 0.5) t.speed += 0.005;
	  }
	  else {
		  if(t.speed < 0) t.speed += 0.001;
		  else if (t.speed > 0) t.speed -= 0.001;
	  }
	  t.dir_z = -cosf(3.1416*t.angle/180.0);
	  t.dir_x = sinf(3.1416*t.angle/180.0);
  }

};  
  


