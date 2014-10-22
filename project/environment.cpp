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
    
    GLfloat light_position[] = { 0.0, 5.0, 5.0, 1.0 };
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
	glPushMatrix();
	glScalef(2,2,2);
    float car_z=t.position_z,car_x=t.position_x;
    long long z_offset=(int)car_z/10;
    long long x_offset=(int)car_x/10;
	set_env_lightings();
	
	glEnable(GL_TEXTURE_2D);
	
	// Drawing grass
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1,1,1);
	for (long long i = x_offset - 20; i < x_offset+20; i++)
	{
		for (long long j = z_offset-20; j < z_offset+20; j++)
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
				glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+car_x,30,100+t.position_z);
				glTexCoord2f(1.0f, 0.0f);glVertex3f(100+car_x,30,100+t.position_z);
				glTexCoord2f(1.0f, 1.0f);glVertex3f(100+car_x,30,-100+t.position_z);
				glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+car_x,30,-100+t.position_z);
	glEnd();
	
	// Drawing horizon
	
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+car_x,31,80+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100+car_x,31,80+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100+car_x,-0.2,80+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+car_x,-0.2,80+t.position_z);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+car_x,31,-80+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100+car_x,31,-80+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100+car_x,-0.2,-80+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+car_x,-0.2,-80+t.position_z);
	glEnd();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(100+car_x,31.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(100+car_x,31.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(100+car_x,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(100+car_x,-0.2,-100+t.position_z);
	glEnd();
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-100+car_x,31.2,-100+t.position_z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-100+car_x,31.2,100+t.position_z);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-100+car_x,-0.2,100+t.position_z);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-100+car_x,-0.2,-100+t.position_z);
	glEnd();
	set_roads();
	
	set_roads();
	glPopMatrix();
}

void environment::draw_curved_road(){
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	float curve_point[][3]={{16.970562748477537, 0.0, 16.970562748476745},
							{19.95527069526132, 0.0, 13.333685592470104},
							{22.173108780270987, 0.0, 9.184402376761897},
							{23.53884672967756, 0.0, 4.682167728386941},
							{24.0, 0.0, 0.0},
							{20.0, 0.0, 0.0},
							{19.61570560806463, 0.0, 3.9018064403224506},
							{18.477590650225824, 0.0, 7.65366864730158},
							{16.6293922460511, 0.0, 11.111404660391752},
							{14.14213562373128, 0.0, 14.14213562373062},
							};
		glPushMatrix();
		glRotatef(180,0,0,1);
		glScalef(1,1,-1);
		glTranslatef(-22,0,0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 10; i++)
		{
			float x,y;
			if(i<=4)
			{
				x=1.0;
				y=1.0-0.25*i;
			}
			else{
				x=0.0;
				y=0.25*(i-5);
			}
			glTexCoord2f(x, y);glVertex3f(curve_point[i][0],curve_point[i][1],curve_point[i][2]);
		}
		glEnd();
		glPopMatrix();
}

void environment::draw_curved_road_90(){
	float angle=0,x=0,y=0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(x,0,-1*y);
			glRotatef(-1*angle*180.0/M_PI,0,1,0);
			draw_curved_road();
		glPopMatrix();
		angle+=45*(M_PI/180);
		y=22*sin(angle);
		x=22.0*(1.0-cos(angle));
		
	}
}

void environment::draw_straight_road(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);glVertex3f(-2.0,0,0.0);
			glTexCoord2f(1, 0);glVertex3f(2.0,0,0.0);
			glTexCoord2f(1, 1);glVertex3f(2.0,0,-22.0);
			glTexCoord2f(0, 1);glVertex3f(-2.0,0,-22.0);
		glEnd();
	glPopMatrix();	
	
}
void environment::set_roads(){
	
	glPushMatrix();
		draw_curved_road_90();
		
		glPushMatrix();
			glTranslatef(22,0,-22);
			glRotatef(-90,0,1,0);
			draw_straight_road();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(44,0,-22);
			glRotatef(-90,0,1,0);
			draw_straight_road();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(88,0,-44);
			glScalef(-1,1,-1);
			draw_curved_road_90();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(88,0,-44);
			draw_straight_road();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(88,0,-66);
			draw_curved_road_90();
		glPopMatrix();
		
	glPopMatrix();	
}
