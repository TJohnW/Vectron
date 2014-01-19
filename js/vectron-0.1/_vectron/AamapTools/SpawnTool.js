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

function SpawnTool(vectron) {

    this.vectron = vectron;
    this.active = false;

}  

SpawnTool.prototype = {

    constructor: SpawnTool,

    connect:function() {
        if(this.vectron.map.currentTool != null && this.vectron.map.currentTool.active) {
            this.vectron.gui.writeLog("Tool active cannot select another right now.");
            return false;
        } else {
        	this.vectron.map.currentTool = this;
        	return true;
        }
    },

    disconnect:function() {
    	this.vectron.map.currentTool = null;
    	this.active = false;
    },


    //mouse down, detect drag direction locked to map axes.
    start:function() {

    	this.active = true;
    },
    //mouse up they have selected a direction store the point as an object.
    complete:function() {

    	this.active = false;
    }

}