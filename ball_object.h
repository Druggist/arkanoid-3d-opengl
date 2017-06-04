#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game_object.h"

using namespace glm;

class BallObject : public GameObject {
public:
	GLfloat Radius;
	GLboolean Stuck;

	BallObject();
	BallObject(vec3 pos, GLfloat radius, vec3 scale = vec3(1.0f), vec3 velocity = vec3(0.0f));
	
	vec3 Move(GLfloat dt);
	void Reset(vec3 pos, vec3 velocity);
};

#endif