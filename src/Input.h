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

#ifndef INPUT_H
#define INPUT_H
#include "stdafx.h"
/*\brief A simple state machine to hold the current input buttons in a place
easily accessable from anywhere inside the program*/
class Input {
public:
    /*!\brief Clears the input buffers to prepare for writing*/
    static void clear( );

    static void drawCursor();

    /*!\brief Sets the mouse position and change in mouse position

    \param [in] newMouseX The current x-position of the mouse, in screen
    coordinates
    \param [in] newMouseY The current y-position of the mouse, in screen
    coordinates*/
    static void updateMouse( double newMouseX, double newMouseY );

    /*!\brief An array of boolean flags, one for each key defined by GLFW

    See http://www.glfw.org/docs/3.0/group__keys.html for a complete listing*/
    static bool keys[349];

    /*\brief Variables for the x-position, y-position, x change, and y change
    of the mouse*/
    static double mouseX, mouseY, mouseDeltaX, mouseDeltaY;

    /* Moving callbacks for mouse handling to the input class */

    static void _scroll( GLFWwindow *window, double x, double y );
    static void _mousePos( GLFWwindow *window, double x, double y );
    static void _mouseButton( GLFWwindow *window, int button, int action, int mods );
    
};

#endif