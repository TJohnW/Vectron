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

#include "Grid.h"
#include "Input.h"
#include "Screen.h"
#include "Zone.h"

using namespace std;

void error_callback( int error, const char *description );
void key_callback( GLFWwindow *window, int key, int scancode, int action, 
    int mods );

void addZone();
void drawCursor();


forward_list<Zone*> zones;

int main(void) {

    Screen s = Screen(640, 480);

    glfwSetErrorCallback(error_callback);

    Grid *g = new Grid();


    glfwSetKeyCallback(s.window, Input::_key);

    glfwSetCursorPosCallback( s.window, Input::_mousePos );
    glfwSetMouseButtonCallback( s.window, Input::_mouseButton );
    glfwSetScrollCallback( s.window, Input::_scroll );

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    while (!glfwWindowShouldClose(s.window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        g->draw( Screen::pxWidth, Screen::pxHeight );

        /* Instead of looping through every type here, lets make a base object class
           that every type extends upon and overrides / has its own draw() function */
        /* This also simplifies the history because it allows for simple loop of objects
            and then each object -> draw(). then to remove one just pop it off. */
        for( Zone *z : zones ) {
            z->draw();
        }
                
        Input::drawCursor();

        glfwSwapBuffers(s.window);
        glfwPollEvents();
    }

    glfwDestroyWindow(s.window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/* Where should we put error handling? */

void error_callback( int error, const char *description ) {
    fputs( description, stderr );
}

