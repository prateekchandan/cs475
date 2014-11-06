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
		}
		if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
			t.turning_state = 0;
		}
		if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
			t.turning_state = 1;
		}
		if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
			t.turning_state = 0;
		}

		if(key == GLFW_KEY_UP && action == GLFW_PRESS){
			//if(t.motion_state!=1)
				//t.speed/=3.0;
			t.motion_state = 1;
		}
		if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			//if(t.motion_state!=-1)
				//t.speed/=3.0;
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
		if(key == GLFW_KEY_R && action == GLFW_PRESS){
			exportKeyframe();
		}

	}


	/**
	 * setting camera positions as per the state variabls
	 */
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

	/**
	 * give the car its motion as per the state variables as well as
	 * apply constraints on the movements of the car
	 */
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


	void exportKeyframe(){
		//cerr << position_x << " " << position_z << " " << angle << " " << turning_state << " " << motion_state << " " << speed << endl;
		//if(state_change()) cout << frame_index << " " << turning_state << " " << motion_state << endl;
		if(!t.state_export)
		t.keyfile
		       << 0
		<< " " <<  t.frame_index
		<< " " <<  t.state_head_flap
		<< " " <<  t.state_legs
		<< " " <<  t.state_wheels
		<< " " <<  t.state_flaps
		<< " " <<  t.state_hands
		<< " " <<  t.turning_factor
		<< " " <<  t.speed
		<< " " <<  t.position_x
		<< " " <<  t.position_z
		<< " " <<  t.dir_x
		<< " " <<  t.dir_z
		<< " " <<  t.angle
		<< " " <<  t.wheel_rotation << endl;
	}

	void exportStateKeyframe(){
		
	}

	void importKeyframe(){
		//cin >> position_x >> position_z >> angle >> turning_state >> motion_state >> speed;
		if(t.frame_index == t.next_frame || t.frame_index == 1) {
			//turning_state = next_turning_state;
			//motion_state = next_motion_state;
			//cin >> next_frame >> next_turning_state >> next_motion_state;
			t.prev_frame     =t.frame_index;
			t.state_head_flap=t.next_state_head_flap;
			t.state_legs     =t.next_state_legs     ;
			t.state_wheels   =t.next_state_wheels   ;
			t.state_flaps    =t.next_state_flaps    ;
			t.state_hands    =t.next_state_hands    ;
			t.turning_factor =t.next_turning_factor ;
			t.speed          =t.next_speed          ;
			t.position_x     =t.next_position_x     ;
			t.position_z     =t.next_position_z     ;
			t.dir_x          =t.next_dir_x          ;
			t.dir_z          =t.next_dir_z          ;
			t.angle          =t.next_angle          ;
			t.wheel_rotation =t.next_wheel_rotation;;

			t.prev_state_head_flap=t.state_head_flap;
			t.prev_state_legs     =t.state_legs     ;
			t.prev_state_wheels   =t.state_wheels   ;
			t.prev_state_flaps    =t.state_flaps    ;
			t.prev_state_hands    =t.state_hands    ;
			t.prev_turning_factor =t.turning_factor ;
			t.prev_speed          =t.speed          ;
			t.prev_position_x     =t.position_x     ;
			t.prev_position_z     =t.position_z     ;
			t.prev_dir_x          =t.dir_x          ;
			t.prev_dir_z          =t.dir_z          ;
			t.prev_angle          =t.angle          ;
			t.prev_wheel_rotation =t.wheel_rotation;;

			t.keyfile
			>> t.next_frame 
			>> t.next_state_head_flap
			>> t.next_state_legs
			>> t.next_state_wheels
			>> t.next_state_flaps
			>> t.next_state_hands
			>> t.next_turning_factor
			>> t.next_speed
			>> t.next_position_x
			>> t.next_position_z
			>> t.next_dir_x
			>> t.next_dir_z
			>> t.next_angle
			>> t.next_wheel_rotation;

		}
		else {
			t.state_head_flap= t.next_state_head_flap*float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_state_head_flap*float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.state_legs     = t.next_state_legs     *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_state_legs     *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.state_wheels   = t.next_state_wheels   *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_state_wheels   *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.state_flaps    = t.next_state_flaps    *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_state_flaps    *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.state_hands    = t.next_state_hands    *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_state_hands    *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.turning_factor = t.next_turning_factor *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_turning_factor *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.speed          = t.next_speed          *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_speed          *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.position_x     = t.next_position_x     *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_position_x     *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.position_z     = t.next_position_z     *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_position_z     *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.dir_x          = t.next_dir_x          *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_dir_x          *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.dir_z          = t.next_dir_z          *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_dir_z          *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.angle          = t.next_angle          *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_angle          *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);
			t.wheel_rotation = t.next_wheel_rotation *float(t.frame_index-t.prev_frame)/float(t.next_frame-t.prev_frame)+t.prev_wheel_rotation *float(t.next_frame-t.frame_index)/float(t.next_frame-t.prev_frame);





			//state_head_flap=(next_state_head_flap+prev_state_head_flap)*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//state_legs     =(next_state_legs     +prev_state_legs     )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//state_wheels   =(next_state_wheels   +prev_state_wheels   )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//state_flaps    =(next_state_flaps    +prev_state_flaps    )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//state_hands    =(next_state_hands    +prev_state_hands    )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//turning_factor =(next_turning_factor +prev_turning_factor )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//speed          =(next_speed          +prev_speed          )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//position_x     =(next_position_x     +prev_position_x     )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//position_z     =(next_position_z     +prev_position_z     )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//dir_x          =(next_dir_x          +prev_dir_x          )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//dir_z          =(next_dir_z          +prev_dir_z          )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//angle          =(next_angle          +prev_angle          )*float(frame_index-prev_frame)/(next_frame-prev_frame);
			//wheel_rotation =(next_wheel_rotation +prev_wheel_rotation )*float(frame_index-prev_frame)/(next_frame-prev_frame);
		}
	}

};  



