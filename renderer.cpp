#include "renderer.h"

GLuint Renderer::MakeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1,&handle);
	glBindBuffer(GL_ARRAY_BUFFER,handle);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);

	return handle;
}

void Renderer::VBOToAttr(ShaderProgram *shaderProgram, const char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName);
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL);
}