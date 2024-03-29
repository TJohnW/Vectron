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

function XMLHandler(vectron) {

    this.vectron = vectron;

    $('#files').change(function(e) {

        vectron.map.handler.handle(e, vectron);
        vectron.gui.writeLog("SDF.");
    });

}  

XMLHandler.prototype = {

    constructor: XMLHandler,

    //Returns aamapObject representation of a map
    //Also stores the dtd and required info into the map provided

    process:function(xml) {
        this.vectron.gui.writeLog(xml);
        var x;
        var y;
        var vectron = this.vectron;
        var ptsx = [];
        var ptsy = [];

        $(xml).find("Zone").each(function() {
            var zone = $(this);
            var effect = zone.attr("effect");
            var radius = zone.find("ShapeCircle").attr("radius");
            x = zone.find("Point").attr("x");
            y = zone.find("Point").attr("y");
            ptsx.push(parseFloat(x));
            ptsy.push(parseFloat(y));
            vectron.gui.writeLog("(" + x + ', ' + y + ')' + radius + " " + effect);
            vectron.map.add(
                new Zone(
                    vectron, parseFloat(x), parseFloat(y), parseFloat(radius), vectron.map.zoneTool.whatType[effect],
                    vectron.map.nextId)
            );
            vectron.map.nextId++;
        });

        $(xml).find("Wall").each(function() {
            var wall = $(this);
            var points = [];
            wall.find("Point").each(function() {
                var x = $(this).attr("x");
                var y = $(this).attr("y");
                ptsx.push(parseFloat(x));
                ptsy.push(parseFloat(y));
                points.push(new WallPoint(parseFloat(x), parseFloat(y)));
            });
            vectron.gui.writeLog("Wall Added.");
            var wallObj = new Wall(vectron, vectron.map.nextId);
            vectron.map.nextId++;
            wallObj.points = points;
            wallObj.render();
            vectron.map.add(wallObj);
        });

        var max_x = Math.max.apply(Math, ptsx);
        var min_x = Math.min.apply(Math, ptsx);
        var max_y = Math.max.apply(Math, ptsy);
        var min_y = Math.min.apply(Math, ptsy);

        this.vectron.map.panX = -1*(max_x + min_x)/2;
        this.vectron.map.panY = -1*(max_y + min_y)/2;
        this.vectron.render();

    },

    writeZone:function(zone) {

    },

    writeSpawn:function(spawn) {

    },

    writeWall:function(wall) {

    },

    propertyDTD:function(dtd) {

    },

    propertyAxes:function(axes) {

    },

    load:function(vectron) {

        if (window.File && window.FileReader && window.FileList && window.Blob) {
            this.vectron.gui.writeLog("File reading supported by your browser. Good.");
        } else {
            this.vectron.gui.writeLog("And you can't read files D:. NOOB.");
        }
    },

    handle:function(evt, vectron) {
        var reader = new FileReader();
        reader.readAsText(evt.target.files[0]);
        var result;
        var self = this;
        reader.vectron = vectron;
        reader.onload = function(evt) {
            alert(this.result);
            this.vectron.map.handler.process(this.result);
        };
    },

    onload:function() {
        alert(this.result);
        this.vectron.gui.writeLog("HI");
        this.process(this.result);
    }

}
