#include "game.h"

GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint bufColors;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowujący tablickę wektorów normalnych

//Kostka
float* vertices=Models::CubeInternal::vertices;
float* colors=Models::CubeInternal::colors;
float* normals=Models::CubeInternal::normals;
//float* normals=Models::CubeInternal::vertexNormals;
int vertexCount=Models::CubeInternal::vertexCount;

GameObject *Player;
ShaderProgram *shaderProgram;

Game::Game(GLuint width) 
	: State(GAME_ACTIVE), Keys(), Width(width) { 

}

Game::~Game() {
	delete Player;
	delete shaderProgram;
}

void Game::Init() {
	Player = new GameObject();
	shaderProgram = new ShaderProgram("vshader.txt",NULL,"fshader.txt"); //Wczytaj program cieniujący


	//*****Przygotowanie do rysowania pojedynczego obiektu*******
	//Zbuduj VBO z danymi obiektu do narysowania
	bufVertices=Renderer::MakeBuffer(vertices, vertexCount, sizeof(float)*4); //VBO ze współrzędnymi wierzchołków
	bufColors=Renderer::MakeBuffer(colors, vertexCount, sizeof(float)*4);//VBO z kolorami wierzchołków
	bufNormals=Renderer::MakeBuffer(normals, vertexCount, sizeof(float)*4);//VBO z wektorami normalnymi wierzchołków

	//Zbuduj VAO wiążący atrybuty z konkretnymi VBO
	glGenVertexArrays(1,&vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO

	Renderer::VBOToAttr(shaderProgram,"vertex",bufVertices,4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
	Renderer::VBOToAttr(shaderProgram,"color",bufColors,4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
	Renderer::VBOToAttr(shaderProgram,"normal",bufNormals,4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

	glBindVertexArray(0); //Dezaktywuj VAO
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
	Player->Draw(vao, shaderProgram);
}