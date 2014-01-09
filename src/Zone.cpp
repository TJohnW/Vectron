/*
**************************************************************************
Vectron - map editor for Armagetron Advanced.
Copyright (C) 2014 	Tristan Whitcher 	(tristan.whitcher@gmail.com)
				   	David Dubois 		(ddubois@jotunstudios.com)
**************************************************************************

This file is part of Vectron.

Vectron is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Vectron is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Vectron.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Zone.h"

Zone::Zone( int newX, int newY, float newRadius ) {
    x = newX;
    y = newX;
    radius = newRadius;
}

void Zone::draw() {
    glColor3f( 1.0, 0.0, 0.0 );
    glBegin( GL_LINE_LOOP );
    for( float i = 0; i < TOOPI; i+= 0.1f ) {
        glVertex2f( cos( i ) * radius + x, sin( i ) * radius + y );
    }
    glEnd( );
}
