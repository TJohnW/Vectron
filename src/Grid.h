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
#ifndef GRID_H
#define GRID_H

#include "stdafx.h"

#include "Input.h"
#include "Screen.h"

class Grid {

public:
    void draw(int width, int height);
    static int spacing, panX, panY;
    static void _scroll( GLFWwindow *window, double x, double y );
    static int mapX( double pos );
    static int mapY( double pos );

    //void drawCircle(float);
};

#endif