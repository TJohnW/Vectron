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
    editedPoint = new WallPoint( Input::mouseX, Input::mouseY );
    addPoint( Input::mouseX, Input::mouseY );
}

void Wall::update() {
    editedPoint->x = Input::mouseX;
    editedPoint->y = Input::mouseY;
    if( Input::mouse0 ) {
        //make editedPoint a real point
        addPoint( editedPoint->x, editedPoint->y );
        //prevent bugs from holding down the mouse over multiple frames
        Input::mouse0 = false;
    } else if( Input::mouse1 ) {
        //make EditedPoint a real point
        addPoint( editedPoint->x, editedPoint->y );
        //Make editedPoint change no longer
        WallFinishedFunc();
    }
}

void Wall::draw() {
    glColor3f( 0, 0, 0 );
    glBegin( GL_LINES );
    WallPoint *curPoint = front;
    while( curPoint != editedPoint->next ) {
        glVertex2f( curPoint->x * ScreenVars::spacing, 
            curPoint->y * ScreenVars::spacing );
        glVertex2f( curPoint->next->x * ScreenVars::spacing, 
            curPoint->next->y * ScreenVars::spacing );
        curPoint = curPoint->next;
    }
    glColor3f( 0.8f, 0.8f, 0.8f );
    glVertex2f( editedPoint->x, editedPoint->y );
    glVertex2f( editedPoint->next->x, editedPoint->next->y );
    glEnd();
}

void Wall::addPoint( int x, int y ) {
    //We know the front and the back
    //Add to the back
    //editedPoint is ALWAYS the last point, until Wall::editing is false
    WallPoint *p;
    switch( length ) {
    case 0:
        front = new WallPoint( x, y );
        front->next = editedPoint;
        editedPoint->next = front;
        length++;
        break;
    case 1:
        p = new WallPoint( x, y );
        front->next = p;
        p->next = editedPoint;
        editedPoint->next = p;
        length++;
        break;
    default:
        p = new WallPoint( x, y );
        p->next = editedPoint;
        editedPoint->next->next = p;
        editedPoint->next = p;
        length++;
    }
}