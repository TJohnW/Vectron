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
#include "Screen.h"
#include "Input.h"
#include "Screen.h"
#include "Wall.h"
#include "Zone.h"

using namespace std;

void error_callback( int error, const char *description );

Screen *s;

int main() {
    s = new Screen(640, 480);

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(s->window, Input::_key);
    glfwSetCursorPosCallback( s->window, Input::_mousePos );
    glfwSetMouseButtonCallback( s->window, Input::_mouseButton );
    glfwSetScrollCallback( s->window, Screen::_scroll );

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    while( !glfwWindowShouldClose( s->window ) ) {
        glClear( GL_COLOR_BUFFER_BIT );

        s->draw();

        glfwSwapBuffers( s->window );
        glfwPollEvents();
    }

    glfwDestroyWindow( s->window );
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/* Where should we put error handling? */

/* Right here is fine */

void error_callback( int error, const char *description ) {
    fputs( description, stderr );
}

