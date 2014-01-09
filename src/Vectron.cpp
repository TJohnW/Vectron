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
void loadCursor();
void drawCursor();

forward_list<Zone*> zones;

GLuint cursorTex;

void loadCursor() {
    glGenTextures( 1, &cursorTex );

    glBindTexture( GL_TEXTURE_2D, cursorTex );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Read the file, call glTexImage2D with the right parameters
    int w, h, c;
    GLubyte *texData = stbi_load( "img/Cursor.png", &w, &h, &c, 0 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    if( c == 3 ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, 
            GL_UNSIGNED_BYTE, texData );
    } else if( c == 4 ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
            GL_UNSIGNED_BYTE, texData );
    }
}

void drawCursor() {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, cursorTex );
    glBegin( GL_QUADS );
    glVertex2f( Input::mouseX - 3, Input::mouseY - 3 );
    glVertex2f( Input::mouseX - 3, Input::mouseY + 2 );
    glVertex2f( Input::mouseX + 2, Input::mouseY + 2 );
    glVertex2f( Input::mouseX + 2, Input::mouseY - 3 );
    glEnd();
    glDisable( GL_TEXTURE_2D );
}

int main(void) {

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit( EXIT_FAILURE );

    window = glfwCreateWindow(640, 480, "Vectron Alpha 0.0.2", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    zones.push_front( new Zone( 10, 10, 10 ) );
    Grid *g = new Grid();

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback( window, mousepos_callback );
    glfwSetMouseButtonCallback( window, mousebtn_callback );
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0f);

    loadCursor();

    while (!glfwWindowShouldClose(window)) {

        float ratio;

        glfwGetFramebufferSize(window, &Screen::width, &Screen::height);
        ratio = Screen::width / (float) Screen::height;
        glViewport( 0, 0, Screen::width, Screen::height );

        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0, Screen::width, 0, Screen::height, 1.f, -1.f );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity( );

        //draw the grid first
        g->draw( Screen::width, Screen::height, 23 );

        for( Zone *z : zones ) {
            z->draw();
        }
                
        drawCursor();

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
            new Zone( Input::mouseX, Screen::height - Input::mouseY, 10 ) );
    } else if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, GL_TRUE );
    }
}

void mousepos_callback( GLFWwindow *window, double x, double y ) {
    //Why dows GLFW use doubles if pixels are ints?
    Input::updateMouse( x, y );
}

void mousebtn_callback( GLFWwindow *window, int button, int action, int mods ) {

}