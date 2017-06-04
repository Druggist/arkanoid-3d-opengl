#include "ball_object.h"

BallObject::BallObject()
	: GameObject(), Radius(1.0f), Stuck(true) {}

BallObject::BallObject(vec3 pos, GLfloat radius, glm::vec3 color, vec3 velocity)
	: GameObject(pos, vec3(radius * 2), color, velocity), Radius(radius), Stuck(true) {}

vec3 BallObject::Move(GLfloat dt){
	if (!this->Stuck) this->Position += this->Velocity * dt;
	return this->Position;
}

void BallObject::Reset(vec3 pos, vec3 velocity){
	this->Position = pos;
    this->Velocity = velocity;
    this->Stuck = true;
}
