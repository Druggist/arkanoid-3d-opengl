// This is a .cpp file for the model: plane

#include "plane.h"

unsigned int planeNumVerts = 6;

float planeVerts[18] = 
{
5, -0, 4, 
5, 0, -4, 
-10, 0, -4, 
-10, -0, 4, 
5, -0, 4, 
-10, 0, -4, 
};

float planeTexCoords[12] = 
{
7.3e-05, 7.3e-05, 
0.533329, 7.3e-05, 
0.533328, 0.999927, 
7.3e-05, 0.999927, 
7.3e-05, 7.3e-05, 
0.533328, 0.999927, 
};

float planeNormals[18] = 
{
0, 1, 0, 
0, 1, 0, 
0, 1, 0, 
0, 1, 0, 
0, 1, 0, 
0, 1, 0, 
};

