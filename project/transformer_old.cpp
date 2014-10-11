#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
typedef unsigned char BYTE; 
using namespace std;

struct transformer{
	int sequence_number_wheels, sequence_number_hands, sequence_number_legs;
	double color_red, color_green, color_blue;
	double color_variant;
	double cube_index;

	
	/**
	 * Function Name : LoadTexture();
	 * loads a textures
	 * */
	GLuint LoadTexture(const char * pic, int width, int height)
	{
		GLuint Texture;
		BYTE * data;
		FILE * picfile;

		picfile = fopen(pic, "rb");
		if (picfile == NULL)
			return 0;

		data = (BYTE *)malloc(width * height * 3);

		fread(data, width * height, 3, picfile);
		fclose(picfile);
		
		glGenTextures(1, &Texture);
		//glBindTexture(GL_TEXTURE_2D,  Texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		free(data);
		return Texture;
	}

	void drawWheel(double radius, double width) {
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
	
	void drawUnitCube(){
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		
		GLuint myTex;
		myTex = LoadTexture("./img/paper.bmp", 1,1);
		glBindTexture(GL_TEXTURE_2D, myTex);
		
		glBegin(GL_POLYGON);
			glColor3f(color_red, color_green, color_blue);		        // Top of triangle (front)
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red, color_green, color_blue);		        // Top of triangle (front)
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-color_variant), color_green*(1.0f-color_variant), color_blue*(1.0f-color_variant));		        // Top of triangle (front)
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-color_variant), color_green*(1.0f-color_variant), color_blue*(1.0f-color_variant));		        // Top of triangle (front)
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,0.0f);
			glVertex3f(1.0f,1.0f,1.0f);
			glVertex3f(0.0f,1.0f,1.0f);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3f(color_red*(1.0f-2*color_variant), color_green*(1.0f-2*color_variant), color_blue*(1.0f-2*color_variant));		        // Top of triangle (front)
			glVertex3f(0.0f,0.0f,0.0f);
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
		glDisable(GL_TEXTURE_2D);
	}

	void drawCuboid(double width, double height, double length){
		glScalef(width, height, length);
		GLubyte list[1];
		list[0]=cube_index;
		glPushMatrix();
		glCallLists(1,GL_UNSIGNED_BYTE,list);
		glPopMatrix();
		glScalef(1/width, 1/height, 1/length);
		/*
		 *glBegin(GL_POLYGON);
		 *    glColor3f(1.0f,0.0f,0.0f);		        // Top of triangle (front)
		 *    glVertex3f(0.0f,0.0f,0.0f);
		 *    glVertex3f(width,0.0f,0.0f);
		 *    glVertex3f(width,height,0.0f);
		 *    glVertex3f(0.0f,height,0.0f);
		 *glEnd();
		 *glBegin(GL_POLYGON);
		 *    glColor3f(1.0f,0.0f,0.0f);
		 *    glVertex3f(0.0f,0.0f,length);
		 *    glVertex3f(width,0.0f,length);
		 *    glVertex3f(width,height,length);
		 *    glVertex3f(0.0f,height,length);
		 *glEnd();
		 *glBegin(GL_POLYGON);
		 *    glColor3f(0.9f,0.0f,0.0f);
		 *    glVertex3f(0.0f,0.0f,0.0f);
		 *    glVertex3f(width,0.0f,0.0f);
		 *    glVertex3f(width,0.0f,length);
		 *    glVertex3f(0.0f,0.0f,length);
		 *glEnd();
		 *glBegin(GL_POLYGON);
		 *    glColor3f(0.9f,0.0f,0.0f);
		 *    glVertex3f(0.0f,height,0.0f);
		 *    glVertex3f(width,height,0.0f);
		 *    glVertex3f(width,height,length);
		 *    glVertex3f(0.0f,height,length);
		 *glEnd();
		 *glBegin(GL_POLYGON);
		 *    glColor3f(0.8f,0.0f,0.0f);
		 *    glVertex3f(0.0f,0.0f,0.0f);
		 *    glVertex3f(0.0f,height,0.0f);
		 *    glVertex3f(0.0f,height,length);
		 *    glVertex3f(0.0f,0.0f,length);
		 *glEnd();
		 *glBegin(GL_POLYGON);
		 *    glColor3f(0.8f,0.0f,0.0f);
		 *    glVertex3f(width,0.0f,0.0f);
		 *    glVertex3f(width,height,0.0f);
		 *    glVertex3f(width,height,length);
		 *    glVertex3f(width,0.0f,length);
		 *glEnd();
		 */
	}

	double steps;

	double max_head_disp;
	double head_speed;
	double cur_head_disp;

	void animateHead() {
		if(sequence_number >= 44) {
			glTranslatef(0.0, cur_head_disp, 0.0);
			cur_head_disp -= head_speed;
			if(cur_head_disp >= 0) sequence_number=-1;
		}
		else if(sequence_number >= 0){
			if(sequence_number == 0) {
				glTranslatef(0.0, cur_head_disp, 0.0);
				cur_head_disp += head_speed;
				if(cur_head_disp <= max_head_disp) sequence_number++;
			}
			else {
				glTranslatef(0.0, max_head_disp, 0.0);
			}
		}
	}

	double max_left_hand1_disp;
	double left_hand1_speed;
	double cur_left_hand1_disp;

	double max_left_hand1_rot;
	double left_hand1_rot_speed;
	double cur_left_hand1_rot;

	void animateLeftHand1() {
		bool s3 = true, s1 = true;
		if(sequence_number >= 43) {
			s1 = false;
			if(sequence_number == 43) {
				glTranslatef(0, 0, cur_left_hand1_disp);
				cur_left_hand1_disp -= left_hand1_speed;
				if(cur_left_hand1_disp <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 41) {
			s3 = false;
			if(sequence_number == 41) {
				glTranslatef(0.0, 0.05, max_left_hand1_disp);
				glRotatef(cur_left_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.05, -max_left_hand1_disp);
				cur_left_hand1_rot -= left_hand1_rot_speed;
				if(cur_left_hand1_rot <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 3 && s3) {
			if(sequence_number == 3) {
				glTranslatef(0.0, 0.05, max_left_hand1_disp);
				glRotatef(cur_left_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.05, -max_left_hand1_disp);
				cur_left_hand1_rot += left_hand1_rot_speed;
				if(cur_left_hand1_rot >= max_left_hand1_rot) sequence_number++;
			}
			else { 
				glTranslatef(0.0, 0.05, max_left_hand1_disp);
				glRotatef(max_left_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.05, -max_left_hand1_disp);
			}
		}
		if(sequence_number >= 1 && s1) {
			if(sequence_number == 1) {
				glTranslatef(0, 0, cur_left_hand1_disp);
				cur_left_hand1_disp += left_hand1_speed;
				if(cur_left_hand1_disp >= max_left_hand1_disp) sequence_number++;
			}
			else glTranslatef(0, 0, max_left_hand1_disp);
		}
	}


	double max_left_hand2_rot;
	double left_hand2_rot_speed;
	double cur_left_hand2_rot;

	void animateLeftHand2() {
		if(sequence_number >= 42) {
			if(sequence_number == 42) {
				glRotatef(cur_left_hand2_rot, 0, 1, 0);
				cur_left_hand2_rot -= left_hand2_rot_speed;
				if(cur_left_hand2_rot <= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 2) {
			if(sequence_number == 2) {
				glRotatef(cur_left_hand2_rot, 0, 1, 0);
				cur_left_hand2_rot += left_hand2_rot_speed;
				if(cur_left_hand2_rot >= max_left_hand2_rot) sequence_number++;
			}
			else glRotatef(max_left_hand2_rot, 0, 1, 0);
		}
	}

	double max_right_hand1_disp;
	double right_hand1_speed;
	double cur_right_hand1_disp;

	double max_right_hand1_disp1;
	double right_hand1_speed1;
	double cur_right_hand1_disp1;

	double max_right_hand1_rot;
	double right_hand1_rot_speed;
	double cur_right_hand1_rot;

	void animateRightHand1() {
		bool s7 = true, s5 = true, s4 = true;
		if(sequence_number >= 40) {
			s4 = false;
			if(sequence_number == 40) {
				glTranslatef(0, 0, cur_right_hand1_disp);
				cur_right_hand1_disp -= right_hand1_speed;
				if(cur_right_hand1_disp <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 39) {
			s5 = false;
			if(sequence_number == 39) {
				glTranslatef(0, cur_right_hand1_disp1,0);
				cur_right_hand1_disp1 -= right_hand1_speed1;
				if(cur_right_hand1_disp1 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 37) {
			s7 = false;
			if(sequence_number == 37) {
				glTranslatef(0.0, 0.35, 0.0);
				glRotatef(cur_right_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.35, 0.0);
				cur_right_hand1_rot -= right_hand1_rot_speed;
				if(cur_right_hand1_rot >= 0) sequence_number++;
			}
		}
		if(sequence_number >= 7 && s7) {
			if(sequence_number == 7) {
				glTranslatef(0.0, 0.35, 0.0);
				glRotatef(cur_right_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.35, 0.0);
				cur_right_hand1_rot += right_hand1_rot_speed;
				if(cur_right_hand1_rot <= max_right_hand1_rot) sequence_number++;
			}
			else { 
				glTranslatef(0.0, 0.35, 0.0);
				glRotatef(max_right_hand1_rot, 0, 0, 1);
				glTranslatef(0.0, -0.35, 0.0);
			}
		}
		if(sequence_number >= 5 && s5) {
			if(sequence_number == 5) {
				glTranslatef(0, cur_right_hand1_disp1,0);
				cur_right_hand1_disp1 += right_hand1_speed1;
				if(cur_right_hand1_disp1 >= max_right_hand1_disp1) sequence_number++;
			}
			else glTranslatef(0, max_right_hand1_disp1,0);
		}
		if(sequence_number >= 4 && s4) {
			if(sequence_number == 4) {
				glTranslatef(0, 0, cur_right_hand1_disp);
				cur_right_hand1_disp += right_hand1_speed;
				if(cur_right_hand1_disp <= max_right_hand1_disp) sequence_number++;
			}
			else glTranslatef(0, 0, max_right_hand1_disp);
		}
	}


	double max_right_hand2_rot;
	double right_hand2_rot_speed;
	double cur_right_hand2_rot;

	void animateRightHand2() {
		if(sequence_number >= 38) {
			if(sequence_number == 38) {
				glRotatef(cur_right_hand2_rot, 0, 1, 0);
				cur_right_hand2_rot -= right_hand2_rot_speed;
				if(cur_right_hand2_rot <= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 6) {
			if(sequence_number == 6) {
				glRotatef(cur_right_hand2_rot, 0, 1, 0);
				cur_right_hand2_rot += right_hand2_rot_speed;
				if(cur_right_hand2_rot >= max_right_hand2_rot) sequence_number++;
			}
			else glRotatef(max_right_hand2_rot, 0, 1, 0);

		}
	}


	double max_left_foot2_rot;
	double left_foot2_rot_speed;
	double cur_left_foot2_rot;

	void animateLeftFoot2() {
		if(sequence_number >= 36) {
			if(sequence_number == 36) {
				glTranslatef(0,0,0.075);
				glRotatef(cur_left_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
				cur_left_foot2_rot -= left_foot2_rot_speed;
				if(cur_left_foot2_rot >= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 8) {
			if(sequence_number == 8) {
				glTranslatef(0,0,0.075);
				glRotatef(cur_left_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
				cur_left_foot2_rot += left_foot2_rot_speed;
				if(cur_left_foot2_rot <= max_left_foot2_rot) sequence_number++;
			}
			else{
				glTranslatef(0,0,0.075);
				glRotatef(max_left_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
			}
		}
	}



	double max_left_foot1_rot;
	double left_foot1_rot_speed;
	double cur_left_foot1_rot;

	double max_left_foot1_rot1;
	double left_foot1_rot_speed1;
	double cur_left_foot1_rot1;

	double max_left_foot1_disp;
	double left_foot1_disp_speed;
	double cur_left_foot1_disp;

	double max_left_foot1_rot2;
	double left_foot1_rot_speed2;
	double cur_left_foot1_rot2;

	double max_left_foot1_disp1;
	double left_foot1_disp_speed1;
	double cur_left_foot1_disp1;

	void animateLeftFoot1() {
		bool s13 = true, s12 = true, s11 = true, s10 = true, s9 = true;
		if(sequence_number >= 35) {
			s9 = false;
			if(sequence_number == 35) {
				glRotatef(cur_left_foot1_rot, 1, 0, 0);
				cur_left_foot1_rot -= left_foot1_rot_speed;
				if(cur_left_foot1_rot <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 34) {
			s10 = false;
			if(sequence_number == 34) {
				glTranslatef(0.125,0,0);
				glRotatef(cur_left_foot1_rot1, 0, 0, 1);
				glTranslatef(-0.125,0,0);
				cur_left_foot1_rot1 -= left_foot1_rot_speed1;
				if(cur_left_foot1_rot1 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 33) {
			s11 = false;
			if(sequence_number == 33) {
				glTranslatef(cur_left_foot1_disp, 0, 0);
				cur_left_foot1_disp -= left_foot1_disp_speed;
				if(cur_left_foot1_disp <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 32) {
			s12 = false;
			if(sequence_number == 32) {
				glTranslatef(0,0.075,0);
				glRotatef(cur_left_foot1_rot2, 1, 0, 0);
				glTranslatef(0,-0.075,0);
				cur_left_foot1_rot2 -= left_foot1_rot_speed2;
				if(cur_left_foot1_rot2 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 31) {
			s13 = false;
			if(sequence_number == 31) {
				glTranslatef(0, cur_left_foot1_disp1, 0);
				cur_left_foot1_disp1 -= left_foot1_disp_speed1;
				if(cur_left_foot1_disp1 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 13 && s13) {
			if(sequence_number == 13) {
				glTranslatef(0, cur_left_foot1_disp1, 0);
				cur_left_foot1_disp1 += left_foot1_disp_speed1;
				if(cur_left_foot1_disp1 >= max_left_foot1_disp1) sequence_number++;
			}
			else glTranslatef(0, max_left_foot1_disp1, 0);
		}
		if(sequence_number >= 12 && s12) {
			if(sequence_number == 12) {
				glTranslatef(0,0.075,0);
				glRotatef(cur_left_foot1_rot2, 1, 0, 0);
				glTranslatef(0,-0.075,0);
				cur_left_foot1_rot2 += left_foot1_rot_speed2;
				if(cur_left_foot1_rot2 >= max_left_foot1_rot2) sequence_number++;
			}
			else{
				glTranslatef(0,0.075,0);
				glRotatef(max_left_foot1_rot2, 2, 0, 0);
				glTranslatef(0,-0.075,0);
			}
		}
		if(sequence_number >= 11 && s11) {
			if(sequence_number == 11) {
				glTranslatef(cur_left_foot1_disp, 0, 0);
				cur_left_foot1_disp += left_foot1_disp_speed;
				if(cur_left_foot1_disp >= max_left_foot1_disp) sequence_number++;
			}
			else glTranslatef(max_left_foot1_disp, 0, 0);
		}
		if(sequence_number >= 10 && s10) {
			if(sequence_number == 10) {
				glTranslatef(0.125,0,0);
				glRotatef(cur_left_foot1_rot1, 0, 0, 1);
				glTranslatef(-0.125,0,0);
				cur_left_foot1_rot1 += left_foot1_rot_speed1;
				if(cur_left_foot1_rot1 >= max_left_foot1_rot1) sequence_number++;
			}
			else{
				glTranslatef(0.125,0,0);
				glRotatef(max_left_foot1_rot1, 0, 0, 1);
				glTranslatef(-0.125,0,0);
			}
		}
		if(sequence_number >= 9 && s9) {
			if(sequence_number == 9) {
				glRotatef(cur_left_foot1_rot, 1, 0, 0);
				cur_left_foot1_rot += left_foot1_rot_speed;
				if(cur_left_foot1_rot >= max_left_foot1_rot) sequence_number++;
			}
			else glRotatef(max_left_foot1_rot, 1, 0, 0);
		}
	}


	double max_right_foot2_rot;
	double right_foot2_rot_speed;
	double cur_right_foot2_rot;

	void animateRightFoot2() {
		if(sequence_number >= 30) {
			if(sequence_number == 30) {
				glTranslatef(0,0,0.075);
				glRotatef(cur_right_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
				cur_right_foot2_rot -= right_foot2_rot_speed;
				if(cur_right_foot2_rot >= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 14) {
			if(sequence_number == 14) {
				glTranslatef(0,0,0.075);
				glRotatef(cur_right_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
				cur_right_foot2_rot += right_foot2_rot_speed;
				if(cur_right_foot2_rot <= max_right_foot2_rot) sequence_number++;
			}
			else{
				glTranslatef(0,0,0.075);
				glRotatef(max_right_foot2_rot, 0, 1, 0);
				glTranslatef(0,0,-0.075);
			}
		}
	}


	double max_right_foot1_rot;
	double right_foot1_rot_speed;
	double cur_right_foot1_rot;

	double max_right_foot1_rot1;
	double right_foot1_rot_speed1;
	double cur_right_foot1_rot1;

	double max_right_foot1_disp;
	double right_foot1_disp_speed;
	double cur_right_foot1_disp;

	double max_right_foot1_rot2;
	double right_foot1_rot_speed2;
	double cur_right_foot1_rot2;

	double max_right_foot1_disp1;
	double right_foot1_disp_speed1;
	double cur_right_foot1_disp1;

	void animateRightFoot1() {
		bool s19 = true, s18 = true, s17 = true, s16 = true, s15 = true;
		if(sequence_number >= 29) {
			s15 = false;
			if(sequence_number == 29) {
				glTranslatef(cur_right_foot1_disp, 0, 0);
				cur_right_foot1_disp -= right_foot1_disp_speed;
				if(cur_right_foot1_disp >= 0) sequence_number++;
			}
		}
		if(sequence_number >= 28) {
			s16 = false;
			if(sequence_number == 28) {
				glRotatef(cur_right_foot1_rot, 0, 0, 1);
				cur_right_foot1_rot -= right_foot1_rot_speed;
				if(cur_right_foot1_rot <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 27) {
			s17 = false;
			if(sequence_number == 27) {
				glRotatef(cur_right_foot1_rot1, 1, 0, 0);
				cur_right_foot1_rot1 -= right_foot1_rot_speed1;
				if(cur_right_foot1_rot1 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 26) {
			s18 = false;
			if(sequence_number == 26) {
				glTranslatef(0, 0, cur_right_foot1_disp1);
				cur_right_foot1_disp1 -= right_foot1_disp_speed1;
				if(cur_right_foot1_disp1 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 25) {
			s19 = false;
			if(sequence_number == 25) {
				glRotatef(cur_right_foot1_rot2, 1, 0, 0);
				cur_right_foot1_rot2 -= right_foot1_rot_speed2;
				if(cur_right_foot1_rot2 <= 0) sequence_number++;
			}
		}
		if(sequence_number >= 19 && s19) {
			if(sequence_number == 19) {
				glRotatef(cur_right_foot1_rot2, 1, 0, 0);
				cur_right_foot1_rot2 += right_foot1_rot_speed2;
				if(cur_right_foot1_rot2 >= max_right_foot1_rot2) sequence_number++;
			}
			else{
				glRotatef(max_right_foot1_rot2, 1, 0, 0);
			}
		}
		if(sequence_number >= 18 && s18) {
			if(sequence_number == 18) {
				glTranslatef(0, 0, cur_right_foot1_disp1);
				cur_right_foot1_disp1 += right_foot1_disp_speed1;
				if(cur_right_foot1_disp1 >= max_right_foot1_disp1) sequence_number++;
			}
			else glTranslatef(0, 0, max_right_foot1_disp1);
		}
		if(sequence_number >= 17 && s17) {
			if(sequence_number == 17) {
				glRotatef(cur_right_foot1_rot1, 1, 0, 0);
				cur_right_foot1_rot1 += right_foot1_rot_speed1;
				if(cur_right_foot1_rot1 >= max_right_foot1_rot1) sequence_number++;
			}
			else{
				glRotatef(max_right_foot1_rot1, 1, 0, 0);
			}
		}
		if(sequence_number >= 16 && s16) {
			if(sequence_number == 16) {
				glRotatef(cur_right_foot1_rot, 0, 0, 1);
				cur_right_foot1_rot += right_foot1_rot_speed;
				if(cur_right_foot1_rot >= max_right_foot1_rot) sequence_number++;
			}
			else{
				glRotatef(max_right_foot1_rot, 0, 0, 1);
			}
		}
		if(sequence_number >= 15 && s15) {
			if(sequence_number == 15) {
				glTranslatef(cur_right_foot1_disp, 0, 0);
				cur_right_foot1_disp += right_foot1_disp_speed;
				if(cur_right_foot1_disp <= max_right_foot1_disp) sequence_number++;
			}
			else glTranslatef(max_right_foot1_disp, 0, 0);
		}
	}


	double max_wheel1_rot;
	double wheel1_rot_speed;
	double cur_wheel1_rot;

	void animateWheel1() {
		if(sequence_number >= 24) {
			if(sequence_number == 24) {
				glTranslatef(0.05,0,0.1);
				glRotatef(cur_wheel1_rot, 0, 1, 0);
				glTranslatef(-0.05,0,-0.1);
				cur_wheel1_rot -= wheel1_rot_speed;
				if(cur_wheel1_rot >= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 20) {
			if(sequence_number == 20) {
				glTranslatef(0.05,0,0.1);
				glRotatef(cur_wheel1_rot, 0, 1, 0);
				glTranslatef(-0.05,0,-0.1);
				cur_wheel1_rot += wheel1_rot_speed;
				if(cur_wheel1_rot <= max_wheel1_rot) sequence_number++;
			}
			else{
				glTranslatef(0.05,0,0.1);
				glRotatef(max_wheel1_rot, 0, 1, 0);
				glTranslatef(-0.05,0,-0.1);
			}
		}
	}


	double max_wheel2_rot;
	double wheel2_rot_speed;
	double cur_wheel2_rot;

	void animateWheel2() {
		if(sequence_number >= 23) {
			if(sequence_number == 23) {
				glTranslatef(0.15,0,0.1);
				glRotatef(cur_wheel2_rot, 0, 1, 0);
				glTranslatef(-0.15,0,-0.1);
				cur_wheel2_rot -= wheel2_rot_speed;
				if(cur_wheel2_rot <= 0) sequence_number++;
			}
		}
		else if(sequence_number >= 21) {
			if(sequence_number == 21) {
				glTranslatef(0.15,0,0.1);
				glRotatef(cur_wheel2_rot, 0, 1, 0);
				glTranslatef(-0.15,0,-0.1);
				cur_wheel2_rot += wheel2_rot_speed;
				if(cur_wheel2_rot >= max_wheel2_rot) sequence_number++;
			}
			else{
				glTranslatef(0.15,0,0.1);
				glRotatef(max_wheel2_rot, 0, 1, 0);
				glTranslatef(-0.15,0,-0.1);
			}
		}
	}

	transformer() {
		
		color_red = 0.7;
		color_green = 0;
		color_blue = 0;

		color_variant = 0.1;

		steps = 30;
		sequence_number = -1;

		max_head_disp = -0.11;
		head_speed = max_head_disp/steps;
		cur_head_disp = 0.0;

		max_left_hand1_disp = 0.025;
		left_hand1_speed = max_left_hand1_disp/steps;
		cur_left_hand1_disp = 0.0;

		max_left_hand1_rot = 180;
		left_hand1_rot_speed = max_left_hand1_rot/steps;
		cur_left_hand1_rot = 0;

		max_left_hand2_rot = 180;
		left_hand2_rot_speed = max_left_hand2_rot/steps;
		cur_left_hand2_rot = 0;

		max_right_hand1_disp = -0.025;
		right_hand1_speed = max_right_hand1_disp/steps;
		cur_right_hand1_disp = 0.0;

		max_right_hand1_disp1 = 0.05;
		right_hand1_speed1 = max_right_hand1_disp1/steps;
		cur_right_hand1_disp1 = 0.0;

		max_right_hand1_rot = -180;
		right_hand1_rot_speed = max_right_hand1_rot/steps;
		cur_right_hand1_rot = 0;

		max_right_hand2_rot = 180;
		right_hand2_rot_speed = max_right_hand2_rot/steps;
		cur_right_hand2_rot = 0;

		max_left_foot2_rot = -180;
		left_foot2_rot_speed = max_left_foot2_rot/steps;
		cur_left_foot2_rot = 0;

		max_left_foot1_rot = 180;
		left_foot1_rot_speed = max_left_foot1_rot/steps;
		cur_left_foot1_rot = 0;

		max_left_foot1_rot1 = 90;
		left_foot1_rot_speed1 = max_left_foot1_rot1/steps;
		cur_left_foot1_rot1 = 0;

		max_left_foot1_disp = 0.075;
		left_foot1_disp_speed = max_left_foot1_disp/steps;
		cur_left_foot1_disp = 0;

		max_left_foot1_rot2 = 90;
		left_foot1_rot_speed2 = max_left_foot1_rot2/steps;
		cur_left_foot1_rot2 = 0;

		max_left_foot1_disp1 = 0.075;
		left_foot1_disp_speed1 = max_left_foot1_disp1/steps;
		cur_left_foot1_disp1 = 0;

		max_right_foot2_rot = -180;
		right_foot2_rot_speed = max_right_foot2_rot/steps;
		cur_right_foot2_rot = 0;

		max_right_foot1_rot = 90;
		right_foot1_rot_speed = max_right_foot1_rot/steps;
		cur_right_foot1_rot = 0;

		max_right_foot1_rot1 = 90;
		right_foot1_rot_speed1 = max_right_foot1_rot1/steps;
		cur_right_foot1_rot1 = 0;

		max_right_foot1_disp = -0.075;
		right_foot1_disp_speed = max_right_foot1_disp/steps;
		cur_right_foot1_disp = 0;

		max_right_foot1_rot2 = 180;
		right_foot1_rot_speed2 = max_right_foot1_rot2/steps;
		cur_right_foot1_rot2 = 0;

		max_right_foot1_disp1 = 0.075;
		right_foot1_disp_speed1 = max_right_foot1_disp1/steps;
		cur_right_foot1_disp1 = 0;

		max_wheel1_rot = -90;
		wheel1_rot_speed = max_wheel1_rot/steps;
		cur_wheel1_rot = 0;

		max_wheel2_rot = 90;
		wheel2_rot_speed = max_wheel2_rot/steps;
		cur_wheel2_rot = 0;
	}



	void drawRobot() {
		glTranslatef(-0.15, -0.05,  0.0);
		glPushMatrix();
			
			drawCuboid(0.2,0.3,0.1);
			glPushMatrix();
				
				glTranslatef(0.05,0.31,0);
				animateHead();
				drawCuboid(0.1,0.1,0.1);

			glPopMatrix();
			glPushMatrix();
				
				glTranslatef(0.2,0.25,0.025);
				//glRotatef(rtri, 0.0, 0.0, 1.0);
				animateLeftHand1();
				drawCuboid(0.2,0.05,0.05);
				glPushMatrix();

					glTranslatef(0.2,0,0);
					//glRotatef(rtri, 0.0, 0.0, 1.0);
					animateLeftHand2();
					drawCuboid(0.2,0.05,0.05);

				glPopMatrix();

			glPopMatrix();
			glPushMatrix();

				animateRightHand1();
				glTranslatef(0.0, 0.25, 0.075);
				glRotatef(180, 0.0, 1.0, 0.0);
				//glRotatef(rtri, 0.0, 0.0, 1.0);
				drawCuboid(0.2,0.05,0.05);
				glPushMatrix();
					glTranslatef(0.2,0,0);
					animateRightHand2();
					//glRotatef(rtri, 0.0, 0.0, 1.0);
					drawCuboid(0.2,0.05,0.05);

				glPopMatrix();

			glPopMatrix();
			glPushMatrix();

				animateRightFoot1();
				glRotatef(-90, 0.0, 0.0, 1.0);
				drawCuboid(0.2, 0.075, 0.075);
				glPushMatrix();

					glTranslatef(0.2, 0.0, 0.0);
					animateRightFoot2();
					drawCuboid(0.2, 0.075, 0.075);

				glPopMatrix();

			glPopMatrix();
			glPushMatrix();

				animateLeftFoot1();
				glTranslatef(0.125, 0.0, 0.0);
				glRotatef(-90, 0.0, 0.0, 1.0);
				drawCuboid(0.2, 0.075, 0.075);
				glPushMatrix();

					glTranslatef(0.2, 0.0, 0.0);
					animateLeftFoot2();
					drawCuboid(0.2, 0.075, 0.075);

				glPopMatrix();

			glPopMatrix();
			glPushMatrix();

				animateWheel1();
				glTranslatef(0.05, 0.25, 0.125);
				drawWheel(0.05,0.06);

			glPopMatrix();
			glPushMatrix();

				animateWheel2();
				glTranslatef(0.15, 0.25, 0.125);
				drawWheel(0.05,0.06);

			glPopMatrix();
			glPushMatrix();

				animateWheel1();
				glTranslatef(0.05, 0.05, 0.125);
				drawWheel(0.05,0.06);

			glPopMatrix();
			glPushMatrix();

				animateWheel2();
				glTranslatef(0.15, 0.05, 0.125);
				drawWheel(0.05,0.06);

			glPopMatrix();

		glPopMatrix();
	}
};

