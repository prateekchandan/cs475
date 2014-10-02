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
    int sequence_number_head_flap, sequence_number_hands, sequence_number_legs;
    double color_red, color_green, color_blue, color_variant;
    
    // Variables for display list
    double cube_index,cylinder_index,square_index;
    
    /**
    * Constructor ;
    * */
    transformer () {
        sequence_number_head_flap = 0;
        sequence_number_hands = 0;
        sequence_number_legs = 0;
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
			glColor3f(color_red, color_green, color_blue);		       
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red, color_green, color_blue);		       
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-color_variant), color_green*(1.0f-color_variant), color_blue*(1.0f-color_variant));		        glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-color_variant), color_green*(1.0f-color_variant), color_blue*(1.0f-color_variant));		        glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-2*color_variant), color_green*(1.0f-2*color_variant), color_blue*(1.0f-2*color_variant));		glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-2*color_variant), color_green*(1.0f-2*color_variant), color_blue*(1.0f-2*color_variant));		        // Top of triangle (front)
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
		color_green=1;
	    drawRectangle(4,8);
	    color_blue=1;color_green=0;color_red=0.5;
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
		
	     glTranslatef(0,8,-2);
	     drawRectangle(4,6);
	 }
	 
	 void drawHeadFlapLeft() {
	 
	 }
	 
	 void drawHeadFlapBackLeft() {
	 
	 }
	 
	 void drawHeadFlapUpperLeft() {
	 
	 }
	 
	 void drawHeadFlapRight() {
	 
	 }
	 
	 void drawHeadFlapBackRight() {
	 
	 }
	 
	 void drawHeadFlapUpperRight() {
	 
	 }
	 
	 void drawHandUpperLeft() {
	 
	 }
	 
	 void drawHandLowerLeft() {
	 
	 }
	 
	 void drawFistLeft() {
	 
	 }
	 
	 void drawHandWheelLeft() {
	 
	 }
	 
	 void drawHandUpperRight() {
	 
	 }
	 
	 void drawHandLowerRight() {
	 
	 }
	 
	 void drawFistRight() {
	 
	 }
	 
	 void drawHandWheelRight() {
	 
	 }
	 
	 void drawThighLeft() {
	 
	 }
	 
	 void drawLegLeft() {
	 
	 }
	 
	 void drawToeLeft() {
	 
	 }
	 
	  void drawThighRight() {
	 
	 }
	 
	 void drawLegRight() {
	 
	 }
	 
	 void drawToeRight() {
	 
	 }
	 
	 void drawAxleLeft() {
	 
	 }
	 
	 void drawWheelLeft() {
	 
	 }
	 
	 void drawAxleRight() {
	 
	 }
	 
	 void drawWheelRight() {
	 
	 }
	 
	 /**
	  * Animating single parts of the body
	  */
	 
	 void animateTorsoFlap() {
	 
	 }
	 
	 void animateHeadFlapLeft() {
	 
	 }
	 
	 void animateHeadFlapBackLeft() {
	 
	 }
	 
	 void animateHeadFlapUpperLeft() {
	 
	 }
	 
	 void animateHeadFlapRight() {
	 
	 }
	 
	 void animateHeadFlapBackRight() {
	 
	 }
	 
	 void animateHeadFlapUpperRight() {
	 
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
	 
	 }
	 
	 void animateLegLeft() {
	 
	 }
	 
	 void animateToeLeft() {
	 
	 }
	 
	  void animateThighRight() {
	 
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
	 
	 void placeHeadFlapLeft() {
	 
	 }
	 
	 void placeHeadFlapBackLeft() {
	 
	 }
	 
	 void placeHeadFlapUpperLeft() {
	 
	 }
	 
	 void placeHeadFlapRight() {
	 
	 }
	 
	 void placeHeadFlapBackRight() {
	 
	 }
	 
	 void placeHeadFlapUpperRight() {
	 
	 }
	 
	 void placeHandUpperLeft() {
	 
	 }
	 
	 void placeHandLowerLeft() {
	 
	 }
	 
	 void placeFistLeft() {
	 
	 }
	 
	 void placeHandWheelLeft() {
	 
	 }
	 
	 void placeHandUpperRight() {
	 
	 }
	 
	 void placeHandLowerRight() {
	 
	 }
	 
	 void placeFistRight() {
	 
	 }
	 
	 void placeHandWheelRight() {
	 
	 }
	 
	 void placeThighLeft() {
	 
	 }
	 
	 void placeLegLeft() {
	 
	 }
	 
	 void placeToeLeft() {
	 
	 }
	 
	  void placeThighRight() {
	 
	 }
	 
	 void placeLegRight() {
	 
	 }
	 
	 void placeToeRight() {
	 
	 }
	 
	 void placeAxleLeft() {
	 
	 }
	 
	 void placeWheelLeft() {
	 
	 }
	 
	 void placeAxleRight() {
	 
	 }
	 
	 void placeWheelRight() {
	 
	 }

	
	void drawRobot(){
	    glScalef(0.05,0.05,0.05);
		glPushMatrix();
		
		    drawTorso();
		    
		    glPushMatrix();
		    
		        drawTorsoFlap();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawHeadFlapLeft();
		        
		        glPushMatrix();
		        
		            drawHeadFlapBackLeft();   
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		        
		            drawHeadFlapUpperLeft();   
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawHeadFlapRight();
		        
		        glPushMatrix();
		        
		            drawHeadFlapBackRight();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		        
		            drawHeadFlapUpperRight();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawHandUpperLeft();
		        
		        glPushMatrix();
		        
		            drawHandLowerLeft();
		            
		            glPushMatrix();
		        
		                drawFistLeft();
		        
		            glPopMatrix();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		        
		            drawHandWheelLeft();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawHandUpperRight();
		        
		        glPushMatrix();
		        
		            drawHandLowerRight();
		            
		            glPushMatrix();
		        
		                drawFistRight();
		        
		            glPopMatrix();
		        
		        glPopMatrix();
		        
		        glPushMatrix();
		        
		            drawHandWheelRight();
		        
		        glPopMatrix();
		        
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawThighLeft();
		        
		        glPushMatrix();
		        
		            drawLegLeft();
		            
		            glPushMatrix();
		            
		                drawToeLeft();
		            
		            glPopMatrix();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawThighRight();
		        
		        glPushMatrix();
		        
		            drawLegRight();
		            
		            glPushMatrix();
		            
		                drawToeRight();
		            
		            glPopMatrix();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawAxleLeft();
		        
		        glPushMatrix();
		        
		            drawWheelLeft();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		    
		    glPushMatrix();
		    
		        drawAxleRight();
		        
		        glPushMatrix();
		        
		            drawWheelRight();
		        
		        glPopMatrix();
		    
		    glPopMatrix();
		
		glPopMatrix();
	    
	}
};

