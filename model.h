#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

class Model {
public:
	Model(const char * obj, const char * texture);

	float width, height, depth;

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > texCoords;
	std::vector< glm::vec3 > normals; 


private:
	bool loadOBJ(
	    const char * path,
	    std::vector < glm::vec3 > & out_vertices,
	    std::vector < glm::vec2 > & out_uvs,
	    std::vector < glm::vec3 > & out_normals
	)

}

