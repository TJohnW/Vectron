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

GLFWwindow* Screen::window;

int Screen::height = 0;
int Screen::width = 0;

int Screen::pxHeight = 0;
int Screen::pxWidth = 0;

Screen::Screen(int width, int height) {

	glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit( EXIT_FAILURE );

    this.width = width;
    this.height = height;

    this.window = glfwCreateWindow(width, height, "Vectron Alpha 0.0.2", NULL, NULL);

    if (!this.window) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(this.window);
}


void Screen::_size(GLFWwindow* window, int width, int height) {
    this.width = width;
    this.height = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this.width, 0, this.height, 0, 1);
}


void Screen::_framebuffer(GLFWwindow* window, int pxWidth, int pxHeight){
    this.pxWidth = pxWidth;
    this.pxHeight = pxHeight;
    glViewport(0, 0, pxWidth, pxHeight);
}

