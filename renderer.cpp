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

GLuint Renderer::ReadTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);

	if (error!=0) printf("Error while reading texture %s. Error code: %d. \n",filename,error);

	glGenTextures(1,&tex); 
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return tex;
}

vec3 Renderer::MeasureObject(float * vertices, unsigned int numVertices) {
	vec3 min(0.0f);
	vec3 max(0.0f);
	for(int i = 0; i<numVertices/3; i++){
		if(vertices[0+i*3] < min.x) min.x = vertices[0+i*3];
		if(vertices[1+i*3] < min.y) min.y = vertices[1+i*3];
		if(vertices[2+i*3] < min.z) min.z = vertices[2+i*3];

		if(vertices[0+i*3] > max.x) max.x = vertices[0+i*3];
		if(vertices[1+i*3] > max.y) max.y = vertices[1+i*3];
		if(vertices[2+i*3] > max.z) max.z = vertices[2+i*3];
	}

	return max-min;
}