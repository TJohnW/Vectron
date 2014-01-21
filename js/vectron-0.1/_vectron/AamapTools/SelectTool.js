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

    this.guideObj = null;
    this.selectedObjs = null;

}  

SpawnTool.prototype = {

    constructor: SpawnTool,

    connect:function() {
        if(this.vectron.map.currentTool != null && this.vectron.map.currentTool.active) {
            this.vectron.gui.writeLog("Tool active cannot select another right now.");
            return false;
        } else {
            if(this.vectron.map.currentTool != null)
                this.vectron.map.currentTool.disconnect();
        	this.vectron.map.currentTool = this;
        	return true;
        }
    },

    disconnect:function() {
        if(this.currentObj != null) {
            this.currentObj.obj.remove();
            this.currentObj.guideObj.remove();
        }
        this.vectron.map.currentTool = null;
        this.active = false;
    },


    //mouse down start drag
    start:function() {
        this.selectedObjects = select( xStart, yStart, xEnd, yEnd );
    	this.active = true;
    },
    //mouse up they have selected a direction store the point as an object.
    complete:function() {
        this.currentObj.guideObj.remove();
        this.vectron.map.add(this.currentObj);
        this.currentObj.render();
        this.currentObj = null;
    	this.active = false;
    }

    select:function( xStart, yStart, xEnd, yEnd ) {
        selectedObjs = [];
        params = orderCorners( xStart, yStart, xEnd, yEnd ); 
        //params = [left, top, right, bottom]
        for( int i = 0; i < this.vectron.map.objects.length; i++ ) {
            curObj = this.vectron.map.objects[i];
            if( curObj instanceof Wall ) {
                //Don't care
            } else {
                if( params[0] < curObj.x && curObj.x < params[2] &&
                    params[1] > curObj.y && curObj.y > params[3] ) {
                    curObj.obj.glow();
                    selectedObjs.push( curObj.obj );
                } else {
                    //noglo
                    curObj.obj.glow( 0 );
                }
            }
        }
    },
    
    /* Much gross. Very ew. */
    orderCorners:function( xStart, yStart, xEnd, yEnd ) {
        ordered = [];
        if( xStart < xEnd ) {
            if( yStart < yEnd ) {
                ordered = [xStart, yEnd, xEnd, yStart];
            } else {
                ordered = [xStart, yStart, xEnd, yEnd];
            } 
        } else {
            if( yStart < yEnd ) {
                ordered = [xEnd, yEnd, xStart, yStart];
            } else {
                ordered = [xEnd, yStart, xStart, yEnd];
            }
        }
    }
}
