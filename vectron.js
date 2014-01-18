//********//********//********//********//********//********//********//********
window.onload = function() {

    var vectron = new Canvas();

    vectron.render( 10 );

    window.onresize = function() {
        vectron.render();
    }
    
}


function Canvas() {
    this.width = $("#canvas_container").width();
    this.height = $("#canvas_container").height();
    this.paper = new Raphael(document.getElementById('canvas_container'), 
        this.width, this.height);
    this.spacing = 10;
    this.map = new Aamap();
}  

Canvas.prototype = {

    constructor: Canvas,

    render:function() {
        this.paper.clear();
        this.width = $("#canvas_container").width();
        this.height = $("#canvas_container").height();
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
    }
}



function Aamap() {
    this._xml = '';
    this.objects = [1];
}  

Aamap.prototype = {

    constructor: Aamap,

    render:function() {
        for(var i = 0; i < this.objects.length; i++) {
            //this.objects[i].render();
          $('#debug_box').append('<span class="debug_message">Default</span>');
        }
    }
}


    
    
    /*
    instead of this ^^^^^
    we have each object that needs rendering have a render function, then in the resize callback, we just tell grid to render itself
    and store the rendered object (which can be .remove()'d) in the like, Grid.g object.
    */
    


/*
    var middleX = $("#canvas_container").width()/2;
    var middleY = $("#canvas_container").height()/2;

    var snappedMouseX = middleX;
    var snappedMouseY = middleY;

    var gridSpacing = 10;

    var cursor = paper.path(
        ["M", middleX - 5, middleY - 5,
         'L', middleX - 1, middleY - 1,
         'M', middleX + 1, middleY + 1,
         'L', middleX + 5, middleY + 5]
    );

    var guide = paper.circle(snappedMouseX, snappedMouseY, 20).attr("stroke",
        "#FF0000").attr("stroke-dasharray", "-");

    g = grid_draw(paper, width, height, gridSpacing);
    g.click(function(event) {
        console.log(this);
        console.log(event.x, event.y);
    });
    paper.path(gridArray).attr("stroke", "#d6d6ec");
    var dz = paper.circle($("#canvas_container").width()/2, 
        $("#canvas_container").height()/2, 20).attr("stroke", "#FF0000");

    //dz.remove();
    window.onresize = function() {
        paper.clear();
        
        width = $("#canvas_container").width();
        height = $("#canvas_container").height();

        middleX = $("#canvas_container").width()/2;
        middleY = $("#canvas_container").height()/2;

        paper.setSize(width, height);

        g = grid_draw(paper, width, height, gridSpacing);
        g.click(function(event) {
            console.log(this);
            console.log(event.x, event.y);
        });
        //paper.circle($("#canvas_container").width()/2, 
            //$("#canvas_container").height()/2, 20).attr("stroke", "#FF0000");
    }

    $("#canvas_container").on("click", function(e) {

            e.preventDefault();
            var x0 = e.pageX, y0 = e.pageY;
            var x = x0, y = y0;
            var elem = paper.getElementByPoint(x0, y0);
            paper.circle(snappedMouseX, snappedMouseY, 20).attr("stroke",
                "#FF0000");
            console.log("WAWA");
    });

    $("#canvas_container").mousemove(function(event) {
        
        cursor.remove();
        guide.remove();

        snappedMouseX = middleX - Math.round((middleX - event.pageX) /
            gridSpacing) * gridSpacing;
        snappedMouseY = middleY - Math.round((middleY - event.pageY) /
        gridSpacing) * gridSpacing;

        cursor = paper.path(
            ['M', snappedMouseX - 7, snappedMouseY,
             'L', snappedMouseX - 2, snappedMouseY,
             'M', snappedMouseX + 2, snappedMouseY,
             'L', snappedMouseX + 7, snappedMouseY,
             'M', snappedMouseX, snappedMouseY - 7,
             'L', snappedMouseX, snappedMouseY - 2,
             'M', snappedMouseX, snappedMouseY + 2,
             'L', snappedMouseX, snappedMouseY + 7]
        );
        guide = paper.circle(snappedMouseX, snappedMouseY, 20).attr("stroke",
            "#FF0000").attr("stroke-dasharray", "--..");
    });
}


*/