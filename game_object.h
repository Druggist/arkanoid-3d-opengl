#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"
#include "constants.h"
#include "renderer.h"

using namespace glm;

class GameObject {
public:
	vec3 Position, Size, Velocity, Scale, Rotation;
	GLboolean Destroyed;
	GLboolean Solid;
	GLuint Tex;

	GameObject();
	GameObject(vec3 pos, vec3 size, vec3 rot = vec3(0.0f), vec3 scale = vec3(1.0f), vec3 velocity = vec3(0.0f)); 
	
	virtual void Draw(GLuint &vao, ShaderProgram *shaderProgram, GLuint vertexCount);
};

#endif