#include "transformer.hpp"
#include <SOIL/SOIL.h>

void transformer::LoadGLTextures() {	
	
	char a[4][100];
	strcpy(a[0],"img/logo.png");
	strcpy(a[1],"img/metal.png");
	strcpy(a[2],"img/face.png");
	strcpy(a[3],"img/skin.png");
	
	for (int i = 0; i < 4; i++)
	{
		texture[i]=SOIL_load_OGL_texture(
			a[i],
			 SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
		if(texture[i] == 0)
		{
			cout<<"Failed to load "<<a[i]<<" : "<<SOIL_last_result()<<"\n";
		}
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
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
	    wheel_rotation+=speed*30;
	    if(wheel_rotation>360)
			wheel_rotation-=360;
		if(wheel_rotation<-360)
			wheel_rotation+=360;
	    
		glTranslatef(position_x, 0, position_z);
	    glScalef(0.2,0.2,0.2);
		glRotatef(-angle, 0, 1, 0);
		glTranslatef(0, 3, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(-2, 0, 0);
		
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
		            //drawHeadLight();
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
		            //drawHeadLight();
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
	if(turning_factor<24)
		turning_factor+=3;
}

void transformer::turnRobotRight(){
	is_turning=true;
	if(turning_factor>-24)
		turning_factor-=3;
}

void transformer::restoreTurning(){
	if(is_turning){
		//cout<<"success"<<endl;
		return;
	}

	if(turning_factor>0)
		turning_factor-=3;
	else if(turning_factor<0)
		turning_factor+=3;
}

void transformer::drawHeadLight(){
		if(headlight==0)
		{
			glDisable(GL_LIGHT2);
			return;
		}
		glEnable(GL_LIGHT2);
	
	GLfloat light_position[] = {position_x+dir_x*4,1,position_z+dir_z*4,1};
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_ambient);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30);
	GLfloat spot_direction[] = {dir_x, -0.5, dir_z ,0};
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	 glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,1000.0f);
	
		
}

