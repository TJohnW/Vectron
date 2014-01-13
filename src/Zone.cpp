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

#include "Zone.h"

GLuint Zone::vertsVBO = 0;
GLuint Zone::indicesVBO = 0;

GLfloat Zone::points [] = new GLfloat[128];
GLushort Zone::indices [] = new GLushort[64];

/* These coordinates now better represent the actual location of the zone in the
    XML which is vital. Now on zoom the zones will accomidate for the change in
    Screen spacing but still retain their value as the same zone. After so much
    zoom, we need to redraw the Screen with less pxspacing but keep the zone the
    same somehow Not sure how yet though.
*/
Zone::Zone( double newX, double newY, float newRadius ) {
    x = newX;
    y = newY;
    radius = newRadius;
    cout << "Adding a zone at (" << x << ", " << y << ")\n";
 }


/*
    Zones need to be drawn according to a set coordiate that can be changed with
    the current Screen scale.
*/

void Zone::draw( glm::mat4 worldMat ) {
    glDrawElements( GL_LINE_LOOP, 64, GL_UNSIGNED_SHORT, (void*) 0 );
}

void Zone::update() {
    //int xDist = Input::mouseMapX - x;
    //int yDist = Input::mouseMapY - y;
    //radius = sqrt( xDist * xDist + yDist* yDist );
    //if(radius < 1) radius = 0.5;
	x = Input::mouseMapX;
	y = Input::mouseMapY;
    if( Input::mouse0 ) {
        ZoneFinishedFunc();
    } else if( Input::keys[GLFW_KEY_EQUAL] && Input::keys[GLFW_KEY_LEFT_CONTROL]) {
    	radius = floor(radius) + 1;
    	Input::keys[GLFW_KEY_EQUAL] = false;
    } else if( Input::keys[GLFW_KEY_MINUS] && Input::keys[GLFW_KEY_LEFT_CONTROL]) {
    	radius = floor(radius) - 1;
    	Input::keys[GLFW_KEY_MINUS] = false;
    } else if (Input::keys[GLFW_KEY_EQUAL]) {
    	radius += 0.05;
    } else if (Input::keys[GLFW_KEY_MINUS]) {
    	radius -= 0.05;
    }
    modelMat[0][0] = radius;
    modelMat[1][1] = radius;
    modelMat[0][3] = x;
    modelMat[1][3] = y;
}

void Zone::resize(double factor) {
    radius *= factor;
    x *= factor;
    y *= factor;
}

void Zone::beginZones( Shader *shader ) {
    glBindBuffer( GL_ARRAY_BUFFER, vertsVBO );

    glVertexAttribPointer( shader->vertPos, 2, GL_FLOAT, GL_FALSE, 
        2 * sizeof(GL_FLOAT), (void*) 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesVBO );
}

void Zone::initVBO() {
    float theta = 0;
    for( int i = 0; i < 64; i++ ) {
        points[i * 2] = cos( theta );
        points[i * 2 + 1] = sin( theta );
        indices[i] = i;
        theta += .0981747704;
    }

    glGenBuffers( 1, &vertsVBO );
    glBindBuffer( GL_ARRAY_BUFFER, vertsVBO );
    glBufferData( GL_ARRAY_BUFFER, 128 * sizeof(GLfloat), points, 
        GL_STATIC_DRAW );

    glGenBuffers( 1, &indicesVBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesVBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 64 * sizeof(GLushort), indices,
        GL_STATIC_DRAW );
}