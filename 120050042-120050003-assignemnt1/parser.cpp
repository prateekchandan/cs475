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

#include "parser.hpp"

std::string parser_t::parse_token(std::istream &_inp, turtle_com_list_t &list)
{
	std::string token;
	_inp>>token;

	if (token == "F")
	{
		std::cerr<<"Forward: ";
		turtle_fwd_t* com = new turtle_fwd_t;
		_inp>>com->dist;
		std::cerr<<com->dist<<std::endl;
		list.push_back(com);
	}
	else if (token == "B")
	{
		std::cerr<<"Back: ";
		turtle_bck_t* com = new turtle_bck_t;
		_inp>>com->dist;
		std::cerr<<com->dist<<std::endl;
		list.push_back(com);
	}
	else if (token == "L")
	{
		std::cerr<<"Left: ";
		turtle_lft_t* com = new turtle_lft_t;
		_inp>>com->angl;
		std::cerr<<com->angl<<std::endl;
		list.push_back(com);
	}
	else if (token == "R")
	{
		std::cerr<<"Right: ";
		turtle_rht_t* com = new turtle_rht_t;
		_inp>>com->angl;
		std::cerr<<com->angl<<std::endl;
		list.push_back(com);
	}
	else if (token == "MF")
	{
		std::cerr<<"Move Forward: ";
		turtle_mfwd_t* com = new turtle_mfwd_t;
		_inp>>com->dist;
		std::cerr<<com->dist<<std::endl;
		list.push_back(com);
	}
	else if (token == "MB")
	{
		std::cerr<<"Move Backward: ";
		turtle_mbck_t* com = new turtle_mbck_t;
		_inp>>com->dist;
		std::cerr<<com->dist<<std::endl;
		list.push_back(com);
	}
	else if (token == "RESET")
	{
		std::cerr<<"Reset Turtle"<<std::endl;
		turtle_rst_t* com = new turtle_rst_t;
		list.push_back(com);
	}
	else if (token == "CLS")
	{
		std::cerr<<"Clear Screen"<<std::endl;
		turtle_cls_t* com = new turtle_cls_t;
		list.push_back(com);
	}
	else if (token == "PAUSE")
	{
		std::cerr<<"PAUSE: ";
		turtle_pause_t* com = new turtle_pause_t;
		_inp>>com->tim;
		std::cerr<<com->tim<<std::endl;
		list.push_back(com);
	}
	else if (token == "REPEAT")
	{
		std::cerr<<"Repeat ";
		turtle_rep_t* com = new turtle_rep_t;
		_inp>>com->times;
		std::cerr<<com->times<<" times"<<std::endl;
		list.push_back(com);

		while (token != "ENDREP")
		{
			token = parse_token(_inp, com->replist);
		}
		token="";
	}
	else if (token == "ENDREP")
	{
		std::cerr<<"End Repeat "<<std::endl;
		turtle_erep_t* com = new turtle_erep_t;
		list.push_back(com);  
	}
	else if (token == "COL")
	{
		std::cerr<<"Color: ";
		turtle_col_t* com = new turtle_col_t;
		_inp>>com->r>>com->g>>com->b;
		std::cerr<<"("<<com->r<<", "<<com->g<<", "<<com->b<<")"<<std::endl;
		list.push_back(com);
	}
	else if (token == "BGCOL")
	{
		std::cerr<<"Background Color: ";
		turtle_bgcol_t* com = new turtle_bgcol_t;
		_inp>>com->r>>com->g>>com->b;
		std::cerr<<"("<<com->r<<", "<<com->g<<", "<<com->b<<")"<<std::endl;
		list.push_back(com);
	}
	else if (token == "SCALE")
	{
		std::cerr<<"Scale: ";
		turtle_scale_t* com = new turtle_scale_t;
		_inp>>com->s;
		std::cerr<<com->s<<std::endl;
		list.push_back(com);
	}
	else if (token == "END")
	{
		std::cerr<<"End"<<std::endl;
		turtle_end_t* com = new turtle_end_t;
		list.push_back(com);
		_inp>>token;
		if (!_inp.eof()) 
		{
			std::cerr<<"Error: Reading beyond END tag."<<std::endl;
			exit(-1);
		}
	}

	return token;
}

void parser_t::parse(std::istream &_inp, turtle_com_list_t &list)
{
	list.empty();

	if (_inp == NULL)
	{
		std::cerr<<"Error: Unable to read input stream."<<std::endl;
		exit(-1);
	}

	std::string token;
	_inp>>token;
	if (token != "BEGIN")
	{
		std::cerr<<"Error: Missing BEGIN."<<std::endl;
		exit(-1);
	}   
	else
	{
		std::cerr<<"Begin"<<std::endl;
		turtle_beg_t* com = new turtle_beg_t;
		list.push_back(com);
	}

	while (!_inp.eof())
	{
		token=parse_token(_inp, list); 
	}

	if (token != "END")
	{
		std::cerr<<"Error: No END tag."<<std::endl;
		exit(-1);
	}


}
