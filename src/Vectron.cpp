/*
********************************************************************************
Vectron - map editor for Armagetron Advanced.
Copyright (C) 2014  Tristan Whitcher    (tristan.whitcher@gmail.com)
                    David Dubois        (ddubois@jotunstudios.com)
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

#include "stdafx.h"

#include "AamapObject.h"
#include "Grid.h"
#include "Input.h"
#include "Screen.h"
#include "Wall.h"
#include "Zone.h"

using namespace std;

void error_callback( int error, const char *description );
void key_callback( GLFWwindow *window, int key, int scancode, int action, 
    int mods );

void addZone();
void drawCursor();
void update();
void draw();

forward_list<Zone*> zones;

Grid *g;
Screen *s;
Zone *editedZone;
Wall *editedWall;

void update() {
    if( editedZone != NULL ) {
        editedZone->update( );
    } else if( editedWall != NULL ) {
        editedWall->update();
    }
    if( Input::keys[GLFW_KEY_Z] ) {
        Zone *z = new Zone( Input::mouseX, Input::mouseY, 30 );
        editedZone = z;
        zones.push_front( z );
        Input::keys[GLFW_KEY_Z] = false;
    }
}

void draw() {
    glClear( GL_COLOR_BUFFER_BIT );

    g->draw( Screen::pxWidth, Screen::pxHeight );

    /* Instead of looping through every type here, lets make a base object
    class that every type extends upon and overrides / has its own draw()
    function */
    /* This also simplifies the history because it allows for simple loop of
    objects and then each object -> draw(). then to remove one just pop
    it off. */
    for( Zone *z : zones ) {
        z->draw();
    }
    Zone myZone = Zone(0, 0, 10);
    myZone.draw();
    Input::drawCursor();


    glfwSwapBuffers( s->window );
}

int main() {

    s = new Screen(640, 480);

    glfwSetErrorCallback(error_callback);

    g = new Grid();


    glfwSetKeyCallback(s->window, Input::_key);
    glfwSetCursorPosCallback( s->window, Input::_mousePos );
    glfwSetMouseButtonCallback( s->window, Input::_mouseButton );
    glfwSetScrollCallback( s->window, Input::_scroll );

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0f);


    while( !glfwWindowShouldClose( s->window ) ) {
        update();
        draw();
       
        glfwPollEvents();
    }

    glfwDestroyWindow( s->window );
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/* Where should we put error handling? */

void error_callback( int error, const char *description ) {
    fputs( description, stderr );
}

