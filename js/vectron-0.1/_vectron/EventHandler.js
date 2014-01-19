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

function EventHandler(vectron) {

    //setup key handling here also.

    window.onresize = function() {
        vectron.render();
    }

    vectron.map.zoneTool.connect();

    $("#canvas_container").mousemove(function(event) {
        event.pageX -= 60;
        vectron.cursor.render(event.pageX, event.pageY, vectron.map.zoom);

        if(vectron.map.currentTool instanceof WallTool) {
        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.currentObj.guide();

        } else if(vectron.map.currentTool instanceof ZoneTool) {
        	vectron.map.currentTool.guide();
        }

    });

    $("#canvas_container").mouseup(function(e) {

        e.preventDefault();

        if(vectron.map.currentTool instanceof WallTool) {
        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.progress();
            else
            	vectron.map.currentTool.start();

        } else if(vectron.map.currentTool instanceof ZoneTool) {

        	vectron.map.currentTool.complete();
        }

    }); 

    // TOOLBAR

    $("#toolbar-gui-toggle").mouseup(function(e) {
        $("#control_box").toggle();
        vectron.gui.writeLog('GUI TOGGLE');

    });

    $("#toolbar-toolWall").mouseup(function(e) {
        vectron.gui.writeLog('WALL TOOL');

    });

        //ZONES

    $("#toolbar-toolZone-death").mouseup(function(e) {
        vectron.gui.writeLog('ZONE DEATH');
    });

    $("#toolbar-toolZone-win").mouseup(function(e) {
        vectron.gui.writeLog('ZONE WIN');

    });

    $("#toolbar-toolZone-target").mouseup(function(e) {
        vectron.gui.writeLog('ZONE TARGET');

    });

    $("#toolbar-toolZone-fortress").mouseup(function(e) {
        vectron.gui.writeLog('ZONE FORT');

    });

    $("#toolbar-toolZone-rubber").mouseup(function(e) {
        vectron.gui.writeLog('ZONE RUBBER');

    });

        // SPAWN
    $("#toolbar-toolSpawn").mouseup(function(e) {

        vectron.gui.writeLog('SPAWN TOOL');
    });
        //cancel
    $("#toolbar-disconnect").mouseup(function(e) {
        vectron.gui.writeLog('CANCEL');

    });


    $(window).dblclick(function(e) {
    	e.preventDefault();
        if(vectron.map.currentTool instanceof WallTool) {
        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.complete();
        }

    });

    Mousetrap.bind('shift+w', function(e) {
    	if(vectron.map.currentTool instanceof WallTool) {
        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.complete();
        
        }
    });

     Mousetrap.bind('shift+z', function(e) {
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		vectron.map.zoneTool.type += 1;
        	if(vectron.map.zoneTool.type > 4) {
        		vectron.map.zoneTool.type = 0;
        	}
        	vectron.gui.writeLog('Zone Tool Toggled: '
        		+ vectron.map.zoneTool.typeArray[vectron.map.zoneTool.type][0]);
        	vectron.map.currentTool.guide();
    	}
    });

    Mousetrap.bind('=', function(e) {
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius < 30) {
	    		vectron.map.zoneTool.radius += 0.1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('+', function(e) {
    	if (e.preventDefault) {
        	e.preventDefault();
	    } else {
	        // internet explorer
	        e.returnValue = false;
	    }
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius < 30) {
	    		vectron.map.zoneTool.radius = Math.floor(vectron.map.zoneTool.radius) + 1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('-', function(e) {
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius > 0) {
	    		vectron.map.zoneTool.radius -= 0.1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('_', function(e) {
    	if (e.preventDefault) {
        	e.preventDefault();
	    } else {
	        // internet explorer
	        e.returnValue = false;
	    }
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius > 0) {
	    		vectron.map.zoneTool.radius = Math.floor(vectron.map.zoneTool.radius) - 1;
	    		vectron.map.currentTool.guide();
    		}
    	}
    }, 'keydown');

    Mousetrap.bind('w', function(e) {
    	if(vectron.map.currentTool instanceof WallTool) {
    		return;
    	} else {
    		//vectron.map.currentTool.disconnect();
    		vectron.map.wallTool.connect();
    	}
    }, 'keydown');

    Mousetrap.bind('z', function(e) {
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		return;
    	} else {
    		//vectron.map.currentTool.disconnect();
    		vectron.map.zoneTool.connect();
    	}
    }, 'keydown');

    Mousetrap.bind('right', function(e) {
        vectron.map.panX -= 1;
        vectron.render();
    });
    Mousetrap.bind('left', function(e) {
        vectron.map.panX += 1;
        vectron.render();
    });
    Mousetrap.bind('up', function(e) {
        vectron.map.panY -= 1;
        vectron.render();
    });
    Mousetrap.bind('down', function(e) {
        vectron.map.panY += 1;
        vectron.render();
    });
    Mousetrap.bind('shift+space', function(e) {
        vectron.map.panY = 0;
        vectron.map.panX = 0;
        vectron.render();
    });

    Mousetrap.bind('space', function(e) {
        vectron.map.panY = -1*vectron.map.mapY(vectron.cursor.realY);
        vectron.map.panX = -1*vectron.map.mapX(vectron.cursor.realX);
        vectron.render();
    });

    
}  

