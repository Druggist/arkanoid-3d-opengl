#include "game.h"

GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint bufColors;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowujący tablickę wektorów normalnych
GLuint bufTexCoords; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych teksturowania

//Kostka
float* vertices=Models::CubeInternal::vertices;
float* colors=Models::CubeInternal::colors;
float* normals=Models::CubeInternal::normals;
float* texCoords=Models::CubeInternal::texCoords;
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
	glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
	glEnable(GL_DEPTH_TEST);

	Player = new GameObject();
	shaderProgram = new ShaderProgram("vshader.txt",NULL,"fshader.txt"); //Wczytaj program cieniujący


	//*****Przygotowanie do rysowania pojedynczego obiektu*******
	//Zbuduj VBO z danymi obiektu do narysowania
	bufVertices=Renderer::MakeBuffer(vertices, vertexCount, sizeof(float)*4); //VBO ze współrzędnymi wierzchołków
	bufColors=Renderer::MakeBuffer(colors, vertexCount, sizeof(float)*4);//VBO z kolorami wierzchołków
	bufNormals=Renderer::MakeBuffer(normals, vertexCount, sizeof(float)*4);//VBO z wektorami normalnymi wierzchołków
	bufTexCoords=Renderer::MakeBuffer(texCoords, vertexCount, sizeof(float)*2);//VBO ze wspolrzednymi teksturowania

	//Zbuduj VAO wiążący atrybuty z konkretnymi VBO
	glGenVertexArrays(1,&vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO

	Renderer::VBOToAttr(shaderProgram,"vertex",bufVertices,4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
	Renderer::VBOToAttr(shaderProgram,"color",bufColors,4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
	Renderer::VBOToAttr(shaderProgram,"normal",bufNormals,4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
	Renderer::VBOToAttr(shaderProgram,"texCoords",bufTexCoords,2); //"texCoords" odnosi się do deklaracji "in vec2 texCoords;" w vertex shaderze

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
	Player->Position = vec3(-1.0f, -1.0f, 5.0f);
	Player->Size = vec3(0.5f,0.5f,0.5f);
	Player->Rotation = vec3(45.0f,0.0f,0.0f);

	Player->Draw(vao, shaderProgram);
}