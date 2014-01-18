<html>  
    <head>  
        <title>JavaScript Learning</title>
        <script type="text/javascript" src="https://code.jquery.com/jquery.js"></script>
        <script type="text/javascript" src="./raphael-min.js"></script>  
        <script type="text/javascript" src="./vectron.js"></script> 
        <style type="text/css">

            #canvas_container {  
                width: 100%;
                height: 100%;  
                border: 1px solid #aaa;  
            }

            html, body { margin:0; }

            body.noscroll {
			    position: fixed; 
			    width: 100%;
			    height:100%;
			}

            #debug_box {
                position:absolute;
                bottom:0;
                right:0;
                width:300px; 
                height:140px; 
                border-top-left-radius:6px;
                border-top:1px solid #1b1b1b;
                border-left:1px solid #1b1b1b;
                background:rgba(0, 0, 0, .8);
            }

        </style>  
    </head>  
    <body class="noscroll">  
        <div id="canvas_container"></div>
        <div id="debug_box"></div>
    </body>  
</html>