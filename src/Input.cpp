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

void Input::updateMouse( double newMouseX, double newMouseY ) {
    cout << "Updating mouse from (" << mouseX << ", " << mouseY << ") to (" 
        << newMouseX << ", " << newMouseY << ")\n";
    mouseDeltaX = newMouseX - mouseX;
    mouseDeltaY = newMouseY - mouseY;
    mouseX = newMouseX;
    mouseY = newMouseY;
}