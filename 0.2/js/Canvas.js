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
    'Mediator',
    'mousewheel'
], function(geometry, Raphael, Mediator) {

    var Canvas = Backbone.View.extend({

        initialize: function(options) {
            this.zoom = 1;
            this.zoomMaxLimit = 100;
            this.zoomMinLimit = 0.01;
            this.zoomStep = 1.05;

            this.gridSize = 5000;
            this.gridStep = 10;
            this.gridStart = new geometry.Point;

            // canvas anchor point to handle panning
            this.anchor = new geometry.Point;

            this.updateCanvasSize();
            this.paper = new Raphael(
                this.el,
                this.canvasSize.width,
                this.canvasSize.height
            );

            this.objects = this.paper.set();
            this.createGrid();

            this.mousePos = new geometry.Point;
            this.updateCursorPos(0, 0);
            this.createCursorPointer();

            this.render();
        },

        subscriptions: {
            'aamap:addedObject': 'addObject',
            'aamap:removedObject': 'removeObject',

            'canvas:zoom-in': 'zoomIn',
            'canvas:zoom-out': 'zoomOut',

            'canvas:pan-start': function () {
                if (! this.cursorPanStart) {
                    this.cursorPanStart = this.cursorPos.clone();
                    //console.log('panStart', this.cursorPanStart.toString());
                }
            },

            'canvas:pan-stop': function () {
                this.cursorPanStart = null;
            },
        },

        events: {
            resize: 'updateCanvasSize',

            mousemove: function (event) {
                this.cursorPointer.x.transform('T' + event.offsetX + ' 0');
                this.cursorPointer.y.transform('T 0 ' + event.offsetY);

                if (this.cursorPanStart) {
                    // move canvas
                    var panTo = this
                        .screenToMap(event.offsetX, event.offsetY, true)
                        .subtract(this.cursorPanStart);

                    this.setAnchor(panTo.x, panTo.y);
                    this.render();
                } else {
                    // update cursor
                    this.updateCursorPos(event.offsetX, event.offsetY)
                }

                this.updateMousePos(event.offsetX, event.offsetY);
            },

            mousewheel: function (event) {
                // delta depends on wheel speed
                if (event.deltaY > 0) {
                    this.zoomIn(event.deltaY, true);
                } else if (event.deltaY < 0) {
                    this.zoomOut(Math.abs(event.deltaY), true);
                };
            }
        },

        updateMousePos: function (x, y) {
            this.mousePos.x = x;
            this.mousePos.y = y;
            Mediator.publish('canvas:mouse-moved', this.mousePos);
        },

        updateCursorPos: function (x, y) {
            this.cursorPos = this.screenToMap(x, y);
            Mediator.publish('canvas:cursor-moved', this.cursorPos);
        },

        /**
         * @object type AamapObject
         */
        addObject: function (object) {
            var canvasElement;

            switch(object.type) {
                case 'zone':
                    var x = object.get('x');
                    var y = object.get('y'); // fix aamap y vs browser y
                    var radius = object.get('radius');
                    canvasElement = this.paper
                        .circle(x, y, radius)
                        .attr('stroke', object.getColor());
                    break;
            }

            object.set('canvasElement', canvasElement);

            this.objects.push(canvasElement);
            this.render();
        },

        /**
         * @object type AamapObject
         */
        removeObject: function (object) {
            object.get('canvasElement').remove();
            this.render();
        },

        updateCanvasSize: function() {
            return this.canvasSize = {
                width: this.$el.width(),
                height: this.$el.height()
            }
        },

        createGrid: function () {
            var pathBuilder = new geometry.PathBuilder;

            for (var x = -this.gridSize; x <= this.gridSize; x += this.gridStep) {
                pathBuilder
                    .moveTo(x, -this.gridSize)
                    .lineTo(x, this.gridSize);
            }

            //for (var y = - this.gridSize; y <= 0; y += this.gridStep) {
            for (var y = -this.gridSize; y <= this.gridSize; y += this.gridStep) {
                pathBuilder
                    .moveTo(-this.gridSize, y)
                    .lineTo(this.gridSize, y);
            }

            // render grid
            this.grid = this.paper
                .path(pathBuilder.getString())
                .attr('stroke', '#222');

            this.objects.push(this.grid);
        },

        createCursorPointer: function () {
            if (this.cursorPointer) {
                this.cursorPointer.x.remove();
                this.cursorPointer.y.remove();
            } else {
                this.cursorPointer = {};
            }

            var paper = this.paper,
                color = '#ddd';

            function pointerPath (pathBuilder) {
                return paper
                    .path(pathBuilder.getString())
                    .attr('stroke', color);
            }

            // vertical line
            var pathBuilder = new geometry.PathBuilder()
                .moveTo(0, 0)
                .lineTo(0, this.canvasSize.height);

            this.cursorPointer.x = pointerPath(pathBuilder);

            // horizontal line
            pathBuilder = new geometry.PathBuilder()
                .moveTo(0, 0)
                .lineTo(this.canvasSize.width, 0);

            this.cursorPointer.y = pointerPath(pathBuilder);
        },

        /**
         * @times type Number: zoom multiplier
         * @targetMouse type bool: target mouse after zoom
         */
        zoomIn: function (times, targetMouse) {
            times = times || 1;

            var nextZoom = Math.min(this.zoomMaxLimit, this.zoom * this.zoomStep * times);
            if (nextZoom == this.zoom) return;

            this.setZoom(nextZoom, targetMouse);
        },

        /**
         * @times type Number: zoom multiplier
         * @targetMouse type bool: target mouse after zoom
         */
        zoomOut: function (times, targetMouse) {
            times = times || 1;

            var nextZoom = Math.max(this.zoomMinLimit, this.zoom / this.zoomStep / times);
            if (nextZoom == this.zoom) return;

            this.setZoom(nextZoom, targetMouse);
        },

        render: function () {
            var transformString = [
                'S',
                this.zoom,
                - this.zoom, // inverse y
                0, 0,
                'T',
                this.anchor.x * this.zoom,
                - this.anchor.y * this.zoom
            ].join(' ');

            //console.log('render', transformString);
            this.objects.transform(transformString);
        },

        /**
         * adjust this.anchor so that the target point stays still after zooming
         * @zoomTo type Number
         * @targetMouse type bool: true when using mousewheel, false otherwise
         */
        adjustPan: function(zoomTo, targetMouse) {
            var targetX, targetY, // target point in screen coordinates
                realTarget; // screen target translated into real map coordinates

            if (targetMouse) {
                // target point is current mouse pos
                targetX = this.mousePos.x;
                targetY = this.mousePos.y;
                realTarget = this.cursorPos;
            } else {
                // target point is screen center
                targetX = this.canvasSize.width / 2;
                targetY = this.canvasSize.height / 2;
                realTarget = this.screenToMap(targetX, targetY);
            }

            var panX = (targetX - realTarget.x * zoomTo) / zoomTo;
            var panY = (- targetY - realTarget.y * zoomTo) / zoomTo;
            this.setAnchor(panX, panY);
        },

        setZoom: function (zoomTo, targetMouse) {
            // call adjustPan before setting new zoom
            // because it uses this.zoom (called by screenToMap)
            this.adjustPan(zoomTo, targetMouse);

            this.zoom = zoomTo;
            this.render();

            Mediator.publish('canvas:zoom-changed', this.zoom);

            // enable/disable zoom-in button
            if (this.zoom >= this.zoomMaxLimit) {
                Mediator.publish('button:zoom-in-enable', false);
            } else {
                Mediator.publish('button:zoom-in-enable', true);
            }

            this.updateCursorPos(this.mousePos.x, this.mousePos.y);

            // enable/disable zoom-out button
            if (this.zoom <= this.zoomMinLimit) {
                Mediator.publish('button:zoom-out-enable', false);
            } else {
                Mediator.publish('button:zoom-out-enable', true);
            }
        },

        setAnchor: function (x, y) {
            this.anchor.x = x;
            this.anchor.y = y;
            this.render();
            //console.log('pan', this.anchor.toString());
            Mediator.publish('canvas:anchor-changed', this.anchor);
        },

        getCurrentCenter: function () {
            var x = this.canvasSize.width / 2 + this.anchor.x;
            var y = this.canvasSize.height / 2 + this.anchor.y;
            return new geometry.Point(x, y);
        },

        /**
         * @point type PoinT: map coordinates
         * @returns type Point: SVG coordinates
         */
        mapToScreen: function (mapX, mapY) {
            var x = (this.anchor.x + mapX) * this.zoom;
            var y = - (this.anchor.y + mapY) * this.zoom;
            return new geometry.Point(x, y);
        },

        /**
         * @point type Point: SVG coordinates
         * @returns type Point: map coordinates
         */
        screenToMap: function (screenX, screenY, discardPan) {
            var point = new geometry.Point(
                screenX / this.zoom,
                - screenY / this.zoom
            );
            if (discardPan) {
                return point;
            }
            return point.subtract(this.anchor);
        }
    });

    return Canvas;
});
