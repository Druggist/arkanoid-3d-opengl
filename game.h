#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
	GLuint Width, Height;

	Game(GLuint Width, GLuint Height);
	~Game();
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

#endif