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

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <fstream>
#include <iostream>
#include <cstdlib>

#include "turtle_defs.hpp"

//The parser class
class parser_t
{
public:

  //Default Constructor
  parser_t() {;}

  //Default Destructor
  ~parser_t() {;}
  
  //Parse the tokens from the input stream
  std::string parse_token(std::istream &_inp, turtle_com_list_t &list);

  //Parse the input stream till it ends
  void parse(std::istream &_inp, turtle_com_list_t &list);
  

};

#endif
