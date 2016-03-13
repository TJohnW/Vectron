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

window.onload = function() {
    var v = new Vectron();
}

function Vectron() {

    this.width = $("#canvas_container").width();
    this.height = $("#canvas_container").height();

    this.screen = new Raphael(document.getElementById('canvas_container'), 
        this.width, this.height);

    this.settings = new Settings(this);

    this.gui = new GUI(this);

    this.cursor = new Cursor(this);

    this.map = new Aamap(this);

    this.eventHandler = new EventHandler(this);

    this.render();

}  

Vectron.prototype = {

    constructor: Vectron,

    render:function() {
        this.screen.clear();
        this.width = $("#canvas_container").width();
        this.height = $("#canvas_container").height();

        this.screen.setSize(this.width, this.height);
        this.map.render();
        if(this.map.currentTool.currentObj != null && this.map.currentTool instanceof WallTool)
            this.map.currentTool.currentObj.render();
        if(this.map.currentTool instanceof ZoneTool)
            this.map.currentTool.guide();
        if(this.map.currentTool instanceof SpawnTool)
            this.map.currentTool.currentObj.guide();
        //this.cursor.render();
    }

}
