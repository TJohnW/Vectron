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

function Aamap(vectron) {

    this.vectron = vectron;
    this.screen = vectron.screen;
    this.active = true;

    this.xml;

    this.aamapObjects = [];

    this.wallTool = new WallTool(this);
    this.zoneTool = new ZoneTool(this);
    this.spawnTool = new SpawnTool(this);

}  

Aamap.prototype = {

    constructor: Aamap,

    // Called when settings saved or anythign changes so the debug log can be removed
    render:function() {
        for(var i = 0; i < this.aamapObjects.length; i++) {
            this.aamapObjects[i].render();
        }
    },

    add:function(obj) {
        //add to xml of the obj
        this.aamapObjects.push(obj);
    },

    remove:function() {
        this.aamapObjects.pop();
    },

    show:function() {
        
        this.active = true; //Draw the cursor!
    },

    hide:function() {

        this.active = false; //Dont draw the cursor!
    },

    mapX:function(realX) {


    },

    mapY:function(realY) {


    }

}
