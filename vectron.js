window.onload = function() {
	var width = $("#canvas_container").width();
	var height = $("#canvas_container").height();
    var paper = new Raphael(document.getElementById('canvas_container'),
        width, height);

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

function grid_draw(canvas, width, height, gridSpacing) {
	gridArray = [];
	for(var i=width/2; i < width; i+= gridSpacing) {
    	gridArray = gridArray.concat(["M", i, height, "L", i, 0]);
        //paper.path(
        	//["M", i, height, "L", i, 0]
        //).attr("stroke", '#d6d6ec');
    }

    for(var i=width/2; i > 0; i -= gridSpacing) {
        //paper.path(
        gridArray = gridArray.concat(["M", i, height, "L", i, 0]);
        //).attr("stroke", '#d6d6ec');
    }

    for(var i=height/2; i < height; i+= gridSpacing) {
        //paper.path(
        gridArray = gridArray.concat(["M", width, i, "L", 0, i]);
        //).attr("stroke", '#d6d6ec');
    }

    for(var i=height/2; i > 0; i -= gridSpacing) {
        //paper.path(
        gridArray = gridArray.concat(["M", width, i, "L", 0, i]);
        //).attr("stroke", '#d6d6ec');
    }
   	
   	return canvas.path(gridArray).attr("stroke", "#d6d6ec");
}
