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

define(['geometry', 'Mediator'], function(geometry, Mediator) {

	function LabeledValue(name, value) {
		this.$el = $('<span class="var"/>');

		var $name = $('<span class="name">' + name + '</span>')
			.appendTo(this.$el);

		var $value = $('<span class="value">' + value + '</span>')
			.appendTo(this.$el);

		this.set = function (value) {
			$value.html(value);
		};
	}

    var Info = Backbone.View.extend({
        initialize: function(options) {
        	this.x = new LabeledValue('x: ', 0);
        	this.y = new LabeledValue('y: ', 0);

        	this.$el
        		.append(this.x.$el)
        		.append(this.y.$el);

        	Mediator.sub('cursor:moved', this.updateCursor, this);
        },

        updateCursor: function (x, y) {
        	this.x.set(x);
        	this.y.set(y);
        }
    });

    return Info;
});
