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

#ifndef SCREEN_H
#define SCREEN_H

#include "stdafx.h"

#include "Input.h"
#include "Aamap.h"
#include "Mouse.h"

class Screen {

public:

    GLFWwindow *window;

    Screen( int width, int height );

    void draw();

    /* Tristan let this be */
    void update();

    static int mapX( double mouseX ); //returns the actual location of the x coordinate of the mouse
    static int mapY( double mouseY ); // ^^ but y

    static void _up(); //panning
    static void _down(); //panning
    static void _right(); //panning
    static void _left(); //panning

    static void _mouse( GLFWwindow *window ); //panning
    static void _center(); //panning pan map coordinates back to center


    static void _framebuffer( GLFWwindow *window, int width, int height );
    static void _size( GLFWwindow* window, int width, int height );

    void draw( int width, int height );
    static void _scroll( GLFWwindow *window, double x, double y );

private:
    Aamap *map;
    Mouse mouse;
};

#endif