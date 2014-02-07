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
            this.zoomMaxLimit = 100;
            this.zoomMinLimit = 0.01;

            this.pan = new geometry.Point;

            var canvasSize = this.getCanvasSize();

            this.screen = new Raphael(
                this.el,
                canvasSize.width,
                canvasSize.height
            );

            this.render();

            Mediator.sub('aamap:addedObject', this.addObject, this);
            Mediator.sub('aamap:removedObject', this.removeObject, this);
        },

        events: {
            mousemove: function (event) {
                var cursorPos = new geometry.Point(event.offsetX, event.offsetY);
                this.renderCursor(cursorPos);
                Mediator.pub('cursor:moved', cursorPos);
            }
        },

        subscriptions: {
            'canvas:zoom-in': 'zoomIn',
            'canvas:zoom-out': 'zoomOut'
        },

        renderGrid: function () {
            var c = this.getCanvasSize();
            var path = '';

            for (var x = 0; x < c.width; x += 10 * this.zoom) {
                path += 'M' + x + ' ' + 0 + 'L' + x + ' ' + c.height;
            }

            for (var y = 0; y < c.height; y += 10 * this.zoom) {
                path += 'M' + 0 + ' ' + y + 'L' + c.width + ' ' + y;
            }

            if (this.grid) {
                this.grid.remove();
            }
            this.grid = this.screen
                .path(path)
                .attr({stroke: '#222'});
        },

        renderCursor: function (m) {
            if (this.cross) {
                this.cross.remove();
            };

            var c = this.getCanvasSize();
            var path = 'M' + Math.round(m.x) + ' 0L' + Math.round(m.x) + ' ' + Math.round(c.height) +
                    'M0 ' + Math.round(m.y) + 'L' + Math.round(c.width) + ' ' + Math.round(m.y);

            this.cross = this.screen.path(path).attr({
                stroke: '#666'
            });
        },

        getCanvasSize: function() {
            return {
                width: this.$el.width(),
                height: this.$el.height()
            }
        },

        render: function () {
            this.screen.clear();
            this.renderGrid();

            //objects.forEach(this.addObject.bind(this));
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

        zoomIn: function () {
            var zoom = Math.min(this.zoomMaxLimit, this.zoom * 2);
            this.setZoom(zoom);
        },

        zoomOut: function () {
            var zoom = Math.max(this.zoomMinLimit, this.zoom / 2);
            this.setZoom(zoom);
        },

        setZoom: function (value) {
            if (value == this.zoom) return;

            this.zoom = value;
            this.render();

            Mediator.pub('canvas:zoom-changed', this.zoom);

            // enable/disable zoom-in button
            if (this.zoom >= this.zoomMaxLimit) {
                Mediator.pub('button:zoom-in-enable', false);
            } else {
                Mediator.pub('button:zoom-in-enable', true);
            }

            // enable/disable zoom-out button
            if (this.zoom <= this.zoomMinLimit) {
                Mediator.pub('button:zoom-out-enable', false);
            } else {
                Mediator.pub('button:zoom-out-enable', true);
            }
        }
    });

    return Canvas;
});
