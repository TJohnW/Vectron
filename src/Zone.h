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
#ifndef ZONE_H
#define ZONE_H

#include "stdafx.h"

#include "AamapObject.h"
#include "Input.h"
#include "ScreenVars.h"

class Zone : public AamapObject {

public:
    Zone( double newX, double newY, float newRadius );
    void draw( glm::mat4 worldMat );
    void update();
    void resize(double factor);

    void( *ZoneFinishedFunc )();

    static void beginZones( Shader *shader );

    static void initVBO();

private:
    float radius;
    double x, y;
    glm::mat4 modelMat;
    static GLuint vertsVBO, indicesVBO;
    static GLfloat points [];   //64 points should be plenty
    static GLushort indices [];
};

#endif