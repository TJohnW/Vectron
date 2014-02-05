/*
********************************************************************************
Vectron - map editor for Armagetron Advanced.
Copyright (C) 2014  Tristan Whitcher    (tristan.whitcher@gmail.com)
David Dubois        (ddubois@jotunstudios.com)
Carlo Veneziano     (carlorfeo@gmail.com)
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

define([
    'Canvas',
    'Aamap',
    'aamapObjects',
    'AamapTools',
    'Toolbar',
    'Info',
    'Mediator',
    'mousetrap'
], function(Canvas, Aamap, aamapObjects, AamapTools, Toolbar, Info, Mediator) {

    var Vectron = Backbone.View.extend({

        initialize: function() {
            this.canvas = new Canvas({
                el: this.$('.canvas-container .canvas')
            });

            this.map = new Aamap();

            this.aamapTools = new AamapTools();

            this.toolbar = new Toolbar({
                el: this.$('.toolbar')
            });

            this.info = new Info({
                el: this.$('.info')
            });

            // temporary, must move to event handler
            this.initShortcuts();

            this.aamapTools.selectTool('select');



            // testing map/canvas
            var zone = aamapObjects.createZone(200, 200, 100);
            this.map.add(zone);

            var zone2 = aamapObjects.createZone(200, 200, 50);
            this.map.add(zone2);

            this.map.remove(zone2);
        },

        initShortcuts: function () {
            Mousetrap.bind('v', function (event) {
                Mediator.pub('tool:select', 'select');
            }.bind(this));

            Mousetrap.bind('s', function (event) {
                Mediator.pub('tool:select', 'spawn');
            }.bind(this));

            Mousetrap.bind('w', function (event) {
                Mediator.pub('tool:select', 'wall');
            }.bind(this));

            Mousetrap.bind('z', function (event) {
                Mediator.pub('tool:select', 'zone');
            }.bind(this));
        }
    });

    return Vectron;
});