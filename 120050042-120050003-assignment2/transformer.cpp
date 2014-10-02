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



/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;



struct transformer {
	
	int xrotate,yrotate,zrotate;
	int x_offset,y_offset;
    int main_state;
    /// sequence_number_* 0 means nothing , 1 means transforming to car , 2 means transforming to ro
    int sequence_number_head_flap, sequence_number_hands, sequence_number_legs,sequence_number_wheels,sequence_number_flaps;
    int flap_toggle;
    int state_head_flap,state_legs,state_wheels,state_flaps,state_hands;
    double color_red, color_green, color_blue, color_variant;
    int steps;
	
	/// storage for one texture  
	unsigned int texture[1];


    // Variables for display list
    double cube_index,cylinder_index,square_index;
    
    /**
    * Constructor ;
    * */
    transformer () {
		flap_toggle=-1;
		main_state=0;
		xrotate=0; yrotate=0; zrotate=0;
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
    }
    
    
	int ImageLoad(const char *filename, Image *image) {
		FILE *file;
		unsigned long size;                 // size of the image in bytes.
		unsigned long i;                    // standard counter.
		unsigned short int planes;          // number of planes in image (must be 1) 
		unsigned short int bpp;             // number of bits per pixel (must be 24)
		char temp;                          // temporary color storage for bgr-rgb conversion.

		// make sure the file is there.
		if ((file = fopen(filename, "rb"))==NULL)
		{
		printf("File Not Found : %s\n",filename);
		return 0;
		}
		
		// seek through the bmp header, up to the width/height:
		fseek(file, 18, SEEK_CUR);

		// read the width
		if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
		}
		printf("Width of %s: %lu\n", filename, image->sizeX);
		
		// read the height 
		if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
		}
		printf("Height of %s: %lu\n", filename, image->sizeY);
		
		// calculate the size (assuming 24 bits or 3 bytes per pixel).
		size = image->sizeX * image->sizeY * 3;

		// read the planes
		if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
		}
		if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
		}

		// read the bpp
		if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
		}
		if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
		}
		
		// seek past the rest of the bitmap header.
		fseek(file, 24, SEEK_CUR);

		// read the data. 
		image->data = (char *) malloc(size);
		if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;	
		}

		if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
		}

		for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
		}
		

		return 1;
	}
		
	// Load Bitmaps And Convert To Textures
	void LoadGLTextures() {	
		
		
		// Load Texture
		Image *image1;
		
		// allocate space for texture
		image1 = (Image *) malloc(sizeof(Image));
		if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
		}

		if (!ImageLoad("./img/skulls.bmp", image1)) {
		exit(1);
		}        

		// Create Texture	
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
		// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	};

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
	   glColor3f(0,1,0);
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
		 
	     glColor3f(0.8,0.8,0);
	     glTranslatef(0,-10,0);
	     
	     glEnable(GL_TEXTURE_2D);
	     glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
	     glBegin(GL_QUADS);		                // begin drawing a cube
			 glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			 glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			 glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
			 glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		 glEnd(); 
		 glTranslatef(0,4,0);
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
		drawFistLeft();
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
	     glTranslatef(-0.75,0,0);
	     glRotatef(90,0,1,0);
	    drawCylinder(0.1,1.5);
	 }
	 
	 void drawWheelLeft() {
	    drawCylinder(1.25,0.5);
	 }
	 
	 void drawAxleRight() {
	    glTranslatef(0.75,0,0);
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
	void drawRobot(){
	    glScalef(0.08,0.08,0.08);
	    assign_states();
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
