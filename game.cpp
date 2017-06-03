#include "game.h"

GameObject *Player;

Game::Game(GLuint width) 
	: State(GAME_ACTIVE), Keys(), Width(width) { 

}

Game::~Game() {
	delete Player;
}

void Game::Init() {
    
}

void Game::Update(GLfloat dt) {

}

void Game::ProcessInput(GLfloat dt) {
if (this->State == GAME_ACTIVE) {
        GLfloat velocity = PAD_SPEED * dt;

        if (this->Keys[GLFW_KEY_A]) {
            if (Player->Position.x >= 0)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render() {
    
}