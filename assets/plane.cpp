// This is a .cpp file for the model: plane

#include "plane.h"

unsigned int planeNumVerts = 6;

float planeVerts[18] = 
{
5, 0, 4, 
5, 0, -4, 
-10, 0, -4, 
-10, 0, 4, 
5, 0, 4, 
-10, 0, -4, 
};

float planeTexCoords[12] = 
{
0, 0, 
1, 0, 
1, 1, 
0, 1, 
0, 0, 
1, 1, 
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

