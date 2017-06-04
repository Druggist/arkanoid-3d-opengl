#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "shaderprogram.h"
#include "lodepng.h"

using namespace glm;

class Renderer {
public:
	static GLuint MakeBuffer(void *data, int vertexCount, int vertexSize);
	static void VBOToAttr(ShaderProgram *shaderProgram, const char* attributeName, GLuint bufVBO, int vertexSize);
	static GLuint ReadTexture(const char* filename);
	static vec3 MeasureObject(float * vertices, unsigned int numVertices);
private:
	Renderer();

};

#endif