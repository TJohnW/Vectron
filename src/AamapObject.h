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

#ifndef AAMAPOBJECT_H
#define AAMAPOBJECT_H

#include "stdafx.h"

#include "Shader.h"

class AamapObject {
public:

    virtual void update() = 0;
    virtual void draw( glm::mat4 &VP, Shader *shader ) = 0;

    virtual void resize(double factor) = 0;
    //virtual string _xml() = 0;
    /*
     *	Need some functions here for every object to resize x2 or /2 in size.
     *
     */
};

#endif