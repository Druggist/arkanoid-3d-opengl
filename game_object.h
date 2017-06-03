#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"
#include "constants.h"
#include "cube.h"

using namespace glm;

class GameObject {
public:
	vec3 Position, Size, Velocity, Color, Rotation;
	GLboolean Destroyed;
	GLboolean Solid;
	//model

	GameObject();
	GameObject(vec3 pos, vec3 size, glm::vec3 color = glm::vec3(1.0f), vec3 velocity = vec3(0.0f), vec3 rotation = vec3(0.0f));
	virtual void Draw(GLuint &vao, ShaderProgram *shaderProgram);
};

#endif