#include "transformer.hpp"
#include <SOIL/SOIL.h>

transformer::transformer()
{
	flap_toggle=-1;
	main_state=0;
	steps = 30;
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


	frame_index = 0;


	prev_state_head_flap = 0;
	prev_state_legs=0;
	prev_state_wheels=0;
	prev_state_flaps=0;
	prev_state_hands=0; 
	prev_turning_factor=0;
	prev_speed = 0;
	prev_position_x = 0;
	prev_position_z = 0;
	prev_dir_x = 0;
	prev_dir_z = -1;
	prev_angle = 0;
	prev_wheel_rotation=0;

	next_state_head_flap = 0;
	next_state_legs=0;
	next_state_wheels=0;
	next_state_flaps=0;
	next_state_hands=0;
	next_turning_factor=0;
	next_speed = 0;
	next_position_x = 0;
	next_position_z = 0;
	next_dir_x = 0;
	next_dir_z = -1;
	next_angle = 0;
	next_wheel_rotation=0;

	next_frame = 0;
	prev_frame = 0;

	state_export = false;

	keyfile.open("keys.txt" ,  ios::out | ios::in);


}

void transformer::drawUnitCylinder() {
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

void transformer::drawCylinder(double radius, double width) {
	glScalef(radius, radius, width);
	glPushMatrix();
	glCallList(cylinder_index);
	glPopMatrix();
	glScalef(1/radius, 1/radius, 1/width);
}

void transformer::drawWheelUnitCylinder(){
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

void transformer::drawWheelCylinder(double radius, double width){
	glScalef(radius, radius, width);
	glPushMatrix();
	drawWheelUnitCylinder();
	glPopMatrix();
	glScalef(1/radius, 1/radius, 1/width);
}

void transformer::createDisplayLists(){
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

void transformer::drawCube(double width, double height, double length) {
	glScalef(width, height, length);
	glPushMatrix();
	glCallList(cube_index);
	glPopMatrix();
	glScalef(1/width, 1/height, 1/length);
}

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

void transformer::assign_states(){
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
 * following 3 functions handle the turning of the car
 */
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

/**
 * function for drawing headlight
 */
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




void transformer::store_past(){
	//prev_turning_state = turning_state;
	//prev_motion_state = motion_state;
	prev_state_head_flap=state_head_flap;
	prev_state_legs     =state_legs     ;
	prev_state_wheels   =state_wheels   ;
	prev_state_flaps    =state_flaps    ;
	prev_state_hands    =state_hands    ;
	prev_turning_factor =turning_factor ;
	prev_speed          =speed          ;
	prev_position_x     =position_x     ;
	prev_position_z     =position_z     ;
	prev_dir_x          =dir_x          ;
	prev_dir_z          =dir_z          ;
	prev_angle          =angle          ;
	prev_wheel_rotation =wheel_rotation;;
}

bool transformer::state_change(){
	//return (turning_state != prev_turning_state) || (motion_state != prev_motion_state);
	return true;
}
