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

#include "Wall.h"

Wall::Wall() {
    length = 0;
    addPoint( Input::mouseX, Input::mouseY );
}

void Wall::update() {
    editedPoint->x = Input::mouseX;
    editedPoint->y = Input::mouseY;
}

void Wall::draw() {
    glColor3f( 1, 1, 1 );
    glBegin( GL_LINES );
    WallPoint *curPoint = front;
    while( curPoint != editedPoint ) {
        glVertex2f( curPoint->x, curPoint->y );
        glVertex2f( curPoint->next->x, curPoint->next->y );
        curPoint = curPoint->next;
    }
    glEnd();
}

void Wall::addPoint( int x, int y ) {
    //We know the front and the back
    //Add to the back
    //editedPoint is ALWAYS the last point, until Wall::editing is false
    switch( length ) {
    case 0:
        front = new WallPoint( x, y );
        front->next = editedPoint;
        back = editedPoint;
        length++;
        break;
    case 1:
        WallPoint *p = new WallPoint( x, y );
        front->next = p;

    }
}