#include "game.h"

#include <iostream>

GLuint BrickVAO, PadVAO, BallVAO, SideVAO, CornerVAO, AddonVAO, PlaneVAO;
GLuint BuffVertices[7];
GLuint BuffTexCoords[7];
GLuint BuffNormals[7];

GameObject *Pad, *Side1, *Side2, *Side3, *Side4, *Side5, *Corner1, *Corner2, *Plane;
GameObject *Addon1, *Addon2, *Addon3, *Addon4, *Addon5, *Addon6, *Addon7, *Addon8;
GameObject *Life1, *Life2, *Life3;
vector<GameObject*> Bricks;
BallObject *Ball;
ShaderProgram *shaderProgram;

Game::Game() { 

}

Game::~Game() {
	delete Pad;
	delete Ball;
	delete Side1;
	delete Side2;
	delete Side3;
	delete Side4;
	delete Side5;
	delete Corner1;
	delete Corner2;
	delete Addon1;
	delete Addon2;
	delete Addon3;
	delete Addon4;
	delete Addon5;
	delete Addon6;
	delete Addon7;
	delete Addon8;
	delete Life1;
	delete Life2;
	delete Life3;
	delete Plane;
	delete shaderProgram;

	glDeleteVertexArrays(1,&BrickVAO);
	glDeleteVertexArrays(1,&PadVAO);
	glDeleteVertexArrays(1,&BallVAO);
	glDeleteVertexArrays(1,&SideVAO);
	glDeleteVertexArrays(1,&CornerVAO);
	glDeleteVertexArrays(1,&AddonVAO);
	glDeleteVertexArrays(1,&PlaneVAO);

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
	Ball = new BallObject(vec3(0.0f,0.0f,5.0f), Renderer::MeasureObject(ballVerts, ballNumVerts).x / 2, vec3(1.5f), BALL_VELOCITY);


	Ball->Tex = Renderer::ReadTexture("assets/textures/white.png");
	Plane = new GameObject(vec3(0.0f,-0.5f,0.0f), Renderer::MeasureObject(planeVerts, planeNumVerts), vec3(0.0f,90.0f,0.0f));
	Plane->Tex = Renderer::ReadTexture("assets/textures/plane.png");
	//CORNERS
	Corner1 = new GameObject(vec3(-3.3f,0.0f,-5.0f), Renderer::MeasureObject(cornerVerts, cornerNumVerts), vec3(0.0f,180.0f,0.0f));
	Corner1->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Corner2 = new GameObject(vec3(4.0f,0.0f,-4.3f), Renderer::MeasureObject(cornerVerts, cornerNumVerts), vec3(0.0f,90.0f,0.0f));
	Corner2->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	//SIDES
	Side1 = new GameObject(vec3(4.0f,0.0f,0.0f), Renderer::MeasureObject(sideVerts, sideNumVerts), vec3(0.0f,90.0f,0.0f));
	Side1->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Side2 = new GameObject(vec3(-4.0f,0.0f,0.0f), Renderer::MeasureObject(sideVerts, sideNumVerts), vec3(0.0f,90.0f,0.0f));
	Side2->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Side3 = new GameObject(vec3(0.0f,0.0f,-5.0f), Renderer::MeasureObject(sideVerts, sideNumVerts), vec3(0.0f,00.0f,0.0f), vec3(0.8f,1.0f,1.0f));
	Side3->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Side4 = new GameObject(vec3(4.0f,0.0f,5.0f), Renderer::MeasureObject(sideVerts, sideNumVerts), vec3(0.0f,90.0f,0.0f));
	Side4->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Side5 = new GameObject(vec3(-4.0f,0.0f,5.0f), Renderer::MeasureObject(sideVerts, sideNumVerts), vec3(0.0f,90.0f,0.0f));
	Side5->Tex = Renderer::ReadTexture("assets/textures/gray.png");


	Addon1 = new GameObject(vec3(2.0f,0.0f,-5.0f), Renderer::MeasureObject(addonVerts, addonNumVerts));
	Addon1->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Addon2 = new GameObject(vec3(-2.0f,0.0f,-5.0f), Renderer::MeasureObject(addonVerts, addonNumVerts));
	Addon2->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	

	Addon3 = new GameObject(vec3(-4.0f,0.0f,-2.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon3->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Addon4 = new GameObject(vec3(4.0f,0.0f,-2.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon4->Tex = Renderer::ReadTexture("assets/textures/gray.png");


	Addon5 = new GameObject(vec3(-4.0f,0.0f,1.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon5->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Addon6 = new GameObject(vec3(4.0f,0.0f,1.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon6->Tex = Renderer::ReadTexture("assets/textures/gray.png");

	Addon7 = new GameObject(vec3(-4.0f,0.0f,4.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon7->Tex = Renderer::ReadTexture("assets/textures/gray.png");
	Addon8 = new GameObject(vec3(4.0f,0.0f,4.0f), Renderer::MeasureObject(addonVerts, addonNumVerts), vec3(0.0f,90.0f,0.0f));
	Addon8->Tex = Renderer::ReadTexture("assets/textures/gray.png");

	//GameObjects
	for(int j = 0; j < 6; j++) {

		for(int i = 0; i < 10; i++) {
			Bricks.push_back(new GameObject());
			Bricks[i+j*10]->Rotation = vec3(0.0f,90.0f,0.0f);
			Bricks[i+j*10]->Position = vec3(-3.15f+0.7f*i,0.0f,-0.5f-0.5f*j);
			if(j==0) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/green.png");
			if(j==1) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/pink.png");
			if(j==2) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/blue.png");
			if(j==3) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/yellow.png");
			if(j==4) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/red.png");
			if(j==5) 
				Bricks[i+j*10]->Tex = Renderer::ReadTexture("assets/textures/gray.png");			
		}
	}

	Life1 = new GameObject(vec3(-1.0f,0.0f,6.5f), Renderer::MeasureObject(padVerts, padNumVerts), vec3(0.0f,90.0f,0.0f), vec3(1.0f,1.0f,1.0f));
	Life1->Tex = Renderer::ReadTexture("assets/textures/pad.png");
	Life2 = new GameObject(vec3(-2.0f,0.0f,6.5f), Renderer::MeasureObject(padVerts, padNumVerts), vec3(0.0f,90.0f,0.0f), vec3(1.0f,1.0f,1.0f));
	Life2->Tex = Renderer::ReadTexture("assets/textures/pad.png");
	Life3 = new GameObject(vec3(-3.0f,0.0f,6.5f), Renderer::MeasureObject(padVerts, padNumVerts), vec3(0.0f,90.0f,0.0f), vec3(1.0f,1.0f,1.0f));
	Life3->Tex = Renderer::ReadTexture("assets/textures/pad.png");

	Pad = new GameObject(vec3(0.0f,0.0f,5.5f), Renderer::MeasureObject(padVerts, padNumVerts), vec3(0.0f,90.0f,0.0f), vec3(1.5f,1.5f,1.5f));
	Pad->Tex = Renderer::ReadTexture("assets/textures/pad.png");

	//scene end

	BuffVertices[0]=Renderer::MakeBuffer(brickVerts, brickNumVerts, sizeof(float)*3);
	BuffTexCoords[0]=Renderer::MakeBuffer(brickTexCoords, brickNumVerts, sizeof(float)*2);
	BuffNormals[0]=Renderer::MakeBuffer(brickNormals, brickNumVerts, sizeof(float)*3);
	BuffVertices[1]=Renderer::MakeBuffer((void*) padVerts, padNumVerts, sizeof(float)*3);
	BuffTexCoords[1]=Renderer::MakeBuffer((void*) padTexCoords, padNumVerts, sizeof(float)*2);
	BuffNormals[1]=Renderer::MakeBuffer((void*) padNormals, padNumVerts, sizeof(float)*3);
	BuffVertices[2]=Renderer::MakeBuffer(ballVerts, ballNumVerts, sizeof(float)*3);
	BuffTexCoords[2]=Renderer::MakeBuffer(ballTexCoords, ballNumVerts, sizeof(float)*2);
	BuffNormals[2]=Renderer::MakeBuffer(ballNormals, ballNumVerts, sizeof(float)*3);
	BuffVertices[3]=Renderer::MakeBuffer(sideVerts, sideNumVerts, sizeof(float)*3);
	BuffTexCoords[3]=Renderer::MakeBuffer(sideTexCoords, sideNumVerts, sizeof(float)*2);
	BuffNormals[3]=Renderer::MakeBuffer(sideNormals, sideNumVerts, sizeof(float)*3);
	BuffVertices[4]=Renderer::MakeBuffer(cornerVerts, cornerNumVerts, sizeof(float)*3);
	BuffTexCoords[4]=Renderer::MakeBuffer(cornerTexCoords, cornerNumVerts, sizeof(float)*2);
	BuffNormals[4]=Renderer::MakeBuffer(cornerNormals, cornerNumVerts, sizeof(float)*3);
	BuffVertices[5]=Renderer::MakeBuffer(addonVerts, addonNumVerts, sizeof(float)*3);
	BuffTexCoords[5]=Renderer::MakeBuffer(addonTexCoords, addonNumVerts, sizeof(float)*2);
	BuffNormals[5]=Renderer::MakeBuffer(addonNormals, addonNumVerts, sizeof(float)*3);
	BuffVertices[6]=Renderer::MakeBuffer(planeVerts, planeNumVerts, sizeof(float)*3);
	BuffTexCoords[6]=Renderer::MakeBuffer(planeTexCoords, planeNumVerts, sizeof(float)*2);
	BuffNormals[6]=Renderer::MakeBuffer(planeNormals, planeNumVerts, sizeof(float)*3);

	glGenVertexArrays(1,&BrickVAO); 
	glBindVertexArray(BrickVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[0],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[0],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[0],3); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&PadVAO); 
	glBindVertexArray(PadVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[1],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[1],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[1],3);
	glBindVertexArray(0);

	glGenVertexArrays(1,&BallVAO); 
	glBindVertexArray(BallVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[2],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[2],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[2],3); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&SideVAO); 
	glBindVertexArray(SideVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[3],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[3],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[3],3); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&CornerVAO); 
	glBindVertexArray(CornerVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[4],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[4],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[4],3); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&AddonVAO); 
	glBindVertexArray(AddonVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[5],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[5],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[5],3); 
	glBindVertexArray(0);

	glGenVertexArrays(1,&PlaneVAO); 
	glBindVertexArray(PlaneVAO); 
	Renderer::VBOToAttr(shaderProgram,"vertex",BuffVertices[6],3); 
	Renderer::VBOToAttr(shaderProgram,"texCoords",BuffTexCoords[6],2); 
	Renderer::VBOToAttr(shaderProgram,"normal",BuffNormals[6],3); 
	glBindVertexArray(0);
}

void Game::Update(GLfloat dt) {
	Ball->Move(dt);
	Collisions();
}

void Game::ProcessInput(GLfloat dt) {
if (this->State == GAME_ACTIVE) {
		GLfloat velocity = PAD_SPEED * dt;

		if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT]) {
			if (Pad->Position.x >= -3.0f){
				Pad->Position.x -= velocity;
				if(Ball->Stuck) Ball->Position.x -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT]) {
			if (Pad->Position.x <= 3.0f){
				Pad->Position.x += velocity;
				if(Ball->Stuck) Ball->Position.x += velocity;
			}
		}
		if (this->Keys[GLFW_KEY_W] || this->Keys[GLFW_KEY_UP] || this->Keys[GLFW_KEY_SPACE]) {
			Ball->Stuck = GL_FALSE;
		}
	}
}

void Game::Render() {

	Plane->Draw(PlaneVAO, shaderProgram, planeNumVerts);

	Corner1->Draw(CornerVAO, shaderProgram, cornerNumVerts);
	Corner2->Draw(CornerVAO, shaderProgram, cornerNumVerts);

	Side1->Draw(SideVAO, shaderProgram, sideNumVerts);
	Side2->Draw(SideVAO, shaderProgram, sideNumVerts);
	Side3->Draw(SideVAO, shaderProgram, sideNumVerts);
	Side4->Draw(SideVAO, shaderProgram, sideNumVerts);
	Side5->Draw(SideVAO, shaderProgram, sideNumVerts);

	Addon1->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon2->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon3->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon4->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon5->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon6->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon7->Draw(AddonVAO, shaderProgram, addonNumVerts);
	Addon8->Draw(AddonVAO, shaderProgram, addonNumVerts);

	for(int i = 0; i < Bricks.size(); i++ ){
		if(Bricks[i]->Destroyed == false) Bricks[i]->Draw(BrickVAO, shaderProgram, brickNumVerts);
	}

	if(!Life1->Destroyed) Life1->Draw(PadVAO, shaderProgram, padNumVerts);
	if(!Life2->Destroyed) Life2->Draw(PadVAO, shaderProgram, padNumVerts);
	if(!Life3->Destroyed) Life3->Draw(PadVAO, shaderProgram, padNumVerts);

	Pad->Draw(PadVAO, shaderProgram, padNumVerts);
	Ball->Draw(BallVAO, shaderProgram, ballNumVerts);
}

void Game::Collisions() {
	if(Ball->Position.x + Ball->Size.x / 2 >= Side1->Position.x - Side1->Size.z / 2 || Ball->Position.x - Ball->Size.x / 2 <= Side2->Position.x + Side2->Size.z / 2){
		Ball->Velocity.x = -Ball->Velocity.x;
	}

	if(Ball->Position.z - Ball->Size.z / 2 <= Side3->Position.z + Side3->Size.z / 2) {
		Ball->Velocity.z = -Ball->Velocity.z;
	}

	if(Ball->Position.z >= 6.0f) {
		Ball->Reset(vec3(Pad->Position.x,0.0f,5.0f), BALL_VELOCITY);
	}
	
	for (auto &box : Bricks) {
		if (!box->Destroyed) {
			Collision collision = CheckCollision(*Ball, *box);
			if (std::get<0>(collision)) { 
				if (!box->Solid) box->Destroyed = GL_TRUE;
				Direction dir = std::get<1>(collision);
                vec2 diff_vector = std::get<2>(collision);
                
                if (dir == LEFT || dir == RIGHT) {
                    Ball->Velocity.x = -Ball->Velocity.x;
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT) Ball->Position.x += penetration;
                    else Ball->Position.x -= penetration;
                } else {
                    Ball->Velocity.z = -Ball->Velocity.z;
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP) Ball->Position.z -= penetration;
                    else Ball->Position.z += penetration;
                }
			}	
		}
	}
}

Collision Game::CheckCollision(BallObject &one, GameObject &two) {
	// Get center point circle first 
	vec2 center(one.Position.x, one.Position.z);
	// Calculate AABB info (center, half-extents)
	vec2 aabb_half_extents(two.Size.x / 2, two.Size.z / 2);
	vec2 aabb_center(two.Position.x, two.Position.z);
	// Get difference vector between both centers
	vec2 difference = center - aabb_center;
	vec2 clamped = clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	vec2 closest = aabb_center + clamped;
	// Now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;
	
	if(length(difference) < one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, vec2(0, 0));
}  

Direction Game::VectorDirection(vec2 target)
{
	glm::vec2 compass[] = {
		vec2(0.0f, 1.0f),	// up
		vec2(1.0f, 0.0f),	// right
		vec2(0.0f, -1.0f),	// down
		vec2(-1.0f, 0.0f)	// left
	};

	GLfloat max = 0.0f;
	GLuint best_match = -1;

	for (GLuint i = 0; i < 4; i++) {
		GLfloat dot_product = dot(normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}   