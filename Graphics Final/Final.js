/*
COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Computer Graphics Fianl Project
Author. Angelo Indre
        adi19@uakron.edu
Purpose. Create a 3D WebGL videogame
*/

/*
    Final.js

    graphics making file for CG Final Project
*/

var gl;

// load the buffers using these vars
var vertices = [];
var colors = [];

var pointTransLoc;

var colorModLoc;

var molderLoc;

var up = false;

var left = false;

var down = false;

var right = false;

var lr = 0;

var ud = 0;

var served = [];

var orderTaken = [];

var cXPos = [];

var cYPos = [];

var cOrder = [];

var currentKey = 1;

var holdingCroissant = false;

var holdingCoffee = false;

var inLobbyCounter = 1;

window.onload = function init(){
    var canvas = document.getElementById("gl-canvas");
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" );
    }

    //  Configure WebGL

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    
    //  Load shaders and initialize attribute buffers
    
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Make block
    makeSquare();

    // Load the data into the GPU
    
    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

    var color = gl.getAttribLocation( program, "color" );
    gl.vertexAttribPointer( color, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( color );

    var bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    // Associate out shader variables with our data buffer
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    // Moving Controls
    document.addEventListener("keydown", function(event){
        if (event.keyCode == 87) {              // W
            up = true;
        } else if (event.keyCode == 65) {       // A
            left = true;
        } else if (event.keyCode == 83) {       // S
            down = true;
        } else if (event.keyCode == 68) {       // D
            right = true;
        } else if (event.keyCode == 81) {
            self.close();
        }
    });

    document.addEventListener("keyup", function(event){
        if (event.keyCode == 87) {              // W
            up = false;
        } else if (event.keyCode == 65) {       // A
            left = false;
        } else if (event.keyCode == 83) {       // S
            down = false;
        } else if (event.keyCode == 68) {       // D
            right = false;
        }
    });

    // orthographic aid for transformations
    orthoMat = ortho(-100, 100, -100, 100, -100, 100);
    gl.uniformMatrix4fv(gl.getUniformLocation(program, "ortho"), false, flatten(orthoMat));

    pointTransLoc = gl.getUniformLocation(program, "pointTranslate");
    colorModLoc = gl.getUniformLocation(program, "colorMod");
    molderLoc = gl.getUniformLocation(program, "molder");

    // Customers
    cXPos.push(0);
    cYPos.push(0);
    orderTaken.push(false);
    served.push(true); 
    // Orders: 0 = croissant, 1 = coffee, 2 = both
    cOrder.push(0);

    for (var i = 1; i <= 20; i++) {
        cOrder.push(Math.floor(Math.random() * 3));
        cXPos.push(0);
        cYPos.push(0);
        orderTaken.push(false);
        served.push(false);
    }

    // Finally with everything linked and filled, we start manipulating and drawing
    render();
};

function makeSquare() { 
    vertices.push(
        0, 0, 0, 1,
        1, 0, 0, 1,
        1, 1, 0, 1,
        0, 1, 0, 1,
        0, 0, 0, 1,
        1, 1, 0, 1,

    );
    colors.push(
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1
    );
}

function makeMolder(xl, yl, zl) {
    var mold = mat4(1);
    mold[0][0] = xl;
    mold[1][1] = yl;
    mold[2][2] = zl;
    return mold;
}

function instantiateStensil( newLength, newHeight, newRed, newGreen, newBlue, newX, newY) {
    gl.uniform4fv(colorModLoc, vec4(newRed, newGreen, newBlue, 1))
    gl.uniform4fv(pointTransLoc, vec4(newX, newY, 0, 0));
    gl.uniformMatrix4fv(molderLoc, false, flatten(makeMolder(newLength, newHeight, 1)));
    gl.drawArrays( gl.TRIANGLES, 0, 6 );
}

function drawCoffeeShop() {
    
    // Backdrop
    instantiateStensil(1000, 1000, 1, .9, .6, -100, -100);
    tileFloor();

    // Seating
    makeTableAndChairs(-40, -90);
    makeTableAndChairs(-85, -70);
    makeTableAndChairs(5, -70);
    makeTableAndChairs(50, -90);

    // Menu
    menuFrame();
    pastry(1, 1, 4, 66);
    coffeCup(1, 1, 42, 73);
}

function person(xPos, yPos, r, g, b) {
    instantiateStensil(2, 1, 0, 0, 0, 0 + xPos, 0 + yPos);
    instantiateStensil(2, 1, 0, 0, 0, 6 + xPos, 0 + yPos);
    instantiateStensil(2, 1, 1, 1, 1, 0 + xPos, 1 + yPos);
    instantiateStensil(2, 1, 1, 1, 1, 6 + xPos, 1 + yPos);
    instantiateStensil(4, 1, 0, 0, 0, -1 + xPos, 2 + yPos);
    instantiateStensil(4, 1, 0, 0, 0, 5 + xPos, 2 + yPos);
    instantiateStensil(10, 1, 0, 0, 0, -1 + xPos, 3 + yPos);
    instantiateStensil(10, 1, 0, 0, 0, -1 + xPos, 4 + yPos);
    instantiateStensil(10, 1, 0, 0, 0, -1 + xPos, 5 + yPos);
    instantiateStensil(10, 1, 0, 0, 0, -1 + xPos, 6 + yPos);
    shirt(xPos, yPos, r, g, b);
    instantiateStensil(1, 2, 0.8, 0.6, 0.6, -2 + xPos, 9 + yPos);
    instantiateStensil(1, 2, 0.8, 0.6, 0.6, 9 + xPos, 9 + yPos);
    instantiateStensil(6, 1, 0.8, 0.6, 0.6, 1 + xPos, 13 + yPos);
    instantiateStensil(8, 6, 0.8, 0.6, 0.6, 0 + xPos, 14 + yPos);
    instantiateStensil(1, 1, 0, 0, 0, 2 + xPos, 17 + yPos);
    instantiateStensil(1, 1, 1, 1, 1, 1 + xPos, 17 + yPos);
    instantiateStensil(1, 1, 0, 0, 0, 5 + xPos, 17 + yPos);
    instantiateStensil(1, 1, 1, 1, 1, 6 + xPos, 17 + yPos);
    instantiateStensil(4, 1, 0, 0, 0, 2 + xPos, 15 + yPos);
    instantiateStensil(8, 1, 0, 0, 0, 0 + xPos, 20 + yPos)

}

function shirt(xPos, yPos, r, g, b) {
    instantiateStensil(10, 1, r, g, b, -1 + xPos, 7 + yPos);
    instantiateStensil(10, 1, r, g, b, -1 + xPos, 8 + yPos);
    instantiateStensil(10, 1, r, g, b, -1 + xPos, 9 + yPos);
    instantiateStensil(10, 1, r, g, b, -1 + xPos, 10 + yPos);
    instantiateStensil(12, 1, r, g, b, -2 + xPos, 11 + yPos);
    instantiateStensil(12, 1, r, g, b, -2 + xPos, 12 + yPos);
}

function trashCan() {
    instantiateStensil(11, 1, 0, 0, 0, -30, 43);
    instantiateStensil(1, 7, 0, 0, 0, -31, 44);
    instantiateStensil(1, 7, 0, 0, 0, -19, 44);
    instantiateStensil(1, 7, 0, 0, 0, -32, 51);
    instantiateStensil(1, 7, 0, 0, 0, -18, 51);
    instantiateStensil(1, 3, 0, 0, 0, -33, 58);
    instantiateStensil(1, 3, 0, 0, 0, -17, 58);
    instantiateStensil(15, 1, 0, 0, 0, -32, 60);
    instantiateStensil(11, 16, 0.6, 0.6, 0.6, -30, 44);
    instantiateStensil(1, 9, 0.6, 0.6, 0.6, -31, 51);
    instantiateStensil(1, 2, 0.6, 0.6, 0.6, -32, 58);
    instantiateStensil(1, 9, 0.6, 0.6, 0.6, -19, 51);
    instantiateStensil(1, 2, 0.6, 0.6, 0.6, -18, 58);
    instantiateStensil(1, 5, 0, 0, 0, -25, 50);
    instantiateStensil(1, 5, 0, 0, 0, -22, 50);
    instantiateStensil(1, 5, 0, 0, 0, -28, 50);
}

function menuFrame() {

    // Croissant Frame
    instantiateStensil(25, 30, 1, 1, .8, 0, 60);
    instantiateStensil(1, 30, .3, .2, .1, -1, 60);
    instantiateStensil(27, 1, .3, .2, .1, -1, 59);
    instantiateStensil(1, 30, .3, .2, .1, 25, 60);
    instantiateStensil(27, 1, .3, .2, .1, -1, 90);

    // Coffee Frame
    instantiateStensil(25, 30, 1, 1, .8, 36, 60);
    instantiateStensil(1, 30, .3, .2, .1, 35, 60);
    instantiateStensil(27, 1, .3, .2, .1, 35, 59);
    instantiateStensil(1, 30, .3, .2, .1, 61, 60);
    instantiateStensil(27, 1, .3, .2, .1, 35, 90);
}

function makeCounterWall() {
    instantiateStensil(60, 8, .4, .2, .1, -70, -20); // Main Wall
    instantiateStensil(2, 8, .3, .1, .05, -10, -18); //     //
    instantiateStensil(2, 8, .3, .1, .05, -8, -16);  //     // diagonal
    instantiateStensil(2, 8, .3, .1, .05, -6, -14);  //     //
    instantiateStensil(25, 8, .4, .2, .1, -4, -12);  // register spot
    instantiateStensil(20, 8, 0.2, 0.05, 0.1, 21, -12); // pastry case
    instantiateStensil(200, 8, .4, .2, .1, 41, -12);     // counter end
}

function makeCounterTopFront() {
    instantiateStensil(60, 12, .9, .9, .8, -70, -12);
    instantiateStensil(2, 12, .9, .9, .8, -10, -10);
    instantiateStensil(2, 12, .9, .9, .8, -8, -8);
    instantiateStensil(2, 12, .9, .9, .8, -6, -6);
    instantiateStensil(650, 12, .9, .9, .8, -4, -4);
}

function makeCounterTopSides() {
    instantiateStensil(12, 50, .9, .9, .8, 88, 8);
    instantiateStensil(12, 56, .9, .9, .8, -70, 0);
}

function makeTableAndChairs(x, y) {
    //table
    instantiateStensil(20, 15, 0.4, 0.3, 0.2, x, y);        //top
    instantiateStensil(2, 5, 0.3, 0.2, 0.1, x, y - 5);      //left leg
    instantiateStensil(2, 5, 0.3, 0.2, 0.1, x + 18, y - 5); //right leg

    //chair (left)
    instantiateStensil(6, 4, .3, .2, .1, x - 6, y + 3); //seat
    instantiateStensil(1, 3, .25, .15, .1, x - 6, y); //backleg
    instantiateStensil(1, 6, .3, .2, .1, x - 6, y + 7); //back

    //chair (right)
    instantiateStensil(6, 4, .3, .2, .1, x + 20, y + 3);
    instantiateStensil(1, 3, .25, .15, .1, x + 25, y);
    instantiateStensil(1, 6, .3, .2, .1, x + 25, y + 7);
}

function make1Tile(x, y) {
    instantiateStensil(.5, 5, 0.5, 0.5, 0.5, x, y - 2.25);
    instantiateStensil(7, .5, 0.5, 0.5, 0.5, x - 2.25, y);
}

function tileFloor() {    
    instantiateStensil(200, 147.5, .75, .7, .7, -100, -100);
    for (var i = -100; i < 100; i += 7) {
        for (var j = -100; j < 50; j += 5) {
            make1Tile(i, j);
        }
    }
}

function pastry(lengthCoeff, widthCoeff, xOffset, yOffset) {
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 0 + xOffset, 0 + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 2 * lengthCoeff + xOffset, 1 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, -1 * lengthCoeff + xOffset, 1 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 0 + xOffset, 1 * widthCoeff + yOffset);
    instantiateStensil(4 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, -1 * lengthCoeff + xOffset, 2 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, -2 * lengthCoeff + xOffset, 2 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 3 * lengthCoeff + xOffset, 2 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, -2 * lengthCoeff + xOffset, 3 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, -1 * lengthCoeff + xOffset, 3 * widthCoeff + yOffset);
    instantiateStensil(5 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 0 * lengthCoeff + xOffset, 3 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, -1 * lengthCoeff + xOffset, 4 * widthCoeff + yOffset);
    instantiateStensil(4 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 0 * lengthCoeff + xOffset, 6 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, .8, .7, .6, -1 * lengthCoeff + xOffset, 5 * widthCoeff + yOffset);
    instantiateStensil(4 * lengthCoeff, 2 * widthCoeff, .8, .7, .6, 0 * lengthCoeff + xOffset, 4 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 4 * lengthCoeff + xOffset, 4 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 5 * lengthCoeff + xOffset, 4 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 4 * lengthCoeff + xOffset, 5 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, -1 * lengthCoeff + xOffset, 7 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, 0, 0, 0, -2 * lengthCoeff + xOffset, 5 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, 0, 0, 0, -2 * lengthCoeff + xOffset, 8 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, 0, 0, 0, -1 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 3 * widthCoeff, 0, 0, 0, 0 * lengthCoeff + xOffset, 12 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 1 * lengthCoeff + xOffset, 15 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 2 * lengthCoeff + xOffset, 16 * widthCoeff + yOffset);
    instantiateStensil(6 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 3 * lengthCoeff + xOffset, 17 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 9 * lengthCoeff + xOffset, 18 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 12 * lengthCoeff + xOffset, 17 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 13 * lengthCoeff + xOffset, 16 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 16 * lengthCoeff + xOffset, 15 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, 0, 0, 0, 17 * lengthCoeff + xOffset, 13 * widthCoeff + yOffset);
    instantiateStensil(4 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 13 * lengthCoeff + xOffset, 12 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 6 * widthCoeff, 0, 0, 0, 13 * lengthCoeff + xOffset, 11 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 12 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 5 * widthCoeff, 0, 0, 0, 11 * lengthCoeff + xOffset, 9 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 10 * lengthCoeff + xOffset, 14 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, 0, 0, 0, 9 * lengthCoeff + xOffset, 15 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 10 * lengthCoeff + xOffset, 8 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 7 * lengthCoeff + xOffset, 7 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 3 * widthCoeff, 0, 0, 0, 7 * lengthCoeff + xOffset, 6 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 5 * lengthCoeff + xOffset, 9 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 3 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, 0, 0, 0, 1 * lengthCoeff + xOffset, 11 * widthCoeff + yOffset);
    instantiateStensil(5 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 0 * lengthCoeff + xOffset, 7 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, .8, .7, .6, -1 * lengthCoeff + xOffset, 8 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 2 * widthCoeff, .8, .7, .6, 0 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 1 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 4 * lengthCoeff + xOffset, 6 * widthCoeff + yOffset);
    instantiateStensil(6 * lengthCoeff, 6 * widthCoeff, .8, .7, .6, 3 * lengthCoeff + xOffset, 11 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 1 * lengthCoeff + xOffset, 12 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 4 * widthCoeff, .8, .7, .6, 2 * lengthCoeff + xOffset, 12 * widthCoeff + yOffset);
    instantiateStensil(5 * lengthCoeff, 5 * widthCoeff, .8, .7, .6, 5 * lengthCoeff + xOffset, 10 * widthCoeff + yOffset);
    instantiateStensil(4 * lengthCoeff, 5 * widthCoeff, .8, .7, .6, 7 * lengthCoeff + xOffset, 9 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 8 * lengthCoeff + xOffset, 8 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 12 * lengthCoeff + xOffset, 11 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 11 * lengthCoeff + xOffset, 14 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 3 * widthCoeff, .8, .7, .6, 10 * lengthCoeff + xOffset, 15 * widthCoeff + yOffset);
    instantiateStensil(1 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 9 * lengthCoeff + xOffset, 17 * widthCoeff + yOffset);
    instantiateStensil(3 * lengthCoeff, 2 * widthCoeff, .8, .7, .6, 14 * lengthCoeff + xOffset, 13 * widthCoeff + yOffset);
    instantiateStensil(2 * lengthCoeff, 1 * widthCoeff, .8, .7, .6, 14 * lengthCoeff + xOffset, 15 * widthCoeff + yOffset);

}

function coffeCup(w, l, x, y) {
    instantiateStensil(11 * w, 4 * l, 1, 1, 1, 0 * w + x, 0 * l + y);
    instantiateStensil(11 * w, 1 * l, .9, .9, .9, 0 * w + x, -1 * l + y);
    instantiateStensil(9 * w, 1 * l, .9, .9, .9, 1 * w + x, -2 * l + y);
    instantiateStensil(7 * w, 1 * l, .9, .9, .9, 2 * w + x, -3 * l + y);
    instantiateStensil(11 * w, 1 * l, .67, .5, .35, 0 * w + x, 4 * l + y);
    instantiateStensil(11 * w, 1 * l, .77, .6, .45, 0 * w + x, 5 * l + y);
    instantiateStensil(13 * w, 1 * l, 0, 0, 0, -1 * w + x, 6 * l + y);
    instantiateStensil(1 * w, 7 * l, 0, 0, 0, -1 * w + x, -1 * l + y);
    instantiateStensil(1 * w, 7 * l, 0, 0, 0, 11 * w + x, -1 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 10 * w + x, -2 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 9 * w + x, -3 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 0 * w + x, -2 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 1 * w + x, -3 * l + y);
    instantiateStensil(13 * w, 1 * l, 0, 0, 0, -1 * w + x, -4 * l + y);
    instantiateStensil(9 * w, 1 * l, 0, 0, 0, 1 * w + x, -5 * l + y);
    instantiateStensil(2 * w, 1 * l, 0, 0, 0, 12 * w + x, 0 * l + y);
    instantiateStensil(1 * w, 5 * l, 0, 0, 0, 14 * w + x, 1 * l + y);
    instantiateStensil(3 * w, 1 * l, 0, 0, 0, 12 * w + x, 5 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 2 * w + x, 8 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 5 * w + x, 8 * l + y);
    instantiateStensil(1 * w, 1 * l, 0, 0, 0, 8 * w + x, 8 * l + y);
    instantiateStensil(1 * w, 2 * l, 0, 0, 0, 3 * w + x, 9 * l + y);
    instantiateStensil(1 * w, 2 * l, 0, 0, 0, 6 * w + x, 9 * l + y);
    instantiateStensil(1 * w, 2 * l, 0, 0, 0, 9 * w + x, 9 * l + y);




}

// This would be easier to implement with a priority queue and customer Objects.
// But the due date is approaching and I don't know how to do that in js.
function customer(key) {

    // Go to place order
    if (!orderTaken[key])  { 
        if (cXPos[key] > -53) {
            cXPos[key] -= 0.5
        }
    }

    // Go to wait for order
    else if (cYPos[key]  > -20 && cXPos[key] > -140) {
        cYPos[key] -= 0.5;
        cXPos[key] -= 0.5;
    } else if (cXPos[key]  > -163) {
        cXPos[key] -= 0.5;
    } else if (cYPos[key] < 40) {
        cYPos[key] += 0.5;
    }

    // Only show the customer if they have yet to be served
    if (!served[key]) {
        person(80 + cXPos[key], -20 + cYPos[key], 1, 0, 0);
    }

}

function takeOrder() {
    if (cXPos[currentKey] == -53 && cYPos[currentKey] == 0 && served[currentKey - 1] == true) {
        orderTaken[currentKey] = true;
        currentKey++;
    }
}

function serve() {
    if (cXPos[currentKey - 1] == -163 && cYPos[currentKey - 1] == 40) {
        served[currentKey - 1] = true;
        holdingCroissant = false;
        holdingCoffee = false;
    }
}

function player() {
    // Player

    // Basic moving space
    if (up) {
        if (ud < 20) {
            ud += 0.5;
        }
    } if (left) {
        if (lr > -65) {
            lr -= 0.5;
        }
    } if (down) {
        if (!(ud <= -28)) {
            ud -= 0.5;
        }
    } if (right) {
        if (lr < 66) {
            lr += 0.5;
        }
    }

    // Cutout Raised Counter
    if (ud < -20 && lr > -20) {
        if (down) {
            ud += 0.5;
        } if (right) {
            lr -= 0.5;
        } if (down && right && ud >= -20) {
            lr += 0.5;
        }
    }

    // Grab Croissant
    if (ud < -18 && lr < 45 && lr > 35) {
        holdingCroissant = true;
    }

    // Grab Coffee
    if (lr > 64 && ud > 5 && ud < 15) {
        holdingCoffee = true;
    }

    // Throw away items
    if (ud == 20 && lr < -35 && lr > -50) {
        holdingCoffee = false;
        holdingCroissant = false;
    }
    
    if (ud < -18 && lr < 20 && lr > 10 && orderTaken[currentKey] == false) {
        takeOrder();
    }
    if (lr < -62 && ud < 5 && ud > -5 && orderMatch()) {
        serve();
    }

    // Draw It!
    person(10 + lr, 20 + ud, .2, .4, .25);
    if (holdingCroissant) {
        pastry(0.5, 0.5, 20 + lr, 25 + ud);
    }
    if (holdingCoffee) {
        coffeCup(0.5, 0.5, 1 + lr, 28 + ud);
    }
    if (orderTaken[currentKey - 1] && currentKey != 1 && !served[currentKey - 1]) {
        displayOrder();
    }
}

function displayOrder() {
    if (cOrder[currentKey - 1] == 0) {
        pastry(0.25, 0.25, 12 + lr, 45 + ud);
    } else if (cOrder[currentKey - 1] == 1) {
        coffeCup(0.25, 0.25, 12 + lr, 45 + ud);
    } else if (cOrder[currentKey - 1] == 2) {
        pastry(0.25, 0.25, 16 + lr, 43 + ud);
        coffeCup(0.25, 0.25, 10 + lr, 45 + ud);
    }
}

function orderMatch() {
    if (cOrder[currentKey - 1] == 0 && holdingCroissant) {
        return true;
    } else if (cOrder[currentKey - 1] == 1 && holdingCoffee) {
        return true;
    } else if (cOrder[currentKey - 1] == 2 && holdingCroissant && holdingCoffee) {
        return true;
    } else {
        return false;
    }
}

function render() {

    gl.clear( gl.COLOR_BUFFER_BIT );

    // Setting
    drawCoffeeShop();
    
    trashCan();

    makeCounterTopSides();

    player();

    // Counter
    makeCounterWall(); 
    makeCounterTopFront();
    
    pastry(.5, .5, 57, 0);
    coffeCup(.5, .5, 90, 40);

    customer(inLobbyCounter);
    if (orderTaken[inLobbyCounter]) {
        customer(inLobbyCounter + 1);
    }
    if (served[inLobbyCounter]) {
        inLobbyCounter++;
    }


    requestAnimationFrame(render);
}