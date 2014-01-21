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
    vectron.map.wallTool.connect();

    window.onresize = function() {
        vectron.render();
    }

    $("#canvas_container").mousemove(function(event) {
        if(!vectron.map.active)
            return;
        event.pageX -= 50;
        vectron.cursor.render(event.pageX, event.pageY, vectron.map.zoom);

        if(vectron.map.currentTool instanceof ZoneTool) {
        	vectron.map.currentTool.guide();
        } else {
            if(vectron.map.spawnTool.active)
                vectron.map.currentTool.currentObj.guide();
        }

    });

    $("#canvas_container").mouseup(function(e) {
        e.preventDefault();
        if(!vectron.map.active)
            return;

        if(vectron.map.currentTool instanceof WallTool) {

        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.progress();
            else
            	vectron.map.currentTool.start();

        } else if(vectron.map.currentTool instanceof ZoneTool) {

        	vectron.map.currentTool.complete();

        } else if(vectron.map.currentTool instanceof SpawnTool) {

           if(vectron.map.spawnTool.active)
                vectron.map.currentTool.complete();
            else
                vectron.map.currentTool.start();
        }

    }); 

    $("#canvas_container").dblclick(function(e) {
        e.preventDefault();
        if(!vectron.map.active)
            return;
        if(vectron.map.currentTool instanceof WallTool) {
            if(vectron.map.wallTool.active)
                vectron.map.currentTool.complete();
        }

    });

    // TOOLBAR

    $("#toolbar-gui-toggle").mouseup(function(e) {
        if(!vectron.gui.active) {
            vectron.gui.show(); // sets active state
            $("#toolbar-gui-toggle").html("&laquo;");
        } else {
            vectron.gui.hide();
            $("#toolbar-gui-toggle").html("&raquo;");
        }
        vectron.gui.writeLog('GUI TOGGLE');

    });

    $("#toolbar-toolWall").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(vectron.map.currentTool instanceof WallTool) {
            return;
        } else {
            vectron.map.wallTool.connect();
            vectron.gui.writeLog('Wall Tool Connected.');
        }
    });

        //ZONES

    $("#toolbar-toolZone-death").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(!(vectron.map.currentTool instanceof ZoneTool)) {
            vectron.map.zoneTool.connect();
        }
        vectron.map.zoneTool.type = 0;
        vectron.map.currentTool.guide();
        vectron.gui.writeLog('DeathZone selected.');
    });

    $("#toolbar-toolZone-win").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(!(vectron.map.currentTool instanceof ZoneTool)) {
            vectron.map.zoneTool.connect();
        }
        vectron.map.zoneTool.type = 1;
        vectron.map.currentTool.guide();
        vectron.gui.writeLog('WinZone selected.');

    });

    $("#toolbar-toolZone-target").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(!(vectron.map.currentTool instanceof ZoneTool)) {
            vectron.map.zoneTool.connect();
        }
        vectron.map.zoneTool.type = 2;
        vectron.map.currentTool.guide();
        vectron.gui.writeLog('TargetZone selected.');

    });

    $("#toolbar-toolZone-fortress").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(!(vectron.map.currentTool instanceof ZoneTool)) {
            vectron.map.zoneTool.connect();
        }
        vectron.map.zoneTool.type = 4;
        vectron.map.currentTool.guide();
        vectron.gui.writeLog('FortressZone selected.');

    });

    $("#toolbar-toolZone-rubber").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(!(vectron.map.currentTool instanceof ZoneTool)) {
            vectron.map.zoneTool.connect();
        }
        vectron.map.zoneTool.type = 3;
        vectron.map.currentTool.guide();
        vectron.gui.writeLog('RubberZone Selected.');

    });

        // SPAWN
    $("#toolbar-toolSpawn").mouseup(function(e) {
        if(!vectron.map.active)
            return;
        if(vectron.map.currentTool instanceof SpawnTool) {
            return;
        } else {
            vectron.map.spawnTool.connect();
            vectron.gui.writeLog('Spawn Tool Connected.');
        }
    });

    $("#toolbar-toolUnlock").mouseup(function(e) {
        vectron.cursor.snap = true;
        $('#toolbar-toolUnlock-list').css('display','none');
        $('#toolbar-toolLock-list').css('display','block');
    });

    $("#toolbar-toolLock").mouseup(function(e) {
        vectron.cursor.snap = false;
        $('#toolbar-toolLock-list').css('display','none');
        $('#toolbar-toolUnlock-list').css('display','block');
    });

        //cancel
    $("#toolbar-disconnect").mouseup(function(e) {
        if(vectron.map.currentTool instanceof ZoneTool) {
            vectron.map.remove();
        } else if(vectron.map.currentTool instanceof WallTool) {
            if(vectron.map.currentTool.active) {
                vectron.map.currentTool.disconnect();
                vectron.map.wallTool.connect();
            } else {
                vectron.map.remove();
            }
        } else if(vectron.map.currentTool instanceof SpawnTool) {
            if(vectron.map.currentTool.active) {
                vectron.map.currentTool.disconnect();
                vectron.map.wallTool.connect();
            } else {
                vectron.map.remove();
            }
        }
    });

    $("#toolbar-toolZoomIn").mousedown(function(e) {
        if(vectron.map.zoom < 60) {
            vectron.map.zoom += 1;
        }
        vectron.render();
    });

    $("#toolbar-toolZoomOut").mouseup(function(e) {
        if(vectron.map.zoom > 5) {
            vectron.map.zoom -= 1;
        }
        vectron.render();
    });

    Mousetrap.bind('shift+w', function(e) {
        if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof WallTool) {
        	if(vectron.map.wallTool.active)
            	vectron.map.currentTool.complete();
        
        }
    });

     Mousetrap.bind('shift+z', function(e) {
        if(!vectron.map.active)
            return;
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
        if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius < 30) {
	    		vectron.map.zoneTool.radius += 0.1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('+', function(e) {
    	if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius < 30) {
	    		vectron.map.zoneTool.radius = Math.floor(vectron.map.zoneTool.radius) + 1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('-', function(e) {
        if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius > 0) {
	    		vectron.map.zoneTool.radius -= 0.1;
	    		vectron.map.currentTool.guide();
	    	}
    	}
    }, 'keydown');

    Mousetrap.bind('_', function(e) {
    	if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		if(vectron.map.zoneTool.radius > 0) {
	    		vectron.map.zoneTool.radius = Math.floor(vectron.map.zoneTool.radius) - 1;
	    		vectron.map.currentTool.guide();
    		}
    	}
    }, 'keydown');

    Mousetrap.bind('w', function(e) {
        if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof WallTool) {
    		return;
    	} else {
    		vectron.map.wallTool.connect();
    	}
    }, 'keydown');

    Mousetrap.bind('z', function(e) {
        if(!vectron.map.active)
            return;
    	if(vectron.map.currentTool instanceof ZoneTool) {
    		return;
    	} else {
    		vectron.map.zoneTool.connect();
    	}
    }, 'keydown');

    Mousetrap.bind('right', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panX -= 1;
        vectron.render();
    });
    Mousetrap.bind('left', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panX += 1;
        vectron.render();
    });
    Mousetrap.bind('up', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panY -= 1;
        vectron.render();
    });
    Mousetrap.bind('down', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panY += 1;
        vectron.render();
    });
    Mousetrap.bind('shift+space', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panY = 0;
        vectron.map.panX = 0;
        vectron.render();
    });

    Mousetrap.bind('space', function(e) {
        if(!vectron.map.active)
            return;
        vectron.map.panY = -1*vectron.map.mapY(vectron.cursor.realY);
        vectron.map.panX = -1*vectron.map.mapX(vectron.cursor.realX);
        vectron.render();
    });

}  

