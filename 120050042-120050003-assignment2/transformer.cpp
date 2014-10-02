#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
typedef unsigned char BYTE; 
using namespace std;

struct transformer {
    
    /// sequence_number_* 0 means nothing , 1 means transforming to car , 2 means transforming to ro
    int sequence_number_head_flap, sequence_number_hands, sequence_number_legs,sequence_number_wheels,sequence_number_flaps;
    int state_head_flap,state_legs,state_wheels,state_flap;
    double color_red, color_green, color_blue, color_variant;
    int steps;
    
    // Variables for display list
    double cube_index,cylinder_index,square_index;
    
    /**
    * Constructor ;
    * */
    transformer () {
        steps = 600;
        sequence_number_head_flap = 1;
        sequence_number_hands = 0;
        sequence_number_legs = 1;
        sequence_number_wheels = 0;
        sequence_number_flaps=0;
        state_head_flap = 1;
        state_legs=0;
        color_red = 0.5;
        color_green = 0.5;
        color_blue = 0.5;
        color_variant = 0;
    }
    
    /**
    * draws a cylinder of unit length
    * */
    void drawUnitCylinder() {
        double radius = 1.0, width = 1.0;
		int count = 18;
		double angle = 0;// = i * 2.0*3.1415926/count;
		glColor3f(0.3, 0.3, 0.3);
		for(int i = 0; i < count; i++) {
			double angle1 = angle;
			angle += 2.0*3.1415926/count;
			glBegin(GL_POLYGON);
				glVertex3f(radius*cosf(angle), radius*sinf(angle), 0.0 - width/2);
				glVertex3f(radius*cosf(angle), radius*sinf(angle), width/2);
				glVertex3f(radius*cosf(angle1), radius*sinf(angle1), width/2);
				glVertex3f(radius*cosf(angle1), radius*sinf(angle1), 0.0 - width/2);
			glEnd();
		}
		glColor3f(0.2, 0.2, 0.2);
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
    
    
    /**
    * drawUnitCube() : draws a unit cube and can be used as primitive
    * */
    void drawUnitCube(){
		glBegin(GL_POLYGON);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
		glBegin(GL_POLYGON);	       
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(1.0f,0.0f,1.0f);
		glEnd();
	}
	
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
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
	}
	
	void drawRectangle(double width, double height) {
	    glColor3f(color_red,color_green,color_blue);	
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
	   color_green=1; color_blue=0; color_red=0;
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
	     color_red=0.8;
		color_green=0.8;
		color_blue=0;
	     glTranslatef(0,2,-2);
	     drawRectangle(4,6);
	 }
	 
	 void drawHead() {
	     glColor3f(0,0,1);
	     drawCube(2,2,1);
	     glColor3f(1,1,0);
	 }
	 
	 void drawHeadFlapLeft() {
	    glBegin(GL_POLYGON);
	        glVertex3f(0, 0, 0);
	        glVertex3f(0, 0, -2);
	        glVertex3f(-1, 4, -2);
	        glVertex3f(-1, 4, -0.5);
	    glEnd();
	 }
	 
	 void drawHeadFlapBackLeft() {
	    glBegin(GL_POLYGON);
	        glVertex3f(0, 0, 0);
	        glVertex3f(-2, 0, 0);
	        glVertex3f(-2, 4, -0.5);
	        glVertex3f(-1, 4, -0.5);
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
	     glTranslatef(0, -2, 0);
	     drawCube(1, 2, 1.5);
	 }
	 
	 void drawHandLowerLeft() {
	    glTranslatef(0,-1,0);
	    glRotatef(90, -1,0,0);
	    drawCylinder(0.5, 2);
	 }
	 
	 void drawFistLeft() {
	 
	 }
	 
	 void drawHandWheelLeft() {
	    glRotatef(90,0,1,0);
	    glTranslatef(0,1,1.25);
	    drawCylinder(1,0.5);
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
	 
	 }
	 
	 void drawHandWheelRight() {
	    glScalef(-1,1,1);
	    drawHandWheelLeft();
	    glScalef(-1,1,1);
	 }
	 
	 void drawThigh(){
	    glTranslatef(0,1.5,0);
	    glRotatef(90,1,0,0);
	    drawCylinder(0.75,3);
	 }
	 
	 void drawLeg(){
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
	     glRotatef(90,0,1,0);
	    drawCylinder(0.1,1.5);
	 }
	 
	 void drawWheelLeft() {
	    drawCylinder(1.25,0.5);
	 }
	 
	 void drawAxleRight() {
	    glRotatef(-90,0,1,0);
	    drawCylinder(0.1,1.5);
	 }
	 
	 void drawWheelRight() {
	    drawCylinder(1.25,0.5);
	 }
	 
	 /**
	  * Animating single parts of the body
	  */
	 
	 void animateTorsoFlap() {
	 
	 }
	 
	 void animateHead() {
	     
	 }
	 
	 void animateHeadFlapLeft() {
	    double max_angle = -60;
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = max_angle/steps*state_head_flap;
	        glRotatef(angle, 0,0,1);
	    }
	    else if(state_head_flap == steps) {
	        glRotatef(max_angle, 0, 0, 1);
	    }
	    if(state_head_flap == steps || state_head_flap == 0) sequence_number_head_flap = 0;
	 }
	 
	 void animateHeadFlapBackLeft() {
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = 180.0/steps*state_head_flap;
	        glRotatef(angle, -1,4,-0.5);
	    }
	    else if(state_head_flap == steps) {
	        glRotatef(180.0, -1, 4, -0.5);
	    }
	    if(state_head_flap == steps || state_head_flap == 0) sequence_number_head_flap = 0;
	 }
	 
	 void animateHeadFlapUpperLeft() {
	    double max_angle = -250;
	    if(state_head_flap < steps && state_head_flap > 0) {
	        double angle = max_angle/steps*state_head_flap;
	        glRotatef(angle, 0,0,1);
	    }
	    else if(state_head_flap == steps) {
	        glRotatef(max_angle, 0, 0, 1);
	    }
	    if(state_head_flap == steps || state_head_flap == 0) sequence_number_head_flap = 0;
	 }
	 
	 void animateHeadFlapRight() {
	    glScalef(-1,1,1);
	    animateHeadFlapLeft();
	    glScalef(-1,1,1);
	    if(sequence_number_head_flap == 1) state_head_flap++;
	    else if(sequence_number_head_flap == 2) state_head_flap--;
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
	 
	 }
	 
	 void animateHandLowerLeft() {
	 
	 }
	 
	 void animateFistLeft() {
	 
	 }
	 
	 void animateHandWheelLeft() {
	 
	 }
	 
	 void animateHandUpperRight() {
	 
	 }
	 
	 void animateHandLowerRight() {
	 
	 }
	 
	 void animateFistRight() {
	 
	 }
	 
	 void animateHandWheelRight() {
	 
	 }
	 
	 void animateThighLeft() {
	    double angle = -180.0/steps*state_legs;
	    glRotatef(angle, 1,0,0);
	    if(sequence_number_legs == 1) state_legs++;
	    else if(sequence_number_legs == 2) state_legs--;
	    if(sequence_number_legs!=0){
			if(state_legs >= steps)
			{
				 sequence_number_legs = 0;
				 state_legs=steps-1;
			}
			else if(state_legs<=0){
				sequence_number_legs = 0;
				state_legs=1;
			}
		}
	 }
	 
	 void animateLegLeft() {
	 
	 }
	 
	 void animateToeLeft() {
	 
	 }
	 
	  void animateThighRight() {
	    animateThighLeft();
	 }
	 
	 void animateLegRight() {
	 
	 }
	 
	 void animateToeRight() {
	 
	 }
	 
	 void animateAxleLeft() {
	 
	 }
	 
	 void animateWheelLeft() {
	 
	 }
	 
	 void animateAxleRight() {
	 
	 }
	 
	 void animateWheelRight() {
	 
	 }

    /**
     * placing single parts of the body on their actual positions
     */
    void placeTorsoFlap() {
	 
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
	    glTranslatef(-0.75,1,-1.75);
	 }
	 
	 void placeWheelLeft() {
	     glTranslatef(0.0,0.0,-1);
	 }
	 
	 void placeAxleRight() {
	    glTranslatef(4.75,1,-1.75);
	 }
	 
	 void placeWheelRight() {
	    glTranslatef(0.0,0.0,-1);
	 }
	
	void drawRobot(){
	    glScalef(0.05,0.05,0.05);
		glPushMatrix();
		
		    drawTorso();
		    
		    glPushMatrix();
		    
		        placeTorsoFlap();
		        animateTorsoFlap();
		        drawTorsoFlap();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeHead();
		        animateHead();
		        drawHead();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeHeadFlapLeft();
		        animateHeadFlapLeft();
		        drawHeadFlapLeft();
		        
		        glPushMatrix();
		            
		            placeHeadFlapBackLeft();
		            animateHeadFlapBackLeft();
		            drawHeadFlapBackLeft();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		            
		            placeHeadFlapUpperLeft();
		            animateHeadFlapUpperLeft();
		            drawHeadFlapUpperLeft();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeHeadFlapRight();
		        animateHeadFlapRight();
		        drawHeadFlapRight();
		        
		        glPushMatrix();
		            
		            placeHeadFlapBackRight();
		            animateHeadFlapBackRight();
		            drawHeadFlapBackRight();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		            
		            placeHeadFlapUpperRight();
		            animateHeadFlapUpperRight();
		            drawHeadFlapUpperRight();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeHandUpperLeft();
		        animateHandUpperLeft();
		        drawHandUpperLeft();
		        
		        glPushMatrix();
		            
		            placeHandLowerLeft();
		            animateHandLowerLeft();
		            drawHandLowerLeft();
		            
		            glPushMatrix();
		                
		                placeFistLeft();
		                animateFistLeft();
		                drawFistLeft();
		        
		            glPopMatrix();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		            
		            placeHandWheelLeft();
		            animateHandWheelLeft();
		            drawHandWheelLeft();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeHandUpperRight();
		        animateHandUpperRight();
		        drawHandUpperRight();
		        
		        glPushMatrix();
		            
		            placeHandLowerRight();
		            animateHandLowerRight();
		            drawHandLowerRight();
		            
		            glPushMatrix();
		                
		                placeFistRight();
		                animateFistRight();
		                drawFistRight();
		        
		            glPopMatrix();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		            
		            placeHandWheelRight();
		            animateHandWheelRight();
		            drawHandWheelRight();
		        
		        glPopMatrix();
		        
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeThighLeft();
		        animateThighLeft();
		        drawThighLeft();
		        
		        glPushMatrix();
		            
		            placeLegLeft();
		            animateLegLeft();
		            drawLegLeft();
		            
		            glPushMatrix();
		                
		                placeToeLeft();
		                animateToeLeft();
		                drawToeLeft();
		            
		            glPopMatrix();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeThighRight();
		        animateThighRight();
		        drawThighRight();
		        
		        glPushMatrix();
		            
		            placeLegRight();
		            animateLegRight();
		            drawLegRight();
		            
		            glPushMatrix();
		                
		                placeToeRight();
		                animateToeRight();
		                drawToeRight();
		            
		            glPopMatrix();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeAxleLeft();
		        animateAxleLeft();
		        drawAxleLeft();
		        
		        glPushMatrix();
		            
		            placeWheelLeft();
                    animateWheelLeft();
		            drawWheelLeft();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		        
		        placeAxleRight();
		        animateAxleRight();
		        drawAxleRight();
		        
		        glPushMatrix();
		            
		            placeWheelRight();
		            animateWheelRight();
		            drawWheelRight();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		
		glPopMatrix();
	    
	}
};
