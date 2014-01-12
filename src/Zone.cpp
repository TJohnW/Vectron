/*
********************************************************************************
Vectron - map editor for Armagetron Advanced.
Copyright (C) 2014 	Tristan Whitcher 	(tristan.whitcher@gmail.com)
				   	David Dubois 		(ddubois@jotunstudios.com)
********************************************************************************

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

/* These coordinates now better represent the actual location of the zone in the
    XML which is vital. Now on zoom the zones will accomidate for the change in
    Screen spacing but still retain their value as the same zone. After so much
    zoom, we need to redraw the Screen with less pxspacing but keep the zone the
    same somehow Not sure how yet though.
*/

Zone::Zone( int newX, int newY, float newRadius ) {
    x = newX;
    y = newY;
    radius = newRadius;
    cout << "Adding a zone at (" << x << ", " << y << ")\n";
 }


/*
    Zones need to be drawn according to a set coordiate that can be changed with
    the current Screen scale.
*/

void Zone::draw() {
    glColor3f( 1.0, 0.0, 0.0 );
    glBegin( GL_LINE_LOOP );
    /*for( float i = 0; i < TOOPI; i+= 0.1f ) {
        glVertex2f( cos( i ) * radius * Screen::spacing + (x + Screen::panX) * 
            Screen::spacing, sin( i ) * radius * Screen::spacing + 
            (y + Screen::panY) * Screen::spacing);
    }*/
    glEnd( );
}

void Zone::update() {
    int xDist = Input::mouseX - x;
    int yDist = Input::mouseY - y;
    radius = sqrt( xDist * xDist + yDist* yDist );
    if( Input::mouse0 ) {
        ZoneFinishedFunc();
    }
}
