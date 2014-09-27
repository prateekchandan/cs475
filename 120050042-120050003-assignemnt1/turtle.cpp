/*
 * CS475/CS675 - Computer Graphics
 *  ToyLOGO Assignment Base Code
 *
 * Copyright 2011, Parag Chaudhuri, Department of CSE, IIT Bombay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glew.h>

#include "turtle.hpp"


void turtle_t::reset(void) 
{
	pos.x=0.0;
	pos.y=0.0;
	dir=0.0;
}

void turtle_t::clear(void)
{
	glClearColor(bgcol.r,bgcol.g, bgcol.b, 0.0); 
	glClearDepth(1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void turtle_t::set_pos(const vertex_t _pos)
{
	pos=_pos;
}

void turtle_t::set_pos(const double _x, const double _y)
{
	pos.x=_x;
	pos.y=_y;
}

void turtle_t::set_dir(const double _dir)
{
	dir=_dir; 
}

void turtle_t::set_col(const color_t _col)
{
	col=_col; 
	glColor3f(col.r, col.g, col.b);
}

void turtle_t::set_col(const double _r, const double _g, const double _b)
{
	col.r=_r;
	col.g=_g;
	col.b=_b;
	glColor3f(col.r, col.g, col.b);
}

void turtle_t::set_bgcol(const double _r, const double _g, const double _b)
{
	bgcol.r=_r;
	bgcol.b=_b;
	bgcol.g=_g;
}

void turtle_t::scale(const double _s)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1/_s,1/ _s,1.0);
}

void turtle_t::turn_left(const double _angle)    
{
	dir += (_angle*M_PI)/180 ;
	if (dir > M_PI * 2)
		dir-=M_PI * 2;
}

void turtle_t::turn_right(const double _angle)
{
	dir -= (_angle*M_PI)/180 ;
	if (dir < M_PI * -2)
		dir+=M_PI * 2;
}

void turtle_t::forward(const double _dist)  
{ 
	float x=pos.x,y=pos.y,newx,newy;
	newx= x + _dist * cos(dir);
	newy= y + _dist * sin(dir);
	glBegin(GL_LINES);
	glVertex2f(x,y);
	glVertex2f(newx,newy);
	glEnd();
	pos.x=newx;
	pos.y=newy;
}

void turtle_t::back(const double _dist)   
{
	float x=pos.x,y=pos.y,newx,newy;
	newx= x - _dist * cos(dir);
	newy= y - _dist * sin(dir);
	glBegin(GL_LINES);
	glVertex2f(x,y);
	glVertex2f(newx,newy);
	glEnd();
	pos.x=newx;
	pos.y=newy;
}

void turtle_t::forward_move(const double _dist)
{
	float x=pos.x,y=pos.y,newx,newy;
	newx= x + _dist * cos(dir);
	newy= y + _dist * sin(dir);
	pos.x=newx;
	pos.y=newy;
}

void turtle_t::backward_move(const double _dist)
{
	float x=pos.x,y=pos.y,newx,newy;
	newx= x - _dist * cos(dir);
	newy= y - _dist * sin(dir);
	pos.x=newx;
	pos.y=newy;
}

void turtle_t::pause(const double _tim)
{
	usleep(_tim);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void turtle_t::repeat(const unsigned int &_n, const turtle_com_list_t &_replist)
{
	for (unsigned int i = 0; i < _n; i++)
	{
		for (unsigned int j = 0; j < _replist.size(); j++)
		{
			exec(_replist[j]);
		}
		
	}
	
}

void turtle_t::exec(turtle_com_t *com)
{

	if (com->cname==F)
	{
		turtle_fwd_t* fcom = dynamic_cast<turtle_fwd_t*>(com);
		if (fcom) forward(fcom->dist);
	}
	else if (com->cname==B)
	{
		turtle_bck_t* bcom = dynamic_cast<turtle_bck_t*>(com);
		if (bcom) back(bcom->dist);
	}
	else if (com->cname==L)
	{
		turtle_lft_t* lcom = dynamic_cast<turtle_lft_t*>(com);
		if (lcom) turn_left(lcom->angl);
	}
	else if (com->cname==R)
	{
		turtle_rht_t* rcom = dynamic_cast<turtle_rht_t*>(com);
		if (rcom) turn_right(rcom->angl);
	}
	else if (com->cname==MF)
	{
		turtle_mfwd_t* mfcom = dynamic_cast<turtle_mfwd_t*>(com);
		if (mfcom) forward_move(mfcom->dist);
	}
	else if (com->cname==MB)
	{
		turtle_mbck_t* mbcom = dynamic_cast<turtle_mbck_t*>(com);
		if (mbcom) backward_move(mbcom->dist);
	}
	else if (com->cname==CLS)
	{
		turtle_cls_t* clscom = dynamic_cast<turtle_cls_t*>(com);
		if (clscom) clear();
	}
	else if (com->cname==RESET)
	{
		turtle_rst_t* rstcom = dynamic_cast<turtle_rst_t*>(com);
		if (rstcom) reset();
	}
	else if (com->cname==COL)
	{
		turtle_col_t* colcom = dynamic_cast<turtle_col_t*>(com);
		if (colcom) set_col(colcom->r, colcom->g, colcom->b);
	}
	else if (com->cname==BGCOL)
	{
		turtle_bgcol_t* bgcolcom = dynamic_cast<turtle_bgcol_t*>(com);
		if (bgcolcom) set_bgcol(bgcolcom->r, bgcolcom->g, bgcolcom->b);
	}
	else if (com->cname==SCALE)
	{
		turtle_scale_t* scalecom = dynamic_cast<turtle_scale_t*>(com);
		if (scalecom) scale(scalecom->s);
	}
	else if (com->cname==REPEAT)
	{
		turtle_rep_t *repcom = dynamic_cast<turtle_rep_t*>(com);

		if (repcom)
		{
			unsigned int times = repcom->times;
			turtle_com_list_t sublist = repcom->replist;
			repeat(times, sublist);
		}
	}
	else if (com->cname==PAUSE)
	{
		turtle_pause_t* bcom = dynamic_cast<turtle_pause_t*>(com);
		if (bcom) pause(bcom->tim);
	}
	else if(com->cname==BEGIN)
	{
		reset();
		set_col(1.0,1.0,1.0);
		glClearColor(bgcol.r, bgcol.g, bgcol.b, 0.0); 
		glClear(GL_COLOR_BUFFER_BIT);
			
	}
	else if ((com->cname==ENDREP) || (com->cname==END)) 
	{
		//These commands are place holders and used for program structure
		//But no execution is necessary - generate a NoOP
		;
	}
	else
	{
		std::cerr<<"Unknown Command: Ignoring"<<std::endl;
		exit(-1);
	}
}

