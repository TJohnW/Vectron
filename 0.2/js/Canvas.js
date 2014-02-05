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
    'geometry',
    'raphael',
    'Mediator'
], function(geometry, Raphael, Mediator) {

    var Canvas = Backbone.View.extend({

        initialize: function(options) {
            this.zoom = 1;
            this.pan = new geometry.Point;

            var canvasSize = this.getCanvasSize();

            this.screen = new Raphael(
                this.el,
                canvasSize.width,
                canvasSize.height
            );

            Mediator.sub('aamap:addedObject', this.addObject, this);
            Mediator.sub('aamap:removedObject', this.removeObject, this);
        },

        events: {
            mousemove: function (event) {
                // canvas.x starts from 50 (i.e. toolbar width)
                // TODO check this bug
                var toolbarWidth = $('#main-toolbar').outerWidth();
                Mediator.pub('cursor:moved', event.clientX - toolbarWidth, event.clientY);
            }
        },

        getCanvasSize: function() {
            return {
                width: this.$el.width(),
                height: this.$el.height()
            }
        },

        render: function (objects) {
            this.screen.clear();
            objects.forEach(this.addObject.bind(this));
        },

        addObject: function(object) {
            var drawData = object.getDrawData();
            screenElement = this.screen.add([drawData]);
            object.set('screenElement', screenElement);

            // hover handling, there's better way for this
            screenElement.mouseover(function() {
                Mediator.pub('canvasObject:mouseover', object);
            });
        },

        removeObject: function (object) {
            object.get('screenElement').remove();
        },

        setZoom: function (value) {
            
        }
    });

    return Canvas;
});
