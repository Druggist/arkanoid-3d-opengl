#include "game_object.h"
#include <iostream>

GameObject::GameObject()
	: Position(vec3(0.0f)), Size(vec3(1.0f)), Scale(vec3(1.0f)), Velocity(vec3(0.0f)), Rotation(vec3(0.0f)), Solid(false), Destroyed(false), Tex(Renderer::ReadTexture("assets/textures/checker.png")) {}

GameObject::GameObject(vec3 pos, vec3 size, vec3 rot, vec3 scale, vec3 velocity)
	: Position(pos), Size(size*scale), Scale(scale), Velocity(velocity), Rotation(rot), Solid(false), Destroyed(false), Tex(Renderer::ReadTexture("assets/textures/checker.png")) {}


void GameObject::Draw(GLuint &vao, ShaderProgram *shaderProgram, GLuint vertexCount, vec3 lightPos1, vec3 lightPos2) {
	shaderProgram->use();

	mat4 P, V, M;
	P = perspective(45 * PI / 180, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0f, 50.0f); //Wylicz macierz rzutowania
	//Upper View
/*	V = lookAt( //Wylicz macierz widoku
		vec3(0.0f, 20.0f, 3.1f),
		vec3(0.0f, 0.0f, 3.0f),
		vec3(0.0f, 1.0f, 0.0f));
*/
 V = lookAt( //Wylicz macierz widoku
		vec3(4.0f, 5.0f, 9.0f),
		vec3(-1.0f, -3.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)); 

	//Wylicz macierz modelu rysowanego obiektu
	M = mat4(1.0f);

	//compute P V M and vertex count
	M = scale(M, Scale);
	V = translate(V, Position);
	M = rotate(M,Rotation.x*PI/180.0f,vec3(1.0f,0.0f,0.0f));
	M = rotate(M,Rotation.y*PI/180.0f,vec3(0.0f,1.0f,0.0f));
	M = rotate(M,Rotation.z*PI/180.0f,vec3(0.0f,0.0f,1.0f));

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(M));
    glUniform4f(shaderProgram->getUniformLocation("lp1"), 5, 1, 1, 1); 
    glUniform4f(shaderProgram->getUniformLocation("lp2"), lightPos2.x/2, 1, lightPos2.z/2, 1); 
	glUniform1i(shaderProgram->getUniformLocation("textureMap0"),0);
  
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Tex);
	//std::cout << lightPos2.x << " : " << lightPos2.z << std::endl;


	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}