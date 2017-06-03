#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "constants.h"
#include "shaderprogram.h"
#include "game_object.h"

using namespace glm;

enum GameState {
	GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
	GameState State;
	GLboolean Keys[1024];
	GLuint Width;

	Game(GLuint width);
	~Game();
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

#endif