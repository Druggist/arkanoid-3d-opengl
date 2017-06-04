#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include "constants.h"
#include "shaderprogram.h"
#include "renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "allmodels.h"

using namespace glm;
using namespace std;

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
	GLuint ReadTexture(const char* filename);
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

#endif