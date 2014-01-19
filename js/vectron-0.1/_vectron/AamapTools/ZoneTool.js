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

function ZoneTool(vectron) {

    this.vectron = vectron;
    this.active = false;

    this.guideObj = null;

    //this.radius = this.vectron.settings.get('Zone_Radius');
    this.radius = 1;
    this.typeArray = {
        0: ["death", "#ff0000"],
        1: ["win", "#2a822d"],
        2: ["target", "#63f768"],
        3: ["rubber", "#f2c73a"],
        4: ["fortress", "#62bef6"]
    }
    this.type = 0;
    //alert(this.typeArray[this.type][1]);

}  

ZoneTool.prototype = {

    constructor: ZoneTool,

    toggle:function(type) {
        if(type == null) {


        } else {


        }

    },

    connect:function() {
        if(this.vectron.map.currentTool != null && this.vectron.map.currentTool.active) {
            this.vectron.gui.writeLog("Tool active cannot select another right now.");
            return false;
        } else {
            this.vectron.map.currentTool = this;
            this.guide();
            return true;
        }
    },

    disconnect:function() {
        this.vectron.map.currentTool = null;
        this.guideObj.remove();
        this.active = false;
    },

    guide:function() {
        if(this.guideObj != null)
            this.guideObj.remove();
        var realX = this.vectron.cursor.realX;
        var realY = this.vectron.cursor.realY;
        var radius = this.radius;
        this.guideObj = this.vectron.screen.circle(realX, realY,
            radius*this.vectron.map.zoom).attr(
                {"stroke": this.typeArray[this.type][1],"stroke-dasharray": "--..", "fill": this.typeArray[this.type][1], "fill-opacity": "0.2"}
            );
    },

    //mouse up they have selected a direction store the point as an object.
    //no start to zone tool, just add the zone and listen for + - event.
    complete:function() {
        this.vectron.map.add(new Zone(this.vectron,
                                this.vectron.map.mapX(this.vectron.cursor.realX),
                                this.vectron.map.mapY(this.vectron.cursor.realY),
                                this.radius, this.type));
        this.guideObj.remove();
        this.active = false;
    }

}
