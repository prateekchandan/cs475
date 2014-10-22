#include "environment.hpp"
#include "transformer.hpp"
#include <iostream>
#include <SOIL/SOIL.h>


// Load Bitmaps And Convert To Textures
void environment::LoadGLTextures() {
	
	char a[100][100];
	
	strcpy(a[0],"img/road.jpg");
	strcpy(a[1],"img/grass.jpg");
	strcpy(a[2],"img/sky.jpg");
	strcpy(a[3],"img/horizon.jpg");
	
	for (int i = 0; i < no_of_textures; i++)
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


void environment::setup(){
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
	gluPerspective(50,1, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
        
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
    
    GLfloat light_position[] = { 0.0, 5.0, 0.0, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.2 };
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	
	
	GLfloat light_position1[] = { 0.0, 5.0, 5.0, 0.0 };
	GLfloat light_diffuse1[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_ambient1[] = { 0.0, 0.0, 0.0, 1.0};
	
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	
	glEnable(GL_DEPTH_TEST);
	
    
}

void environment::set_env_lightings(){
	
	if(sunlight)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
		
	if(moonlight)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	
}

void environment::toggle_Sunlight(){
	sunlight++;
	sunlight%=2;
	
	moonlight++;
	moonlight%=2;
}

void environment::set_ground(){
	
    float car_z=t.position_z;
    int z_offset=(int)car_z/10;
	set_env_lightings();
	
	glEnable(GL_TEXTURE_2D);
	
	// Drawing grass
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1,1,1);
	for (int i = 0; i < 20; i++)
	{
		for (int j = z_offset-10; j < z_offset+20; j++)
		{
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+10*i,-0.1,-90+10*j);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(-90+10*i,-0.1,-90+10*j);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(-90+10*i,-0.1,-100+10*j);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+10*i,-0.1,-100+10*j);
			glEnd();
		}
	}
	
	// Drawing sky
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,30,100+t.position_z);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(100,30,100+t.position_z);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(100,30,-100+t.position_z);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,30,-100+t.position_z);
	glEnd();
	
	// Drawing horizon
	
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,31,80+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100,31,80+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100,-0.2,80+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,-0.2,80+t.position_z);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,31,-80+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100,31,-80+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100,-0.2,-80+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,-0.2,-80+t.position_z);
	glEnd();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(100,31.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100,31.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(100,-0.2,-100+t.position_z);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100,31.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-100,31.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-100,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100,-0.2,-100+t.position_z);
	glEnd();
	set_roads();
	
	// Drawing side walls
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(20,5.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(20,5.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(20,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(20,-0.2,-100+t.position_z);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20,5.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-20,5.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-20,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-20,-0.2,-100+t.position_z);
	glEnd();
	set_roads();
}

void environment::set_roads(){
	
	float x1=-2,x2=2,x3=2,x4=-2,z1=-5,z2=-5,z3=5,z4=5,a=0,cum_a=0;
	float x=0,z=0;
	float car_z=t.position_z;
	//float car_x=t.position_x;
	
	int road_cur_no=0;//(int)car_z/10;
	
	int random_no=(rand()%10 - 5)*M_PI/180.0;
	if(road_no<road_cur_no)
	{
		road_angles.push_back(random_no);
		road_angles.pop_front();
	}
	else if(road_no>road_cur_no)
	{
		road_angles.push_front(random_no);
		road_angles.pop_back();
	}
	road_no=road_cur_no;
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	
	for (int i = 100; i >=0 ; i--)
	{
		glBegin(GL_POLYGON);
			glColor3f(0.0,0.1,0.3);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(x1,0,z1);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x2,0,z2);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(x3,0,z3);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(x4,0,z4);
		glEnd();
		
		x1= x1 + 8* sin(cum_a);
		z1 = z1 + 8* cos(cum_a);
		x2= x2 + 8* sin(cum_a);
		z2 = z2 + 8* cos(cum_a);
		
		if(i>0)
			a=road_angles.at(i-1);
			
		cum_a+=a;
		
		x3= x2 + 10* sin(cum_a);
		z3 = z2 + 10* cos(cum_a);
		x4= x1 + 10* sin(cum_a);
		z4 = z1 + 10* cos(cum_a);
		
	}
	
	x1=-2;x2=2;x3=2;x4=-2;z1=5;z2=5;z3=-5;z4=-5;cum_a=0;
	for (int i = 100; i <200 ; i++)
	{
		glBegin(GL_POLYGON);
			glColor3f(0.0,0.1,0.3);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(x1,0,z1);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x2,0,z2);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(x3,0,z3);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(x4,0,z4);
		glEnd();
	
		
		x1= x1 + 8* sin(cum_a);
		z1 = z1 - 8* cos(cum_a);
		x2= x2 + 8* sin(cum_a);
		z2 = z2 - 8* cos(cum_a);
		
		if(i<200)
		a=road_angles.at(i+1);
		cum_a+=a;
		
		x3= x2 + 10* sin(cum_a);
		z3 = z2 - 10* cos(cum_a);
		x4= x1 + 10* sin(cum_a);
		z4 = z1 - 10* cos(cum_a);
		
	}
	glPopMatrix();
}
