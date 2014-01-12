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
bool Aamap::toolActive = false;
double Aamap::sizeFactor = 1;

void Aamap::render() {
    for( AamapObject *o : objects ) {
    	o->draw();
   	}
}

void Aamap::resize(double factor) {
    for( AamapObject *o : objects ) {
        o->resize(factor);
    }
}

void Aamap::update() {
    if( curObj != NULL ) {
        curObj->update();
    }
    if( Input::keys[GLFW_KEY_Z] ) {
        //spawn a zone!
        if(!Aamap::toolActive) {
            Zone *z = new Zone( Input::mouseMapX, Input::mouseMapY, 5 );
            toolActive = true;
            objects.push_front( z );
            curObj = z;
            z->ZoneFinishedFunc = []() -> void { 
                curObj = NULL;
                Aamap::toolActive = false;
            };
        }
        Input::keys[GLFW_KEY_Z] = false;
    } else if( Input::keys[GLFW_KEY_W] ) {
        //Spawn a wall!
        if(!Aamap::toolActive) {
            Wall *w = new Wall();
            objects.push_front( w );
            curObj = w;
            w->WallFinishedFunc = []() -> void {
                curObj = NULL;
                Aamap::toolActive = false;
            };
        }
        Input::keys[GLFW_KEY_W] = false;
    } else if( Input::keys[GLFW_KEY_EQUAL]) {
        if(!Aamap::toolActive && sizeFactor < 16) {
            cout << "equal" << endl;
            Aamap::resize(2);
            sizeFactor *= 2;
            Input::keys[GLFW_KEY_EQUAL] = false;
        }
    } else if( Input::keys[GLFW_KEY_MINUS]) {
        if(!Aamap::toolActive && sizeFactor > 0.25) {
            cout << "mins" << endl;
            Aamap::resize(0.5);
            sizeFactor *= 0.5;
            Input::keys[GLFW_KEY_MINUS] = false;
        }
    }

}
