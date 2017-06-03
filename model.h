#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include "lodepng.h"

class Model {
public:
	Model(const char * obj, char * texture);
	~Model();

	uint vertexCount;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > texCoords;
	std::vector< glm::vec3 > normals; 

	GLuint texture;

	bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals);
	GLuint readTexture(char* filename);

	void Draw();
	
};

#endif
