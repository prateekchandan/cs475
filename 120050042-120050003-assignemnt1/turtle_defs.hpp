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


#ifndef _TURTLE_DEFS_HPP_
#define _TURTLE_DEFS_HPP_

#include <vector>

//Turtle Command Codes
enum turtle_com_name_t
{
	BEGIN,
	END,
	F,
	B,
	L,
	R,
	CLS,
	RESET,
	REPEAT,
	ENDREP,
	MF,
	MB,
	COL,
	BGCOL,
	SCALE,
	PAUSE
};

//Generic turtle command type
struct turtle_com_t
{ 
	turtle_com_name_t cname;
	turtle_com_t() {;}
	virtual ~turtle_com_t() {;}

	turtle_com_t& operator=(turtle_com_t& _com)
	{cname=_com.cname; return *this;}
};

//A type for list of turtle commands
typedef std::vector<turtle_com_t*> turtle_com_list_t;

//Specific turtle command types 
struct turtle_beg_t : public turtle_com_t 
{
	turtle_beg_t() {cname=BEGIN;}
};
struct turtle_end_t : turtle_com_t 
{
	turtle_end_t() {cname=END;}
};
struct turtle_fwd_t : public turtle_com_t 
{ 
	double dist; 
	turtle_fwd_t() {cname=F; dist=0.0;}

	turtle_fwd_t& operator=(turtle_fwd_t& _com)
	{cname=_com.cname; dist=_com.dist; return *this;}
};
struct turtle_bck_t : public turtle_com_t 
{ 
	double dist; 
	turtle_bck_t() {cname=B; dist=0.0;}

	turtle_bck_t& operator=(turtle_bck_t& _com)
	{cname=_com.cname; dist=_com.dist; return *this;}
};
struct turtle_lft_t : public turtle_com_t 
{ 
	double angl; 
	turtle_lft_t() {cname=L; angl=0.0;}

	turtle_lft_t& operator=(turtle_lft_t& _com)
	{cname=_com.cname; angl=_com.angl; return *this;}
};
struct turtle_rht_t : public turtle_com_t 
{ 
	double angl; 
	turtle_rht_t() {cname=R; angl=0.0;}

	turtle_rht_t& operator=(turtle_rht_t& _com)
	{cname=_com.cname; angl=_com.angl; return *this;}
};
struct turtle_cls_t : public turtle_com_t 
{
	turtle_cls_t() {cname=CLS;}
};
struct turtle_rst_t : public turtle_com_t 
{
	turtle_rst_t() {cname=RESET;}
};
struct turtle_rep_t : public turtle_com_t 
{ 
	unsigned int times; 
	turtle_com_list_t replist;

	turtle_rep_t() {cname=REPEAT; times=0; replist.empty();}


	turtle_rep_t& operator=(turtle_rep_t& _com)
	{cname=_com.cname; times=_com.times; replist = _com.replist; return *this;}
};
//
struct turtle_pause_t : public turtle_com_t 
{ 
	double tim; 
	turtle_pause_t() {cname=PAUSE; tim=0.0;}

	turtle_pause_t& operator=(turtle_pause_t& _com)
	{cname=_com.cname; tim=_com.tim; return *this;}
};

struct turtle_erep_t : turtle_com_t 
{ 
	turtle_erep_t() {cname=ENDREP;}
};
struct turtle_mfwd_t : public turtle_com_t 
{ 
	double dist;
	turtle_mfwd_t() {cname=MF; dist=0.0;}

	turtle_mfwd_t& operator=(turtle_mfwd_t& _com)
	{cname=_com.cname; dist=_com.dist; return *this;}
};
struct turtle_mbck_t : public turtle_com_t 
{ 
	double dist;
	turtle_mbck_t() {cname=MB; dist=0.0;} 

	turtle_mbck_t& operator=(turtle_mbck_t& _com)
	{cname=_com.cname; dist=_com.dist; return *this;}
};
struct turtle_col_t : public turtle_com_t 
{ 
	double r,g,b;
	turtle_col_t() {cname=COL; r=0.0;g=0.0;b=0.0;} 

	turtle_col_t& operator=(turtle_col_t& _com)
	{cname=_com.cname; r=_com.r; g=_com.g; b=_com.b; return *this;}
};
struct turtle_bgcol_t : public turtle_com_t 
{ 
	double r,g,b;
	turtle_bgcol_t() {cname=BGCOL; r=0.0;g=0.0;b=0.0;} 

	turtle_bgcol_t& operator=(turtle_bgcol_t& _com)
	{cname=_com.cname; r=_com.r; g=_com.g; b=_com.b; return *this;}
};
struct turtle_scale_t : public turtle_com_t 
{ 
	double s;
	turtle_scale_t() {cname=SCALE; s=1.0;} 

	turtle_scale_t& operator=(turtle_scale_t& _com)
	{cname=_com.cname; s=_com.s; return *this;}
};


//Helper Classes
struct color_t
{  double r,g,b; };

struct vertex_t
{ 
	double x,y;
};

#endif
