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


#ifndef _TURTLE_HPP_
#define _TURTLE_HPP_

#include "turtle_defs.hpp"
#include "gl_framework.hpp"

/***************
 The Turtle class

  The turtle has:
  a) pos - Position. Note X and Y are bounded between -1 and 1.
  b) dir - Orientation angle in degrees. Zero degrees is due East. 
     It is bounded from 0.0 to 360.0.

  Command syntax should be
  1. Forward (F x)
  2. Back (B x)
  3. Turn Left (L a)
  4. Turn Right (R a)
  5. Move forward without drawing (MF x)
  6. Move backward without drawing (MB x)
  7. Repeat (REPEAT r) : Repeat the next set of commands r times. 
     Scope bounded by  a corresponding ENDREP
  8. Clear (CLS) : Clear the screen
  9. Reset (RESET): Reset the turtle position and orientation
  10. Begin/End (BEGIN/END) : Start/End a turtle program
  11. Color (COL(r, g, b)) : Current pen color
  12. Background color (BGCOL(r, g, b)) : Current background color
  13. Scale (SCALE s) : Scale the current canvas by s

****************/

class turtle_t
{
private:
  
  vertex_t pos;    // Current position
  double dir;      // Current orientation in degrees ccw from east
  color_t col;     // Current color
  color_t bgcol;

public:

	GLFWwindow* window;
  //Default Constructor
  turtle_t() 
  {
    //Reset turtle position and orientation
    reset(); 
    //Set the current draw color
    col.r = 1.0; col.g = 1.0; col.b = 1.0;
    bgcol.r = 0.0; bgcol.g=0.0; bgcol.b=0.0;
  }

  //Copy Constructor
  turtle_t(const turtle_t &turt)
  {
    pos.x = turt.pos.x; pos.y = turt.pos.y;
    dir = turt.dir;
    col.r = turt.col.r; col.g = turt.col.g; col.b = turt.col.b;
  }

  //Default Destructor
  ~turtle_t() {;}

  //Restores initial state
  void reset(void);

  //Clears the screen
  void clear(void);

  //Set turtle position
  void set_pos(const vertex_t _pos);
  void set_pos(const double _x, const double _y);

  //Set turtle orientation
  void set_dir(const double _dir);

  //Set current drawing color
  void set_col(const color_t _col);
  void set_col(const double _r, const double _g, const double _b);

  //Set current background color
  void set_bgcol(const double _r, const double _g, const double _b);

  //Scale the drawing canvas by
  void scale(const double _s);

  //Turn left - angle is in degrees
  void turn_left(const double _angle);

  //Turn right - angle is in degrees
  void turn_right(const double _angle);

  //Move forward and draw
  void forward(const double _dist);  

  //Move back and draw
  void back(const double _dist);   

  //Move forward and do not draw
  void forward_move(const double _dist);

  //Move back and do not draw
  void backward_move(const double _dist);

  //Repeat the execution of the commands given
  //in _replist _n times.
  void repeat(const unsigned int &_n, const turtle_com_list_t &_replist);

  //Executes the command com
  void exec(turtle_com_t *com);
  
  //Function to pause
  void pause(const double _tim);
}; 

#endif
