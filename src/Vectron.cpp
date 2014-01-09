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

#include "stdafx.h"

#include "Grid.h"
#include "Input.h"
#include "Screen.h"
#include "Zone.h"

using namespace std;

void error_callback( int error, const char *description );
void key_callback( GLFWwindow *window, int key, int scancode, int action, 
    int mods );
void mousepos_callback( GLFWwindow *window, double x, double y );
void mousebtn_callback( GLFWwindow *window, int button, int action, int mods );

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow* window, int width, int height);


void px(double width, double height, double *pxWidth, double *pxHeight);

void addZone();

forward_list<Zone*> zones;

int main(void) {

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    Screen::height = 480;
    Screen::width = 640;
    window = glfwCreateWindow(640, 480, "Vectron Alpha 0.0.2", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    zones.push_front( new Zone( 400, 400, 10 ) );
    Grid *g = new Grid();

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    /* Initial Before callback */

    glfwGetFramebufferSize(window, &Screen::pxWidth, &Screen::pxHeight);
    glViewport(0, 0, Screen::pxWidth, Screen::pxHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Screen::width, Screen::height, 0, 0, 1);


    glfwSetCursorPosCallback( window, mousepos_callback );
    glfwSetMouseButtonCallback( window, mousebtn_callback );
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        g->draw( Screen::pxWidth, Screen::pxHeight, 23 );

        //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        for( Zone *z : zones ) {
            z->draw();
        }
                
        //glfwSetCursorPos(window, 0,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void error_callback( int error, const char *description ) {
    fputs( description, stderr );
}

void key_callback( GLFWwindow *window, int key, int scancode, int action, 
    int mods ) {
    if( key == GLFW_KEY_Z && action == GLFW_RELEASE ) {
        zones.push_front( 
            new Zone( Input::mouseX, Input::mouseY, 10 ) );
    } else if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, GL_TRUE );
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    Screen::width = width;
    Screen::height = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Screen::width, Screen::height, 0, 0, 1);
}


void framebuffer_size_callback(GLFWwindow* window, int pxWidth, int pxHeight){
    Screen::pxWidth = pxWidth;
    Screen::pxHeight = pxHeight;
    glViewport(0, 0, pxWidth, pxHeight);
}

void mousepos_callback( GLFWwindow *window, double x, double y ) {
    //Why dows GLFW use doubles if pixels are ints?
    Input::updateMouse( x, y );
}

void mousebtn_callback( GLFWwindow *window, int button, int action, int mods ) {

}