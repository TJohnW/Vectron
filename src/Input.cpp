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

void Input::drawCursor() {
    glColor3f( 0, 0, 0 );
    glBegin( GL_LINES );
    glVertex2f( Input::mouseX - 7, Input::mouseY );
    glVertex2f( Input::mouseX -1, Input::mouseY );
    glVertex2f( Input::mouseX + 1, Input::mouseY );
    glVertex2f( Input::mouseX + 7, Input::mouseY );
    glVertex2f( Input::mouseX, Input::mouseY + 7 );
    glVertex2f( Input::mouseX, Input::mouseY + 1 );
    glVertex2f( Input::mouseX, Input::mouseY -1 );
    glVertex2f( Input::mouseX, Input::mouseY - 7 );
    glEnd();
}

void Input::_scroll( GLFWwindow *window, double x, double y ) {

    int zoomedSpacing = Grid::spacing;

    int diffX = Screen::mapX(Input::mouseX) - (Screen::panX);
    int diffY = Screen::mapY(Input::mouseY) - (Screen::panY);

    if(zoomedSpacing + 2 > 50 && y > 0) {
        Grid::spacing = 50;
        return;
    } else if(zoomedSpacing - 2 < 5 && y < 0) {
        Grid::spacing = 5;
        return;
    }
    if(y > 0) {
        //Zoom in
        zoomedSpacing += 1;
    } else {
        zoomedSpacing -= 1;
    }

    Grid::spacing = zoomedSpacing;

    // Handles Max Zoom and Min zoom values as 50 and 5 for now


}

void Input::_mousePos( GLFWwindow *window, double x, double y ) {
    //Why dows GLFW use doubles if pixels are ints?
    //Because high-dpi monitors they scale to a screen size not pixel size
    Input::updateMouse( x - Screen::width/2 , Screen::height/2 - y );
}

void Input::_mouseButton( GLFWwindow *window, int button, int action, int mods ) {

}

void Input::_key( GLFWwindow *window, int key, int scancode, int action, int mods ) {
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, GL_TRUE );
    }
    if( action == GLFW_PRESS ) {
        keys[key] = true;
        if( key == GLFW_KEY_Z ) {
            cout << "Pressed the z!\n";
        }
    } else if( action == GLFW_RELEASE ) {
        keys[key] = false;
    }
    Input::_dispatch(window);
}

void Input::_dispatch(GLFWwindow *window) {

    if( Input::keys[GLFW_KEY_Z])
    {
        //Aamap::push(new Zone());
        //Zone *z = new Zone( Screen::mapX(Input::mouseX), Screen::mapY(Input::mouseY), 1 );
        //editedZone = z;
        //zones.push_front( z );
        //Zone::_create();
        Input::keys[GLFW_KEY_Z] = false;
    }
    else if ( Input::keys[GLFW_KEY_UP])
    {
        Screen::_up();
        Input::keys[GLFW_KEY_UP] = false;
    }
    else if ( Input::keys[GLFW_KEY_DOWN])
    {
        Screen::_down();
        Input::keys[GLFW_KEY_DOWN] = false;
    }
    else if ( Input::keys[GLFW_KEY_LEFT])
    {
        Screen::_left();
        Input::keys[GLFW_KEY_LEFT] = false;
    }
    else if ( Input::keys[GLFW_KEY_RIGHT])
    {
        Screen::_right();
        Input::keys[GLFW_KEY_RIGHT] = false;
    }
    else if ( Input::keys[GLFW_KEY_SPACE] && Input::keys[GLFW_KEY_LEFT_CONTROL])
    {
        Screen::_mouse(window);
        Input::keys[GLFW_KEY_UP] = false;
    }
    else if (Input::keys[GLFW_KEY_SPACE])
    {
        Screen::_center();
        Input::keys[GLFW_KEY_UP] = false;
    }
}

