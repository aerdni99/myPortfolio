/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Computer Graphics PA3
Author. Angelo Indre
        adi19@uakron.edu
Purpose. Create and animate a robot with WebGL

*/

/*
    Robot.js

    graphics making file for PA3's webGL robot
*/

var gl;

// load the buffers using these vars
var vertices = [];
var colors = [];

var numVertices = 36;

// Core vertex modifiers
var scalarLoc;
var translationLoc;
var colorLoc;
var yRotLoc;

var orthoMat;

// Extra vertex modifiers help implement the wave animation
var toJointLoc;
var inverseToJointLoc;
var zRotLoc;

// controllers for spin animation
var spin = false;
var theta = 0;

// controllers for wave animation
var wave = false;
var touchTop = false;
var lArmDeg = 0;
var rArmDeg = 0;

// controllers for blink animation
var blink = false;
var halfBlink = false;
var blinkHeight = .09;

// controllers for jump animation
var jump = false;
var fall = false;
var height = 0;

var changeColor = false;
var p = 0;  // index for selected color

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
    
    // Make robot part stensil
    stensil();

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

    // Event handler for chosen menu items
    document.addEventListener("keydown", function(event){
        if (event.keyCode == 66) {
            blink = true;
        } else if (event.keyCode == 67) {
            changeColor = true;
        } else if (event.keyCode == 87) {
            wave = true;
        } else if (event.keyCode == 74) {
            jump = true;
        } else if (event.keyCode == 84) {
            spin = true;
        } else if (event.keyCode == 81) {
            self.close();
        }
    });

    // links transformations here to the html file
    scalarLoc = gl.getUniformLocation(program, "scalar");
    translationLoc = gl.getUniformLocation(program, "translation");
    yRotLoc = gl.getUniformLocation(program, "yRot");

    // get location of wave matrices
    zRotLoc = gl.getUniformLocation(program, "zRot");
    toJointLoc = gl.getUniformLocation(program, "toJoint");
    inverseToJointLoc = gl.getUniformLocation(program, "inverseToJoint");

    // links color manipulation here to the html file
    colorLoc = gl.getUniformLocation(program, "initColor");

    // orthographic aid for transformations
    orthoMat = ortho(-10, 10, -10, 10, -10, 10);
    gl.uniformMatrix4fv(gl.getUniformLocation(program, "ortho"), false, flatten(orthoMat));

    // Finally with everything linked and filled, we start manipulating and drawing
    render();
};

// takes 4 vertices and draws 2 triangles from them to form a square
function composeFace(tl, bl, tr, br) {
    var cubeHalves = [tl, bl, tr, bl, tr, br];
    for ( var i = 0; i < 6; i++ ) {
        vertices.push(cubeHalves[i]);
    }
}

// pushes color values onto the color vector for each vertex
function makePrismColor(r, g, b, a) {
    for (var j = 0; j < 6; j++) {
        r -= .05;
        g -= .05;
        b -= .05;
        for ( var i = 0; i < 6; i++ ) {
            colors.push(vec4(r, g, b, a));
        }
    }
}

// Creates a basic white cube which can be manipulated to form robot parts
function stensil() {
    var roboVerts = [
        vec4( -1, -1, -1, 1 ),
        vec4(  1, -1, -1, 1 ),
        vec4( -1,  1, -1, 1 ),
        vec4( -1, -1,  1, 1 ),
        vec4(  1, -1,  1, 1 ),
        vec4(  1,  1, -1, 1 ),
        vec4( -1,  1,  1, 1 ),
        vec4(  1,  1,  1, 1 )
        ];
    composeFace(roboVerts[0], roboVerts[2], roboVerts[3], roboVerts[6]);    // left
    composeFace(roboVerts[0], roboVerts[1], roboVerts[2], roboVerts[5]);    // front
    composeFace(roboVerts[3], roboVerts[4], roboVerts[6], roboVerts[7]);    // rear
    composeFace(roboVerts[1], roboVerts[5], roboVerts[4], roboVerts[7]);    // right
    composeFace(roboVerts[0], roboVerts[1], roboVerts[3], roboVerts[4]);    // bottom
    composeFace(roboVerts[2], roboVerts[5], roboVerts[6], roboVerts[7]);    // top

    makePrismColor( 1.0, 1.0, 1.0, 1.0 );

}

// Makes a 4x4 matrix that scales the length, height, and depth of each robot piece.
// Doubles as scalar matrix for changing color as well
function sizePart(l, h, d) {
    var result = mat4();
    result[0][0] = l;
    result[1][1] = h;
    result[2][2] = d;
    return result;
}

// Makes a 4x4 translation matrix for positioning robot parts
function movePart(x, y, z) {
    var result = mat4(1);
    result[0][3] = x;
    result[1][3] = y;
    result[2][3] = z;
    return result;
}

// Makes a rotation matrix for some degrees in the y axis
function makeYRot(degree) {
    var result = mat4(1);
    result[0][0] = Math.cos(degree);
    result[2][0] = -1 * Math.sin(degree);
    result[2][2] = Math.cos(degree);
    result[0][2] = Math.sin(degree);
    return result;
}

// z axis rotation matrix
function makeZRot(degree) {
    var result = mat4(1);
    result[0][0] = Math.cos(degree);
    result[1][0] = -1 * Math.sin(degree);
    result[1][1] = Math.cos(degree);
    result[0][1] = Math.sin(degree);
    return result;
}

// Available colors to cycle through for color changes
var robotColors = [
    0.4, 0.4, 0.4, 1.0, // gray
    0.4, 0.5, 0.3, 1.0, // green
    0.4, 0.2, 0.1, 1.0, // rust
    0.5, 0.4, 0.0, 1.0, // gold
    0.6, 0.6, 0.7, 1.0, // steel blue
    0.7, 0.5, 0.0, 1.0, // copper
    0.7, 1.0, 0.9, 1.0, // bright green
    1.0, 1.0, 0.3, 1.0  // yellow
];

function render() {

    gl.clearDepth(1.0);

    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT );
    gl.enable(gl.DEPTH_TEST);

    gl.uniformMatrix4fv(toJointLoc, false, flatten(mat4(1)));
    gl.uniformMatrix4fv(inverseToJointLoc, false, flatten(mat4(1)));
    gl.uniformMatrix4fv(zRotLoc, false, flatten(mat4(1)));

    // Color for main body parts
    if (changeColor) {
        p += 4;
        if (p == 32) {
            p = 0;
        }
        changeColor = false;
    }
    var newColor = sizePart(robotColors[p], robotColors[p+1], robotColors[p+2]);
    gl.uniformMatrix4fv( colorLoc, false, flatten( newColor ) );

    // Rotation update
    var rotate = makeYRot(theta);
    gl.uniformMatrix4fv( yRotLoc, false, flatten( rotate ) );

    // spin animation logic
    if (spin) {
        if (theta < 6.28) {
            theta += .02;
        } else {
            spin = false;
            theta = 0;
        }
    }

    // jump animation logic
    if (jump && !fall && height < 2) {
        height += .1;
        if (height > 1.9) {
            fall = true;
        }
    } else if (height > 0) {
        height -= .1;
    } else {
        jump = false;
        fall = false;
        height = 0;
    }

    // torso
    var size = sizePart( 1, 2, 1 );
    var offset = movePart( 0, 0 + height, 0 );
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );

    // left leg 
    var size = sizePart( .40, 1.5, .40 );
    var offset = movePart( -.5, -3.5 + height, 0);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );

    // right leg
    var size = sizePart( .40, 1.5, .40 );
    var offset = movePart( .5, -3.5 + height, 0);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    
    // left arm
    var size = sizePart( .3, 1.25, .3 );
    var offset = movePart( -1.4, .5 + height, 0);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    
    // rotating arms
    if (wave) {
        // Rotation update
        var armRot = makeZRot(lArmDeg);
        if (lArmDeg < 3 && !touchTop) {
            lArmDeg += .05;
        } else {
            lArmDeg -= .05;
        }
        var atJoint = movePart(0, -1.25, 0);
        var putItBack = movePart(0, 1.25, 0);
        gl.uniformMatrix4fv( toJointLoc, false, flatten(atJoint));
        gl.uniformMatrix4fv( zRotLoc, false, flatten( armRot ) );
        gl.uniformMatrix4fv( inverseToJointLoc, false, flatten(putItBack));
        gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    } else {
        gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    }
    
    // right arm
    var size = sizePart( .3, 1.25, .3 );
    var offset = movePart( 1.4, .5 + height, 0);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    if (wave) {
        // Rotation update
        var armRot = makeZRot(rArmDeg);
        if (rArmDeg > -3 && !touchTop) {
            rArmDeg -= .05;
        } else {
            touchTop = true;
            if (rArmDeg < 0) {
                rArmDeg += .05;
            } else {
                wave = false;
                touchTop = false;
            }
        }
        var atJoint = movePart(0, -1.25, 0);
        var putItBack = movePart(0, 1.25, 0);
        gl.uniformMatrix4fv( toJointLoc, false, flatten(atJoint));
        gl.uniformMatrix4fv( zRotLoc, false, flatten( armRot ) );
        gl.uniformMatrix4fv( inverseToJointLoc, false, flatten(putItBack));
        gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    } else {
        gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    }
    gl.uniformMatrix4fv(toJointLoc, false, flatten(mat4(1)));
    gl.uniformMatrix4fv(inverseToJointLoc, false, flatten(mat4(1)));
    gl.uniformMatrix4fv(zRotLoc, false, flatten(mat4(1)));
    
    // head
    var size = sizePart( .75, .75, .75 );
    var offset = movePart( 0, 3 + height, 0);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    
    // Color for eyes (light green) (constant)
    var newColor = sizePart(0.4, 1.0, 0.4);
    gl.uniformMatrix4fv( colorLoc, false, flatten( newColor ) );

    // left eye
    if (!blink) {
        var size = sizePart( .1, .1, .1 );
    } else {
        var size = sizePart( .1, blinkHeight, .1);
    }
    var offset = movePart( -.4, 3 + height, .76);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    
    // right eye
    if (!blink) {
        var size = sizePart( .1, .1, .1 );
    } else {
        var size = sizePart(.1, blinkHeight, .1);
        if (blinkHeight > 0 && !halfBlink) {
            blinkHeight -= .01;
            if (blinkHeight <= .01) {
                halfBlink = true;
            }
        }
        if (blinkHeight >= .1) {
            blink = false;
            halfBlink = false;
        }
        if (halfBlink) {
            blinkHeight += .01;
        }
    }
    var offset = movePart( .5, 3 + height, .76);
    gl.uniformMatrix4fv( translationLoc, false, flatten( offset ) );
    gl.uniformMatrix4fv( scalarLoc, false, flatten( size ) );
    gl.drawArrays( gl.TRIANGLES, 0, numVertices );
    
    requestAnimationFrame(render);
}
