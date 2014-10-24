#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>

using namespace std;

struct transformer {
	
    int main_state;
    /// sequence_number_* 0 means nothing , 1 means transforming to car , 2 means transforming to ro
    int sequence_number_head_flap, sequence_number_hands, sequence_number_legs,sequence_number_wheels,sequence_number_flaps;
    int flap_toggle;
    int state_head_flap,state_legs,state_wheels,state_flaps,state_hands;
    double color_red, color_green, color_blue, color_variant;
    int steps;
    float wheel_rotation;
	
	//! The variable for turning the car left or right
	double turning_factor;
	bool is_turning;
	/// storage for one texture  
	unsigned int texture[5];

	int turning_state, motion_state;
	double speed;
	double position_x, position_z;
	double dir_x, dir_z;
	double angle;
	
	int headlight;
    // Variables for display list
    double cube_index,cylinder_index,square_index;
    
    /**
    * Constructor ;
    * */
    transformer () {
		flap_toggle=-1;
		main_state=0;
        steps = 150;
        sequence_number_head_flap = 0;
        sequence_number_hands = 0;
        sequence_number_legs = 0;
        sequence_number_wheels = 0;
        sequence_number_flaps=0;
        state_head_flap = 0;
        state_legs=0;
        state_wheels=0;
        state_flaps=0;
        state_hands=0;
        color_red = 0.5;
        color_green = 0.5;
        color_blue = 0.5;
        color_variant = 0;
        
        turning_factor=0;
        is_turning=false;

		turning_state = 0;
		motion_state = 0;
		speed = 0;

		position_x = 0;
		position_z = 0;

		dir_x = 0;
		dir_z = -1;
		angle = 0;
		
		wheel_rotation=0;
		
		headlight=1;
    }
    
    	
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures();

    /**
    * draws a cylinder of unit length
    * */
    void drawUnitCylinder() {
        double radius = 1.0, width = 1.0;
		int count = 18;
		double angle = 0;// = i * 2.0*3.1415926/count;
		for(int i = 0; i < count; i++) {
			double angle1 = angle;
			angle += 2.0*3.1415926/count;
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(radius*cosf(angle), radius*sinf(angle), 0.0 - width/2);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(radius*cosf(angle), radius*sinf(angle), width/2);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(radius*cosf(angle1), radius*sinf(angle1), width/2);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(radius*cosf(angle1), radius*sinf(angle1), 0.0 - width/2);
			glEnd();
		}
		glBegin(GL_POLYGON);
			for(int i = 0; i < count; i++) {
				double angle = i * 2.0*3.1415926/count;
				glVertex3f(radius*cosf(angle), radius*sinf(angle), 0.0 - width/2);
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i = 0; i < count; i++) {
				double angle = i * 2.0*3.1415926/count;
				glVertex3f(radius*cosf(angle), radius*sinf(angle), width/2);
			}
		glEnd();
	}

    void drawCylinder(double radius, double width) {
        glScalef(radius, radius, width);
        glPushMatrix();
        glCallList(cylinder_index);
        glPopMatrix();
        glScalef(1/radius, 1/radius, 1/width);
    }
    
    void drawWheelUnitCylinder(){
		double radius = 1.0, width = 1.0;
		int count = 18;
		double angle = 0;// = i * 2.0*3.1415926/count;
		for(int i = 0; i < count; i++) {
			double angle1 = angle;
			angle += 2.0*3.1415926/count;
			
			if(count%2==0)
			{
				glBindTexture(GL_TEXTURE_2D, texture[1]); 
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, texture[3]); 
			}
			glBegin(GL_POLYGON);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(radius*cosf(angle), radius*sinf(angle), 0.0 - width/2);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(radius*cosf(angle), radius*sinf(angle), width/2);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(radius*cosf(angle1), radius*sinf(angle1), width/2);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(radius*cosf(angle1), radius*sinf(angle1), 0.0 - width/2);
				glEnd();
			
		}
		glBegin(GL_POLYGON);
			for(int i = 0; i < count; i++) {
				double angle = i * 2.0*3.1415926/count;
				glVertex3f(radius*cosf(angle), radius*sinf(angle), 0.0 - width/2);
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i = 0; i < count; i++) {
				double angle = i * 2.0*3.1415926/count;
				glVertex3f(radius*cosf(angle), radius*sinf(angle), width/2);
			}
		glEnd();
	}
	
    void drawWheelCylinder(double radius, double width){
		glScalef(radius, radius, width);
        glPushMatrix();
			drawWheelUnitCylinder();
		glPopMatrix();
        glScalef(1/radius, 1/radius, 1/width);
	}
    
    /**
    * drawUnitCube() : draws a unit cube and can be used as primitive
    * */
    void drawUnitCube();
	
	void drawCube(double width, double height, double length) {
	    glScalef(width, height, length);
		glPushMatrix();
		glCallList(cube_index);
		glPopMatrix();
		glScalef(1/width, 1/height, 1/length);
	}
	
	/**
    * drawUnitSquare() : draws a unit square and can be used as primitive
    * */
    void drawUnitSquare(){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
	}
	
	void drawRectangle(double width, double height) {
	    glScalef(width, height, 1);
		glPushMatrix();
		glCallList(square_index);
		glPopMatrix();
		glScalef(1/width, 1/height, 1);
	}
	
	/**
	* createDisplayLists() : Creates all display lists required for the animation 
	* */
	void createDisplayLists(){
	    cube_index = glGenLists(1);
	    cylinder_index = glGenLists(1);
	    square_index = glGenLists(1);
		
		glNewList(cube_index, GL_COMPILE);
			drawUnitCube();
		glEndList();
		glNewList(cylinder_index, GL_COMPILE);
			drawUnitCylinder();
		glEndList();
		glNewList(square_index, GL_COMPILE);
			drawUnitSquare();
		glEndList();
	}
	
	
	/**
	 * Functions for drawing Individual parts of the transformer
	 **/
	 
	 // main torso
	 void drawTorso() {
		 glBindTexture(GL_TEXTURE_2D, texture[1]);
	   glColor3f(0,0,1);
	    drawRectangle(4,8);
	    glPushMatrix();
	        glTranslatef(4,0,0);
	        glRotatef(90,0,1,0);
	        drawRectangle(2,8);
	    glPopMatrix();
	    glPushMatrix();
	        glRotatef(90,0,1,0);
	        drawRectangle(2,8);
	    glPopMatrix();
	    
	    glPushMatrix();
			glTranslatef(0,8,0);
	        glRotatef(-90,1,0,0);
	        drawRectangle(4,2);
	    glPopMatrix();
	    
	    glPushMatrix();
	        glRotatef(-90,1,0,0);
	        drawRectangle(4,2);
	    glPopMatrix();
	 }
	 
	 /// The front flap of torso which opens up to hide legs
	 void drawTorsoFlap() {
		 glBindTexture(GL_TEXTURE_2D, texture[0]);  
	     glColor3f(1,1,1);
	     glTranslatef(0,-6,0);
	     drawRectangle(4,6);
	 }
	 
	 void drawHead() {
		 glBindTexture(GL_TEXTURE_2D, texture[0]);  
	     glColor3f(1,1,1);
	     glPushMatrix();
			drawCube(2,2,1);
			glColor3f(1,1,0);
		 glPopMatrix();
		 glBindTexture(GL_TEXTURE_2D, texture[3]); 
		 glPushMatrix(); 
			glTranslatef(1,-0.25,0.5);
			glRotatef(90,1,0,0);
			drawCylinder(0.6,0.3);
		 glPopMatrix();
		 glPushMatrix();
			glTranslatef(1,-0.7,0.5);
			glRotatef(90,1,0,0);
			drawCylinder(0.6,0.3);
		 glPopMatrix();
		
	 }
	 
	 void drawHeadFlapLeft() {
	    glBindTexture(GL_TEXTURE_2D, texture[1]);  
	    glColor3f(1,0,0);
	    glBegin(GL_POLYGON);
	       glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	        glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -2);
	        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 4, -2);
	        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 4, -0.5);
	    glEnd();
	 }
	 
	 void drawHeadFlapBackLeft() {
	    glBegin(GL_POLYGON);
	        glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	        glTexCoord2f(1.0f, 0.0f); glVertex3f(-2, 0, 0);
	        glTexCoord2f(1.0f, 1.0f); glVertex3f(-2, 4, -0.5);
	        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 4, -0.5);
	    glEnd();
	 }
	 
	 void drawHeadFlapUpperLeft() {
	     glTranslatef(-1,0,0);
	     glRotatef(-90, 1,0,0);
	     drawRectangle(1, 1.5);
	 }
	 
	 void drawHeadFlapRight() {
	    glScalef(-1,1,1);
	    drawHeadFlapLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawHeadFlapBackRight() {
	    glScalef(-1,1,1);
	    drawHeadFlapBackLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawHeadFlapUpperRight() {
	    glScalef(-1,1,1);
	    drawHeadFlapUpperLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawHandUpperLeft() {
		 glBindTexture(GL_TEXTURE_2D, texture[3]);  
		 glColor3f(0.8,0.5,0.5);
	     glTranslatef(0, -2, 0);
	     drawCube(1, 2, 1.5);
	 }
	 
	 void drawHandLowerLeft() {
		glColor3f(1,0.86,0.76);
	    glTranslatef(0,-1,0);
	    glRotatef(90, -1,0,0);
	    drawCylinder(0.5, 2);
	 }
	 
	 void drawFistLeft() {
		glTranslatef(0,0,-1);
		glColor3f(0,0,1);
		glPushMatrix();
		glRotatef(60, -1,0,0);
		drawRectangle(0.5,1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.5,0,0);
		glRotatef(90, -1,0,0);
		drawRectangle(1,1);
		glPopMatrix();
	 }
	 
	 void drawHandWheelLeft() {
		glColor3f(0.3,0.3,0.3);
		glBindTexture(GL_TEXTURE_2D, texture[1]); 
	    glRotatef(90,0,1,0);
	    drawWheelCylinder(1,0.5);
	 }
	 
	 void drawHandUpperRight() {
	    glScalef(-1,1,1);
	    drawHandUpperLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawHandLowerRight() {
	    glScalef(-1,1,1);
	    drawHandLowerLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawFistRight() {
		drawFistLeft();
	 }
	 
	 void drawHandWheelRight() {
	    glScalef(-1,1,1);
	    drawHandWheelLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawThigh(){
		 glBindTexture(GL_TEXTURE_2D, texture[3]);  
		 glColor3f(0.8,0.5,0.5);
	    glTranslatef(0,1.5,0);
	    glRotatef(90,1,0,0);
	    drawCylinder(0.75,3);
	 }
	 
	 void drawLeg(){
		 glColor3f(1,0.86,0.76);
	    drawCylinder(0.5,3);
	 }
	 
	 void drawThighLeft() {
	    drawThigh();
	 }
	 
	 void drawLegLeft() {
	    drawLeg();
	 }
	 
	 void drawToeLeft() {
	    glColor3f(1.0,0.0,0.0);
	    drawUnitCube();
	 }
	 
	  void drawThighRight() {
	    drawThigh();
	 }
	 
	 void drawLegRight() {
	    drawLeg();
	 }
	 
	 void drawToeRight() {
	    glColor3f(1.0,0.0,0.0);
	    drawUnitCube();
	 }
	 
	 void drawAxleLeft() {
		 glColor3f(0.3,0.3,0.3);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	     glTranslatef(-0.75,0,0);
	     glRotatef(90,0,1,0);
	    drawCylinder(0.1,1.5);
	 }
	 
	 void drawWheelLeft() {
	    drawWheelCylinder(1.25,0.5);
	 }
	 
	 void drawAxleRight() {
	    glTranslatef(0.75,0,0);
	    glRotatef(-90,0,1,0);
	    drawCylinder(0.1,1.5);
	 }
	 
	 void drawWheelRight() {
	    drawWheelCylinder(1.25,0.5);
	 }
	 
	 /**
	  * Animating single parts of the body
	  */
	 
	 void animateTorsoFlap() {
	      double angle = 90.0/steps*state_flaps;
	    glRotatef(angle, 1,0,0);
	    if(sequence_number_flaps == 1) state_flaps+=2;
	    else if(sequence_number_flaps == 2) state_flaps-=2;
	    if(sequence_number_flaps!=0){
			if(state_flaps >= steps)
			{
				 sequence_number_flaps = 1;
				 state_flaps=steps-1;
			}
			else if(state_flaps<=0){
				sequence_number_flaps = 2;
				state_flaps=1;
			}
		}
	 }
	 
	 void animateHead() {
	     
	 }
	 
	void check_head_flap_sequence(){
		 if(state_head_flap >= steps)
		{
			 sequence_number_head_flap = 1;
			 state_head_flap=steps-1;
		}
		else if(state_head_flap<=0){
			sequence_number_head_flap = 2;
			state_head_flap=1;
		}
	}
	 void animateHeadFlapLeft() {
	    double max_angle = -60;
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = max_angle/steps*state_head_flap;
	        glRotatef(angle, 0,0,1);
	    }
	    else if(state_head_flap >= steps) {
	        glRotatef(max_angle, 0, 0, 1);
	    }
	 }
	 
	 void animateHeadFlapBackLeft() {
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = 180.0/steps*state_head_flap;
	        glRotatef(angle, -1,4,-0.5);
	    }
	    else if(state_head_flap >= steps) {
	        glRotatef(180.0, -1, 4, -0.5);
	    }
	 }
	 
	 void animateHeadFlapUpperLeft() {
	    double max_angle = -250;
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = max_angle/steps*state_head_flap;
	        glRotatef(angle, 0,0,1);
	    }
	    else if(state_head_flap >= steps) {
	        glRotatef(max_angle, 0, 0, 1);
	    }
	 }
	 
	 void animateHeadFlapRight() {
	    glScalef(-1,1,1);
	    animateHeadFlapLeft();
	    glScalef(-1,1,1);
	    if(sequence_number_head_flap == 1) state_head_flap++;
	    else if(sequence_number_head_flap == 2) state_head_flap--;
	    check_head_flap_sequence();
	 }
	 
	 void animateHeadFlapBackRight() {
	    glScalef(-1,1,1);
	    animateHeadFlapBackLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void animateHeadFlapUpperRight() {
	    glScalef(-1,1,1);
	    animateHeadFlapUpperLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void animateHandUpperLeft() {
		double angle = 25.0/steps*state_hands;
	    glRotatef(angle, -0.1,0,1);
	    if(sequence_number_hands == 1) state_hands++;
	    else if(sequence_number_hands == 2) state_hands--;
	    if(sequence_number_hands!=0){
			if(state_hands >= steps)
			{
				 sequence_number_hands = 1;
				 state_hands=steps-1;
			}
			else if(state_hands<=0){
				sequence_number_hands = 2;
				state_hands=1;
			}
		}
	 }
	 
	 void animateHandLowerLeft() {
		
	 }
	 
	 void animateFistLeft() {
	 
	 }
	 
	 void animateHandWheelLeft() {
		 glPushMatrix();
			glTranslatef(-0.4,0,0);
			glRotatef(90,0,1,0);
			drawCylinder(.1,0.5);
		 glPopMatrix();
		 glRotatef(turning_factor,0,0,1);
		 glRotatef(wheel_rotation,1,0,0);
	 }
	 
	 void animateHandUpperRight() {
		double angle = -25.0/steps*state_hands;
	    glRotatef(angle, 0.1,0,1);
	 }
	 
	 void animateHandLowerRight() {
	 
	 }
	 
	 void animateFistRight() {
	 
	 }
	 
	 void animateHandWheelRight() {
		glPushMatrix();
			glTranslatef(0.4,0,0);
			glRotatef(90,0,1,0);
			drawCylinder(.1,0.5);
		 glPopMatrix();
		 glRotatef(turning_factor,0,0,1);
		 glRotatef(wheel_rotation,1,0,0);
	 }
	 
	 void animateThighLeft() {
	    double angle = -180.0/steps*state_legs;
	    glRotatef(angle, 1,0,0);
	   
	 }
	 
	 void animateLegLeft() {
	 
	 }
	 
	 void animateToeLeft() {
	 
	 }
	 
	  void animateThighRight() {
	    animateThighLeft();
	     if(sequence_number_legs == 1) state_legs++;
	    else if(sequence_number_legs == 2) state_legs--;
	    if(sequence_number_legs!=0){
			if(state_legs >= steps)
			{
				 sequence_number_legs = 1;
				 state_legs=steps-1;
			}
			else if(state_legs<=0){
				sequence_number_legs = 2;
				state_legs=1;
			}
		}
	 }
	 
	 void animateLegRight() {
	 
	 }
	 
	 void animateToeRight() {
	 
	 }
	 
	 void animateAxleLeft() {
	    double angle = -180.0/steps*state_wheels;
	    glRotatef(angle,0,1,0);
	    
	 }
	 
	 void animateWheelLeft() {
		glRotatef(wheel_rotation,0,0,1);
	 }
	 
	 void animateAxleRight() {
	    double angle = 180.0/steps*state_wheels;
	    glRotatef(angle,0,1,0);
	    if(sequence_number_wheels == 1) state_wheels++;
	    else if(sequence_number_wheels == 2) state_wheels--;
	    if(sequence_number_wheels!=0){
			if(state_wheels >= steps)
			{
				 sequence_number_wheels = 1;
				 state_wheels=steps-1;
			}
			else if(state_wheels<=0){
				sequence_number_wheels = 2;
				state_wheels=1;
			}
		}
	 }
	 
	 void animateWheelRight() {
		glRotatef(wheel_rotation,0,0,1);
	 }

    /**
     * placing single parts of the body on their actual positions
     */
    void placeTorsoFlap() {
	    glTranslatef(0,8,-2);
	 }
	 
	 void placeHead() {
	     glTranslatef(1, 9, -1.5);
	 }
	 
	 void placeHeadFlapLeft() {
	    glTranslatef(4,8,0);
	 }
	 
	 void placeHeadFlapBackLeft() {
	 
	 }
	 
	 void placeHeadFlapUpperLeft() {
	    glTranslatef(-1, 4, -0.5);
	 }
	 
	 void placeHeadFlapRight() {
	    glTranslatef(0,8,0);
	 }
	 
	 void placeHeadFlapBackRight() {
	 
	 }
	 
	 void placeHeadFlapUpperRight() {
	    glScalef(-1,1,1);
	    placeHeadFlapUpperLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void placeHandUpperLeft() {
	    glTranslatef(4, 7, -1.75);
	 }
	 
	 void placeHandLowerLeft() {
	    glTranslatef(0.5, 0, 0.75);
	 }
	 
	 void placeFistLeft() {
	 
	 }
	 
	 void placeHandWheelLeft() {
		glTranslatef(1.7,1,0);
	 }
	 
	 void placeHandUpperRight() {
	    glTranslatef(0, 7, -1.75);
	 }
	 
	 void placeHandLowerRight() {
	    glScalef(-1,1,1);
	    placeHandLowerLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void placeFistRight() {
	 
	 }
	 
	 void placeHandWheelRight() {
		glScalef(-1,1,1);
	    placeHandWheelLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void placeThighLeft() {
	    glTranslatef(1.0,0.001,-1);
	 }
	 
	 void placeLegLeft() {
	     glTranslatef(0.0,0.0,-3.0);
	 }
	 
	 void placeToeLeft() {
	    glTranslatef(-0.5,-0.5,-2);
	 }
	 
	  void placeThighRight() {
	    glTranslatef(3.0,0.001,-1);
	 }
	 
	 void placeLegRight() {
	     glTranslatef(0.0,0.0,-3.0);
	 }
	 
	 void placeToeRight() {
	    glTranslatef(-0.5,-0.5,-2);
	 }
	 
	 void placeAxleLeft() {
	    glTranslatef(0,1,-1.75);
	 }
	 
	 void placeWheelLeft() {
	     glTranslatef(0.0,0.0,-1);
	 }
	 
	 void placeAxleRight() {
	    glTranslatef(4,1,-1.75);
	 }
	 
	 void placeWheelRight() {
	    glTranslatef(0.0,0.0,-1);
	 }
	 
	/**
	 * depending on the value of main state and the current states
	 * of the transformation the next states are assigned by this function
	 */
	
	void assign_states(){
		if(flap_toggle==-1){
			return;
		}
		if(main_state==0){
			if(sequence_number_flaps != 1 && flap_toggle==0)
				{sequence_number_flaps = 1; flap_toggle=1; }
			else if(sequence_number_wheels != 2 && state_flaps>= steps-1 && sequence_number_flaps == 1)
				{sequence_number_wheels = 2;}
			else if(sequence_number_legs!=2  && state_wheels<=1 && sequence_number_wheels==2 )
				{sequence_number_legs = 2;}
			else if(sequence_number_flaps != 2 && state_legs<=1 && sequence_number_legs == 2)
				{sequence_number_flaps=2;} 
			else if(sequence_number_head_flap != 2 && state_flaps<=1 && sequence_number_flaps == 2)
				{sequence_number_head_flap = 2;sequence_number_hands = 2;}
		}
		else{
			if(sequence_number_flaps != 1 && flap_toggle==0)
				{sequence_number_flaps = 1; flap_toggle=1; }
			else if(sequence_number_legs!=1 && state_flaps>= steps-1 && sequence_number_flaps == 1)
				{sequence_number_legs = 1;}
			else if(sequence_number_wheels != 1 && state_legs>= steps-1 &&sequence_number_legs==1 )
				{sequence_number_wheels = 1;}
			else if(sequence_number_flaps != 2 && state_wheels>= steps-1 && sequence_number_wheels == 1)
				{sequence_number_flaps=2;} 
			else if(sequence_number_head_flap != 1 && state_flaps<=1 && sequence_number_flaps == 2)
				{sequence_number_head_flap = 1;sequence_number_hands = 1;}
		}
	}
	
	/**
	 * Main Function for drawing the Robot. It contains all the hierarchy of the transformer model
	 * 
	 * */
	void drawRobot();
	
	//! Function to turn Robot Left
	void turnRobotLeft();
	
	//! Function to turn Robot Right
	void turnRobotRight();
	
	//! Function to turn Robot Right
	void restoreTurning();
	
	void drawHeadLight();
	

};
extern transformer t;
