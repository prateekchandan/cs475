#include "transformer.hpp"
#include "Imageloader.hpp"

void transformer::LoadGLTextures() {	

	// Load Texture
	Image *image[5];
	
	// allocate space for texture
	image[0] = (Image *) malloc(sizeof(Image));
	image[1] = (Image *) malloc(sizeof(Image));
	image[2] = (Image *) malloc(sizeof(Image));
	image[3] = (Image *) malloc(sizeof(Image));
	image[4] = (Image *) malloc(sizeof(Image));
	if (image[0] == NULL || image[2]==NULL || image[3]==NULL || image[4]==NULL || image[1]==NULL) {
	printf("Error allocating space for image");
	exit(0);
	}
	
	char a[5][100];
	strcpy(a[0],"./img/logo.bmp");
	strcpy(a[1],"./img/metal.bmp");
	strcpy(a[2],"./img/face.bmp");
	strcpy(a[3],"./img/skin.bmp");
	strcpy(a[4],"./img/flap.bmp");

	
	Imageloader img_loader;
	for (int i = 0; i < 4; i++)
	{
		if (!img_loader.ImageLoad(a[i], image[i])) {
			exit(1);
		} 
	}
	
	for (int i = 0; i < 4; i++)
	{
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);   // 2d texture (x and y size)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image[i]->sizeX, image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->data);
	}
	
	glEnable(GL_TEXTURE_2D);
};

void transformer::drawUnitCube(){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
		glBegin(GL_POLYGON);	       
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,0.0f,1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f);  glVertex3f(1.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f);  glVertex3f(1.0f,0.0f,1.0f);
			glTexCoord2f(0.0f, 1.0f);  glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,1.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
		    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,0.0f,1.0f);
		glEnd();
}
	
void transformer::drawRobot(){
	    // Scaled for robot to fit the screen
	    
	    glTranslatef(0,0,velocity);
	    
	    glScalef(0.08,0.08,0.08);
	    glRotatef(75, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		
	    assign_states();
	    
	    // Model starts here
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


void transformer::turnRobotLeft(){
	if(turning_factor>-25)
		turning_factor-=2;
}

void transformer::turnRobotRight(){
	if(turning_factor<25)
		turning_factor+=2;
}

void transformer::accelerate(){
	if(velocity<10)
		velocity+=0.003;
}

void transformer::breakCar(){
	if(velocity>-10)
		velocity-=0.003;
}
