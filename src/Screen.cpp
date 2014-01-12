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

int Screen::height = 0;
int Screen::width = 0;

int Screen::pxHeight = 0;
int Screen::pxWidth = 0;

int Screen::panX = 0;
int Screen::panY = 0;

Screen::Screen(int newWidth, int newHeight) {

	//glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit( EXIT_FAILURE );

    width = newWidth;
    height = newHeight;

    window = glfwCreateWindow(width, height, "Vectron Alpha 0.0.2", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, _framebuffer);
    glfwSetWindowSizeCallback(window, Screen::_size);

    /* Initial Before callback */

    glfwGetFramebufferSize(window, &pxWidth, &pxHeight);
    glViewport(0, 0, pxWidth, pxHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, 0, 1);
}

void Screen::draw() {
    grid.draw( width, height );
	map.render();
    mouse.draw();
}

void Screen::update( ) {
    if( Input::keys[GLFW_KEY_UP] ) {
        _up( );
        Input::keys[GLFW_KEY_UP] = false;
    } else if( Input::keys[GLFW_KEY_DOWN] ) {
        _down( );
        Input::keys[GLFW_KEY_DOWN] = false;
    } else if( Input::keys[GLFW_KEY_LEFT] ) {
        _left( );
        Input::keys[GLFW_KEY_LEFT] = false;
    } else if( Input::keys[GLFW_KEY_RIGHT] ) {
        _right( );
        Input::keys[GLFW_KEY_RIGHT] = false;
    } else if( Input::keys[GLFW_KEY_SPACE] &&
        Input::keys[GLFW_KEY_LEFT_CONTROL] ) {
        _mouse( window );
        Input::keys[GLFW_KEY_SPACE] = false;
    } else if( Input::keys[GLFW_KEY_SPACE] ) {
        _center( );
        Input::keys[GLFW_KEY_SPACE] = false;
    }

    map.update();
    mouse.update();
}

void Screen::_up() {
    panY -= 1;
}

void Screen::_down() {
    panY += 1;
}

void Screen::_right() {
    panX -= 1;
}

void Screen::_left() {
    panX += 1;
}

/*
 *  Pan the center of the camera to the mouse and move the mouse to the center
 *  Called on LEFTCTRL + SPACE
 */
void Screen::_mouse(GLFWwindow* window) {
    panX = -1 * mapX(Input::mouseX);
    panY = -1 * mapY(Input::mouseY);
    Input::updateMouse(0, 0);
    glfwSetCursorPos(window, width/2, height/2); // Center mouse after panning to it
}

/*
 *  Pan the center of the map to be in the center of the screen, leave their mouse alone.
 *  Called on SPACE
 */
void Screen::_center() {
    panX = 0;
    panY = 0;
}

void Screen::_size(GLFWwindow* window, int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, 0, 1);
    glViewport(0, 0, pxWidth, pxHeight);
}


void Screen::_framebuffer(GLFWwindow* window, int newPxWidth, int newPxHeight){
    pxWidth = newPxWidth;
    pxHeight = newPxHeight;
    glViewport(0, 0, pxWidth, pxHeight);
    glOrtho(-width/2, width/2, -height/2, height/2, 0, 1);
}