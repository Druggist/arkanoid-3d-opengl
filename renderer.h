#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaderprogram.h"

using namespace glm;

class Renderer {
public:
	static GLuint MakeBuffer(void *data, int vertexCount, int vertexSize);
	static void VBOToAttr(ShaderProgram *shaderProgram, const char* attributeName, GLuint bufVBO, int vertexSize);
private:
	Renderer();

};