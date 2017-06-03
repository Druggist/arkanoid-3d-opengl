#include "game_object.h"

GameObject::GameObject()
	: Position(vec3(0.0f)), Size(vec3(1.0f)), Color(vec3(1.0f)), Velocity(vec3(0.0f)), Rotation(vec3(0.0f)), Solid(false), Destroyed(false) {}

GameObject::GameObject(vec3 pos, vec3 size, glm::vec3 color, vec3 velocity, vec3 rotation)
	: Position(pos), Size(size), Color(color), Velocity(velocity), Rotation(rotation), Solid(false), Destroyed(false) {}

void GameObject::Draw() {
	
}