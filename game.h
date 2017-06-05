#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

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

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game {
public:
	GameState State;
	GLboolean Keys[1024];

	Game();
	~Game();
	void Init();
	GLuint ReadTexture(const char* filename);
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void Collisions();

private:
	Collision CheckCollision(BallObject &one, GameObject &two);
	Direction VectorDirection(glm::vec2 target);
};

#endif