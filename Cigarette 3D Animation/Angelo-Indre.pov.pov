/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Ray Tracing Project
Author. Angelo Indre
        adi19@zips.uakron.edu
Purpose. Create a scene with objects and animate them with POVRay's software

*/

#version 3.7;
global_settings { assumed_gamma 1.2 } 

#include "colors.inc"
#include "stones.inc"
#include "textures.inc"  

camera {
    location <-2, 10, -7>
    look_at <0,0,5>
}
light_source {
    <-2, 20, -8>
    color White
    area_light <5, 0, 0>, <0, 0, 5>, 5, 5   // area light makes my shadows soft
    adaptive 1
}  

// "floor"
plane { 
    <0, 1, 0>, -5
    pigment { checker color White, color Black }
    scale 25
}

// The Cigarette   
#declare cigarette = union {        
    cylinder {
        <0, .5, 0>,
        <3, .5, 0>,
        1
        pigment { White }
    }  
    difference {    
        cylinder {
            <-1, .5, 0>,
            <0, .5, 0>,
            1
            pigment { Orange }
        }
        cylinder {
            <-.99, .5, 0>
            <-2, .5, 0>
            .9
            pigment { White }
        }
    }
    scale <1, .3, .3>
}
#declare butt = difference {
    object { cigarette }
    box {
        <1, -1, -1>
        <5, 2, 2>
        pigment { White }
    }
}    

// The Ashtray
#declare ashtray =
difference { 
    difference { 
        cylinder {
            <0, 0, 0> 
            <0, 1, 0> 
            3 
        }
        cylinder {
            <0, 0.1, 0>
            <0, 1.2, 0>
            3
            scale .9 
        }  
    }
    union {
        cylinder {
            <-3, 1, 0>
            <3, 1, 0>
            1
            scale <0, .3, .3>
        }
        cylinder {
            <0, 1, -3>
            <0, 1, 3>
            1
            scale <.3, .3, 0>
        }
        translate <0, .6, 0>
    }
    texture { T_Stone22 }
    finish { specular 1 }
    translate <-1, 3.7 , 3>
}

// Table Components
#declare elbow = difference {
    torus {
        3, .3
        translate <0, 1, 0>
    }
    union {
        box {
            <0, 0, -4>
            <4, 2, 4> 
        }
        box {
            <0, 0, 0>
            <-4, 2, -4>
        }
    }
} 
#declare tableCorner = object {
    union {
        object { elbow }
        object { elbow translate <0, .6, 0> }
        object { elbow translate <0, 1.2, 0> }
        object { elbow translate <0, 1.8, 0> }
        object { elbow translate <0, 2.4, 0> }
    }
}
#declare tableSidePiece = cylinder {
    <0, 1, 3>
    <30, 1, 3>
    .3
}
#declare tableSide = object {
    union {
        object { tableSidePiece }
        object { tableSidePiece translate <0, .6, 0>}
        object { tableSidePiece translate <0, 1.2, 0>}
        object { tableSidePiece translate <0, 1.8, 0>}
        object { tableSidePiece translate <0, 2.4, 0>}   
    }
}

#declare tableBorder = union{
    object { tableSide }
    object { tableCorner }
    object { tableSide
             rotate <0, 90, 0> 
             translate <-6, 0, 0> }
    rotate <0, -135, 0>
    texture { Chrome_Metal }         
}
 
#declare tabletopCorner = cylinder {
    <0, .7, 0>
    <0, 3.7, 0>
    3
}
#declare bigTabletopPiece = union {
    box {
    <0, .7, -3>
    <30, 3.7, 30>
    rotate <0, -45, 0>  
    }
    box {
    <0, .7, -3>
    <-30, 3.7, 30>
    rotate <0, 45, 0>
    }
}
#declare tableTop = union {
    object { tabletopCorner }
    object { bigTabletopPiece }
    rotate <30, 45, 0>
    scale 5
    texture { Tan_Wood }
    scale .2
    rotate <0, -45, 0> 
    rotate <-30, 0, 0> 
    finish { specular 1.2 }
}


// The Table!
#declare table = union {
    object { tableTop }
    object { tableBorder }
} 

table

ashtray

object { butt
         rotate <0, 0, -15>
         translate <-4, 4.4, 3> }

object { cigarette
         #if (clock <= 5)
             translate <-1, 4, -.5 - clock * .5>
         #else
             translate <-1, 4 - pow((clock - 5),2), -3 - (clock - 5) *.5>
         #end
}
object { cigarette
         #if (clock <= 3)
             translate <-1, 4, -1.5 - clock * .5>
         #else
             #if (clock <= 5)
                 translate <-1, 4 - pow((clock - 3),2), -3 - (clock - 3) *.5>
             #end
         #end
}  
         
          
          


 

