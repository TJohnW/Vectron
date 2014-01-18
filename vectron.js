//********//********//********//********//********//********//********//********
window.onload = function() {

    var vectron = new Canvas();

    vectron.render( 10 );

    window.onresize = function() {
        vectron.render();
    }


    $("#canvas_container").mousemove(function(event) {
        event.pageX -= 60;
        vectron.cursor.render(event.pageX, event.pageY, vectron.spacing);
        if(vectron.map.active && vectron.map.currentObj instanceof Wall) {
            vectron.map.currentObj.guide();
        } else if (vectron.map.active && vectron.map.currentObj instanceof Zone) {

        }
    });

    $("#canvas_container").on("mouseup", function(e) {

            e.preventDefault();
            if(vectron.map.active) {
                vectron.map.currentObj.progress();
            } else {
                vectron.map.objects.push(new Wall(vectron));
            }
            /*
            vectron.map.objects.push(
                new Zone(vectron,
                        vectron.getMapX(vectron.cursor.snappedMouseX),
                        vectron.getMapY(vectron.cursor.snappedMouseY),
                        1, "death")
            );
            */
    }); 

    $("#canvas_container").on("dblclick", function(e) {

            e.preventDefault();
            if(vectron.map.active && vectron.map.currentObj instanceof Wall) {
                vectron.map.currentObj.finish();
            } else {
                //vectron.map.objects.push(new Wall(vectron));
            }
            /*
            vectron.map.objects.push(
                new Zone(vectron,
                        vectron.getMapX(vectron.cursor.snappedMouseX),
                        vectron.getMapY(vectron.cursor.snappedMouseY),
                        1, "death")
            );
            */
    });
}


function Canvas() {
    this.width = $("#canvas_container").width();
    this.height = $("#canvas_container").height();
    this.paper = new Raphael(document.getElementById('canvas_container'), 
        this.width, this.height);
    this.spacing = 10;
    this.map = new Aamap(this);
    this.cursor = new Cursor(this);
}  

Canvas.prototype = {

    constructor: Canvas,

    render:function() {
        this.paper.clear();
        this.width = $("#canvas_container").width();
        this.height = $("#canvas_container").height();

        this.cursor.middleX = this.width/2;
        this.cursor.middleY = this.height/2;

        this.paper.setSize(this.width, this.height);
        this.draw_grid();
        this.map.render();
    },
    
    draw_grid:function() {
        var gridArray = [];
        for(var i=this.width/2; i < this.width; i+= this.spacing) {
            gridArray = gridArray.concat(["M", i, this.height, "L", i, 0]);
        }
    
        for(var i=this.width/2; i > 0; i -= this.spacing) {
            gridArray = gridArray.concat(["M", i,this. height, "L", i, 0]);
        }
    
        for(var i=this.height/2; i < this.height; i+= this.spacing) {
            gridArray = gridArray.concat(["M", this.width, i, "L", 0, i]);
        }
    
        for(var i=this.height/2; i > 0; i -= this.spacing) {
            gridArray = gridArray.concat(["M", this.width, i, "L", 0, i]);
        }
        
        this.grid = this.paper.path(gridArray).attr("stroke", "#d6d6ec");
    },

    getRealX:function(x) {
        return this.width/2 + (x*this.spacing);
    },

    getRealY:function(y) {
        return this.height/2 + (-1*y*this.spacing);
    },

    getMapX:function(x) {
        return (x - this.width/2) / this.spacing;
    },

    getMapY:function(y) {
        return -1*(y - this.height/2) / this.spacing;
    }

}

/* MOUSE */
function Cursor(vectron) {

    this.paper = vectron.paper;

    this.middleX = vectron.width / 2;
    this.middleY = vectron.height / 2;
    
    this.snappedMouseX = this.middleX - Math.round( this.middleX / vectron.spacing ) *
        vectron.spacing;
    this.snappedMouseY = this.middleY - Math.round( this.middleY / vectron.spacing ) *
        vectron.spacing;
    
    this.cursor = this.paper.path(
        ["M", this.snappedMouseX - 5, this.snappedMouseY - 5,
         'L', this.snappedMouseX - 1, this.snappedMouseY - 1,
         'M', this.snappedMouseX + 1, this.snappedMouseY + 1,
         'L', this.snappedMouseX + 5, this.snappedMouseY + 5]
    );
}  

Cursor.prototype = {
    constructor: Cursor,

    render:function(newX, newY, spacing) {
        
        this.cursor.remove();

        this.snappedMouseX = this.middleX - Math.round((this.middleX - newX) /
            spacing) * spacing;
        this.snappedMouseY = this.middleY - Math.round((this.middleY - newY) /
            spacing) * spacing;

        this.cursor = this.paper.path(
            ['M', this.snappedMouseX - 7, this.snappedMouseY,
             'L', this.snappedMouseX - 2, this.snappedMouseY,
             'M', this.snappedMouseX + 2, this.snappedMouseY,
             'L', this.snappedMouseX + 7, this.snappedMouseY,
             'M', this.snappedMouseX, this.snappedMouseY - 7,
             'L', this.snappedMouseX, this.snappedMouseY - 2,
             'M', this.snappedMouseX, this.snappedMouseY + 2,
             'L', this.snappedMouseX, this.snappedMouseY + 7]
        );

    }
}

function Aamap(vectron) {

    this._xml = '';
    this.objects = [new Zone(vectron, 0, 0, 1, "win")];
    this.currentObj = 0;

    this.paper = vectron.paper;
    this.canvas = vectron;
    this.active = false; // is a tool active?

}  

Aamap.prototype = {

    constructor: Aamap,

    render:function() {
        for(var i = 0; i < this.objects.length; i++) {
          this.objects[i].render();
          //$('#debug_box').append('<span class="debug_message">Default</span>');
        }
    }
}

function Zone(vectron, x, y, radius, type) {

    this._xml = '';
    this._type = type;
    this._x = x;
    this._y = y;
    this._radius = radius;

    this.canvas = vectron;
    this.paper = vectron.paper;

    this.render();
    $('#debug_stream').append('<span class="debug_message">'
        + 'Zone added at (' + this._x + ', ' + this._y + ')</span>');
    var elem = document.getElementById('debug_stream');
    elem.scrollTop = elem.scrollHeight;

}  

Zone.prototype = {

    constructor: Zone,

    render:function() {
        this.ob = this.paper.circle(this.canvas.getRealX(this._x),
            this.canvas.getRealY(this._y),
            this._radius*this.canvas.spacing).attr(
                {"stroke": "#FF0000", "fill": "#FFF", "fill-opacity": "0"}
            );
    }
}

function WallPoint(x, y) {
    this._x = x;
    this._y = y;
}

function Wall(vectron) {

    this._xml = '';
    this._points = [];

    this.canvas = vectron;
    this.paper = vectron.paper;

    this.pathArr = [];

    this.guideOb = this.paper.path();
    this.ob = this.paper.path();

    this.start();
    this.render();

    var elem = document.getElementById('debug_stream');
    elem.scrollTop = elem.scrollHeight;

}  

Wall.prototype = {

    constructor: Wall,

    start:function() {
        this.canvas.map.active = true;
        this.canvas.map.currentObj = this;
        this._points.push(
            new WallPoint(
                this.canvas.getMapX(this.canvas.cursor.snappedMouseX),
                this.canvas.getMapY(this.canvas.cursor.snappedMouseY))
        );
        this.render();
    },

    finish:function() {
        this.progress();
        if(this._points.length < 2) {

            this.ob.remove();
            this.guideOb.remove();
            this.canvas.map.active = false;
            this.canvas.map.currentObj = null;
            return;
        }
        var last = this._points[this._points.length-1];
        var secLast = this._points[this._points.length-2];
        if(last._x == secLast._x && last._y == secLast._y) {
            this._points.pop();
            $('#debug_stream').append('<span class="debug_message">Duplicate point at end removed.</span>');
            //update xml?
        }
        this.guideOb.remove();
        this.canvas.map.active = false;
        this.canvas.map.currentObj = null;
    },

    progress:function() {
        var newX = this.canvas.getMapX(this.canvas.cursor.snappedMouseX);
        var newY = this.canvas.getMapY(this.canvas.cursor.snappedMouseY);

        var prevPoint = this._points[this._points.length-1];

        if(newX == prevPoint._x && newY == prevPoint._y) {
            $('#debug_stream').append('<span class="debug_message">Duplicate point.</span>');
            return;
        }
        this._points.push( new WallPoint(newX, newY) );
        this.render();
    },

    guide:function() {
        this.guideOb.remove();
        var guideArr = []
        guideArr = guideArr.concat(
            [
             'M',
             this.canvas.getRealX(this._points[this._points.length-1]._x),
             this.canvas.getRealY(this._points[this._points.length-1]._y)
            ]
        );
        guideArr = guideArr.concat(
            [
             'L',
             this.canvas.cursor.snappedMouseX,
             this.canvas.cursor.snappedMouseY
            ]
        );
        this.guideOb = this.paper.path(guideArr).attr({stroke: "#aaa"});
    },

    render:function() {
        this.ob.remove();
        this.pathArr = [];
        for(var i = 0; i < this._points.length; i++) {
            if(i == 0) {
                this.pathArr = this.pathArr.concat(
                    [
                     'M',
                     this.canvas.getRealX(this._points[0]._x),
                     this.canvas.getRealY(this._points[0]._y)
                    ]
                );
            } else {
                this.pathArr = this.pathArr.concat(
                    [
                     'L',
                     this.canvas.getRealX(this._points[i]._x),
                     this.canvas.getRealY(this._points[i]._y)
                    ]
                );
            }
        } 
        this.ob = this.paper.path(this.pathArr).attr({stroke: "#333"});
        $('#debug_stream').append('<span class="debug_message">1' + this.pathArr + '</span>');
    }
}
