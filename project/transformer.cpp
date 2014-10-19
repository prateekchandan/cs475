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
	   t.restoreTurning();
	    
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
		
		is_turning=false;
	    
	}


void transformer::turnRobotLeft(){
	is_turning=true;
	if(turning_factor>-24)
		turning_factor-=4;
}

void transformer::turnRobotRight(){
	is_turning=true;
	if(turning_factor<24)
		turning_factor+=4;
}

void transformer::restoreTurning(){
	if(is_turning){
		//cout<<"success"<<endl;
		return;
	}
	
	//cout<<"poop"<<endl;
	if(turning_factor>0)
		turning_factor-=0.5;
	else if(turning_factor<0)
		turning_factor+=0.5;
}

