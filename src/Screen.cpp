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

#include "Screen.h"

Screen::Screen(int newWidth, int newHeight) {

	//glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit( EXIT_FAILURE );

    ScreenVars::width = newWidth;
    ScreenVars::height = newHeight;

    window = glfwCreateWindow( ScreenVars::width, ScreenVars::height, 
        "Vectron Alpha 0.0.5", NULL, NULL );
    //ScreenVars::width -= 100;

    if (!window) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, _framebuffer);
    glfwSetWindowSizeCallback(window, Screen::_size);

    glewInit();

    /* Initial Before callback */

    glfwGetFramebufferSize( window, &ScreenVars::pxWidth, &ScreenVars::pxHeight );
    glViewport( 0, 0, ScreenVars::pxWidth, ScreenVars::pxHeight );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -ScreenVars::width / 2, ScreenVars::width / 2, -ScreenVars::height / 2, ScreenVars::height / 2, 0, 1 );
    Aamap::toolActive = false;
    map = new Aamap();
}

void Screen::draw() {
    glColor3f( 0.84f, 0.84f, 0.92f );
    glBegin( GL_LINES );

    for( int i = 0; i < ScreenVars::width / 2; i += ScreenVars::spacing ) {
        glVertex2f( i, -ScreenVars::height / 2 );
        glVertex2f( i, ScreenVars::height / 2 );

        glVertex2f( -i, -ScreenVars::height / 2 );
        glVertex2f( -i, ScreenVars::height / 2 );

        glVertex2f( -ScreenVars::width / 2, i );
        glVertex2f( ScreenVars::width / 2, i );

        glVertex2f( -ScreenVars::width / 2, -i );
        glVertex2f( ScreenVars::width / 2, -i );
    }

    glEnd( );
	map->render();
    mouse.draw();
}

void Screen::update( ) {
    if( Input::keys[GLFW_KEY_UP] ) {
        _up( );
        //Input::keys[GLFW_KEY_UP] = false;
    } else if( Input::keys[GLFW_KEY_DOWN] ) {
        _down( );
        //Input::keys[GLFW_KEY_DOWN] = false;
    } else if( Input::keys[GLFW_KEY_LEFT] ) {
        _left( );
        //Input::keys[GLFW_KEY_LEFT] = false;
    } else if( Input::keys[GLFW_KEY_RIGHT] ) {
        _right( );
        //Input::keys[GLFW_KEY_RIGHT] = false;
    } else if( Input::keys[GLFW_KEY_SPACE] &&
        Input::keys[GLFW_KEY_LEFT_CONTROL] ) {
        _center( );
        Input::keys[GLFW_KEY_SPACE] = false;
    } else if( Input::keys[GLFW_KEY_SPACE] ) {
        _mouse( window );
        Input::keys[GLFW_KEY_SPACE] = false;
    }

    map->update();
    mouse.update();
}

void Screen::_up() {
    ScreenVars::panY -= 1;
}

void Screen::_down() {
    ScreenVars::panY += 1;
}

void Screen::_right() {
    ScreenVars::panX -= 1;
}

void Screen::_left() {
    ScreenVars::panX += 1;
}

/*
 *  Pan the center of the camera to the mouse and move the mouse to the center
 *  Called on LEFTCTRL + SPACE
 */
void Screen::_mouse(GLFWwindow* window) {
    ScreenVars::panX = -1 * mapX( Input::mouseX );
    ScreenVars::panY = -1 * mapY( Input::mouseY );
    Input::updateMouse(0, 0);
    glfwSetCursorPos( window, ScreenVars::width / 2, ScreenVars::height / 2 ); // Center mouse after panning to it
}

/*
 *  Pan the center of the map to be in the center of the screen, leave their mouse alone.
 *  Called on SPACE
 */
void Screen::_center() {
    ScreenVars::panX = 0;
    ScreenVars::panY = 0;
}

void Screen::_size(GLFWwindow* window, int newWidth, int newHeight) {
    ScreenVars::width = newWidth;
    ScreenVars::height = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -ScreenVars::width / 2, ScreenVars::width / 2, -ScreenVars::height / 2, ScreenVars::height / 2, 0, 1 );
    glViewport( 0, 0, ScreenVars::pxWidth, ScreenVars::pxHeight );
}


void Screen::_framebuffer(GLFWwindow* window, int newPxWidth, int newPxHeight){
    ScreenVars::pxWidth = newPxWidth;
    ScreenVars::pxHeight = newPxHeight;
    glViewport( 0, 0, ScreenVars::pxWidth, ScreenVars::pxHeight );
    glOrtho( -ScreenVars::width / 2, ScreenVars::width / 2, -ScreenVars::height / 2, ScreenVars::height / 2, 0, 1 );
}

int Screen::mapX( double mouseX ) {
    return mouseX / ScreenVars::spacing - ScreenVars::panX;
}

int Screen::mapY( double mouseY ) {
    return mouseY / ScreenVars::spacing - ScreenVars::panY;
}

void Screen::_scroll( GLFWwindow *window, double x, double y ) {
    int zoomedSpacing = ScreenVars::spacing;

    int diffX = mapX( Input::mouseX ) - ScreenVars::panX;
    int diffY = mapY( Input::mouseY ) - ScreenVars::panY;
    
    if( y > 0  && ScreenVars::spacing < 50) {
        //Zoom in
        zoomedSpacing += 1;
    } else if(y < 0 && ScreenVars::spacing > 5) {
        zoomedSpacing -= 1;
    }

    ScreenVars::spacing = zoomedSpacing;

    // Handles Max Zoom and Min zoom values as 50 and 5 for now
}