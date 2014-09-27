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


#include "render_drawing.hpp"


void triline(turtle_t &turt, double length)
{
   if (length <= 0.01)
   {
      turt.forward(length);
   }
   else
   {
     double newlength = length/3.0;
     triline(turt, newlength);
     turt.turn_left(60);
     triline(turt, newlength);
     turt.turn_right(120);
     triline(turt, newlength);
     turt.turn_left(60);
     triline(turt, newlength);
   }
}

//Drawing a Koch Snowflake
void koch(turtle_t &turt, double x)
{
   turt.reset();
   turt.clear();
   turt.set_pos(-0.3, 0.5);
   turt.turn_right(30);

   for (int i = 0; i<3; i++)
     {
       triline(turt, x);
       turt.turn_right(120);
     }
}

void triangle(turtle_t &turt,int n,double l){
	if(n==0)
		return;
	 triangle(turt,n-1,l/2);
	 turt.forward(l/2);
	 triangle(turt,n-1,l/2);
	 turt.forward(l/2);
	 turt.turn_right(120);
	 turt.forward(l);
	 turt.turn_right(120);
	 turt.forward(l/2);
	 turt.turn_right(120);
	 triangle(turt,n-1,l/2);
	 turt.turn_left(120);
	 turt.forward(l/2);
	 turt.turn_right(120);
	 
}
void render_drawing(turtle_t &turt)
{
  koch(turt, 1.0);
  turt.set_col(0.99,95.0/255.0,0.0);
  turt.reset();
	turt.clear();
	turt.set_pos(-0.7, -0.5);
	turt.turn_left(60);
	triangle(turt,9,1.4);
}
