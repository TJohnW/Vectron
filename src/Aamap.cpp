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

#include "Aamap.h"

AamapObject *Aamap::curObj;

void Aamap::render() {
    for( AamapObject *o : objects ) {
    	o->draw();
   	}
}

void Aamap::update() {
    if( curObj != NULL ) {
        curObj->update();
    }
    if( Input::keys[GLFW_KEY_Z] ) {
        //spawn a Screen!
        Zone *z = new Zone( Input::mouseX, Input::mouseY, 5 );
        objects.push_front( z );
        curObj = z;
        z->ZoneFinishedFunc = []() -> void { curObj = NULL; };
    } else if( Input::keys[GLFW_KEY_W] ) {
        //Spawn a wall!
        Wall *w = new Wall();
        objects.push_front( w );
        curObj = w;
        w->WallFinishedFunc = []() -> void { curObj = NULL; };
    }
}