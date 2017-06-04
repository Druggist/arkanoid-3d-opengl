#include "game.h"

GLuint BrickVAO, PadVAO, BallVAO, SideVAO, CornerVAO, AddonVAO;
GLuint BuffVertices[6];
GLuint BuffTexCoords[6];
GLuint BuffNormals[6];

GameObject *Brick, *Pad, *Side, *Corner, *Addon;
BallObject *Ball;
ShaderProgram *shaderProgram;

Game::Game(GLuint width) 
	: State(GAME_ACTIVE), Keys(), Width(width) { 

}

Game::~Game() {
	delete Brick;
	delete Pad;
	delete Ball;
	delete Side;
	delete Corner;
	delete Addon;
	delete shaderProgram;

	glDeleteVertexArrays(1,&BrickVAO);
	glDeleteVertexArrays(1,&PadVAO);
	glDeleteVertexArrays(1,&BallVAO);
	glDeleteVertexArrays(1,&SideVAO);
	glDeleteVertexArrays(1,&CornerVAO);
	glDeleteVertexArrays(1,&AddonVAO);

	for(int i = 0; i < 6; i++) {
		glDeleteBuffers(1,&BuffVertices[i]);
		glDeleteBuffers(1,&BuffTexCoords[i]);
		glDeleteBuffers(1,&BuffNormals[i]);
	}
}

void Game::Init() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	shaderProgram = new ShaderProgram("vshader.txt",NULL,"fshader.txt");

	//create scene
	Brick = new GameObject();
	Pad = new GameObject();
	Ball = new BallObject();
	Side = new GameObject();
	Corner = new GameObject();
	Addon = new GameObject();

/*
	BuffVertices[0]=Renderer::MakeBuffer(brickVerts, brickNumVerts, sizeof(float)*4);
	BuffTexCoords[0]=Renderer::MakeBuffer(brickTexCoords, brickNumVerts, sizeof(float)*2);
	BuffNormals[0]=Renderer::MakeBuffer(brickNormals, brickNumVerts, sizeof(float)*4);*/
	BuffVertices[1]=Renderer::MakeBuffer((void*) &padVerts, padNumVerts, sizeof(float)*4);
	BuffTexCoords[1]=Renderer::MakeBuffer((void*) &padTexCoords, padNumVerts, sizeof(float)*2);
	BuffNormals[1]=Renderer::MakeBuffer((void*) &padNormals, padNumVerts, sizeof(float)*4);
	/*BuffVertices[2]=Renderer::MakeBuffer(ballVerts, ballNumVerts, sizeof(float)*4);
	BuffTexCoords[2]=Renderer::MakeBuffer(ballTexCoords, ballNumVerts, sizeof(float)*2);
	BuffNormals[2]=Renderer::MakeBuffer(ballNormals, ballNumVerts, sizeof(float)*4);
	BuffVertices[3]=Renderer::MakeBuffer(sideVerts, sideNumVerts, sizeof(float)*4);
	BuffTexCoords[3]=Renderer::MakeBuffer(sideTexCoords, sideNumVerts, sizeof(float)*2);
	BuffNormals[3]=Renderer::MakeBuffer(sideNormals, sideNumVerts, sizeof(float)*4);
	BuffVertices[4]=Renderer::MakeBuffer(cornerVerts, cornerNumVerts, sizeof(float)*4);
	BuffTexCoords[4]=Renderer::MakeBuffer(cornerTexCoords, cornerNumVerts, sizeof(float)*2);
	BuffNormals[4]=Renderer::MakeBuffer(cornerNormals, cornerNumVerts, sizeof(float)*4);
	BuffVertices[5]=Renderer::MakeBuffer(addonVerts, addonNumVerts, sizeof(float)*4);
	BuffTexCoords[5]=Renderer::MakeBuffer(addonTexCoords, addonNumVerts, sizeof(float)*2);
	BuffNormals[5]=Renderer::MakeBuffer(addonNormals, addonNumVerts, sizeof(float)*4);*/
/*
	glGenVertexArrays(1,&BrickVAO); 
	glBindVertexArray(BrickVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[0],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[0],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[0],4); 
	glBindVertexArray(0);*/

	glGenVertexArrays(1,&PadVAO); 
	glBindVertexArray(PadVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[1],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[1],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[1],4); 
	glBindVertexArray(0);
/*
	glGenVertexArrays(1,&BallVAO); 
	glBindVertexArray(BallVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[2],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[2],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[2],4); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&SideVAO); 
	glBindVertexArray(SideVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[3],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[3],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[3],4); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&CornerVAO); 
	glBindVertexArray(CornerVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[4],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[4],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[4],4); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&AddonVAO); 
	glBindVertexArray(AddonVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[5],4); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[5],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[5],4); 
	glBindVertexArray(0);*/
}

void Game::Update(GLfloat dt) {

}

void Game::ProcessInput(GLfloat dt) {
if (this->State == GAME_ACTIVE) {
		GLfloat velocity = PAD_SPEED * dt;

		if (this->Keys[GLFW_KEY_A]) {
			if (Pad->Position.x >= 0)
				Pad->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D]) {
			if (Pad->Position.x <= this->Width - Pad->Size.x)
				Pad->Position.x += velocity;
		}
	}
}

void Game::Render() {
	Pad->Size = vec3(0.5f,0.5f,0.5f);
	Pad->Rotation = vec3(45.0f,0.0f,0.0f);

	Pad->Draw(PadVAO, shaderProgram, padNumVerts);
}