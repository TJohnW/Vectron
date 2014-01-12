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
#include "Mouse.h"

void Mouse::draw() {
    glColor3f( 0, 0, 0 );
    glBegin( GL_LINES );
    glVertex2f( xPos - 7, yPos );
    glVertex2f( xPos - 1, yPos );
    glVertex2f( xPos + 1, yPos );
    glVertex2f( xPos + 7, yPos );
    glVertex2f( xPos, yPos + 7 );
    glVertex2f( xPos, yPos + 1 );
    glVertex2f( xPos, yPos - 1 );
    glVertex2f( xPos, yPos - 7 );
    glEnd( );
}

void Mouse::update() {
    xPos = Input::mouseX;
    yPos = Input::mouseY;
}