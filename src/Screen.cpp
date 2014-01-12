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

Screen::Screen(int width, int height) {

	//glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit( EXIT_FAILURE );

    Screen::width = width;
    Screen::height = height;

    this->window = glfwCreateWindow(width, height, "Vectron Alpha 0.0.2", NULL, NULL);

    if (!this->window) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, Screen::_framebuffer);
    glfwSetWindowSizeCallback(this->window, Screen::_size);

    /* Initial Before callback */

    glfwGetFramebufferSize(this->window, &Screen::pxWidth, &Screen::pxHeight);
    glViewport(0, 0, Screen::pxWidth, Screen::pxHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Screen::width/2, Screen::width/2, -Screen::height/2,
        Screen::height/2, 0, 1);
}

void Screen::draw() {
	
	Aamap::render(Screen::width, Screen::height);
    Input::drawCursor();
}

int Screen::mapX(double mouseX) {
    return mouseX / Grid::spacing - Screen::panX;
}

int Screen::mapY(double mouseY) {
    return mouseY / Grid::spacing - Screen::panY;
}

void Screen::_up() {
    Screen::panY -= 1;
}

void Screen::_down() {
    Screen::panY += 1;
}

void Screen::_right() {
    Screen::panX -= 1;
}

void Screen::_left() {
    Screen::panX += 1;
}

/*
 *  Pan the center of the camera to the mouse and move the mouse to the center
 *  Called on LEFTCTRL + SPACE
 */
void Screen::_mouse(GLFWwindow* window) {
    Screen::panX = -1*Screen::mapX(Input::mouseX);
    Screen::panY = -1*Screen::mapY(Input::mouseY);
    Input::updateMouse(0, 0);
    glfwSetCursorPos(window, Screen::width/2, Screen::height/2); // Center mouse after panning to it
}

/*
 *  Pan the center of the map to be in the center of the screen, leave their mouse alone.
 *  Called on SPACE
 */
void Screen::_center() {
    Screen::panX = 0;
    Screen::panY = 0;
}

void Screen::_size(GLFWwindow* window, int width, int height) {
    Screen::width = width;
    Screen::height = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Screen::width/2, Screen::width/2, -Screen::height/2, Screen::height/2, 0, 1);
    glViewport(0, 0, Screen::pxWidth, Screen::pxHeight);
}


void Screen::_framebuffer(GLFWwindow* window, int pxWidth, int pxHeight){
    Screen::pxWidth = pxWidth;
    Screen::pxHeight = pxHeight;
    glViewport(0, 0, pxWidth, pxHeight);
    glOrtho(-Screen::width/2, Screen::width/2, -Screen::height/2, Screen::height/2, 0, 1);
}

