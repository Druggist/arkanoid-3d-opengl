#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

const GLfloat PI = 3.141592653589793f;
const GLfloat PAD_SPEED = 10.0f;
const vec3 BALL_VELOCITY(0.1f, 0.0f, -2.0f);
const GLuint LIVES = 3;
const GLuint SCREEN_WIDTH = 1024;
const GLuint SCREEN_HEIGHT = 600;

#endif
