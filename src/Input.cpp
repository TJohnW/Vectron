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

#include "Input.h"
#include "Screen.h"
#include "Grid.h"

bool Input::keys[349];
double Input::mouseX = 0;
double Input::mouseY = 0;
double Input::mouseDeltaX = 0;
double Input::mouseDeltaY = 0;

void Input::clear( ) {
    for( int i = 0; i < 349; i++ ) {
        keys[i] = false;
    }
}

/*
	Updated to handle snapping to grid. This applies to zone adding because the software
	mouse is set to the snapped location.
*/

void Input::updateMouse( double newMouseX, double newMouseY ) {
    mouseDeltaX = newMouseX - mouseX;
    mouseDeltaY = newMouseY - mouseY;
    mouseX = round(newMouseX / Grid::spacing) * Grid::spacing;
    mouseY = round(newMouseY / Grid::spacing) * Grid::spacing;
}

void Input::_scroll( GLFWwindow *window, double x, double y ) {

    double zoomedSpacing;
    if(y > 0) {
        zoomedSpacing = Grid::spacing += 2;
    } else {
        zoomedSpacing = Grid::spacing -= 2;
    }

    // Handles Max Zoom and Min zoom values as 50 and 5 for now.
    if(zoomedSpacing > 50) {
        Grid::spacing = 50;
    } else if(zoomedSpacing < 5) {
        Grid::spacing = 5;
    } else {
        Grid::spacing = zoomedSpacing;
    }
    
}

void Input::_mousePos( GLFWwindow *window, double x, double y ) {
    //Why dows GLFW use doubles if pixels are ints?
    Input::updateMouse( x, Screen::height - y );
}

void Input::_mouseButton( GLFWwindow *window, int button, int action, int mods ) {

}

