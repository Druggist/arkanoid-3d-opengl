#include "game_object.h"

GameObject::GameObject()
	: Position(vec3(0.0f)), Size(vec3(1.0f)), Color(vec3(1.0f)), Velocity(vec3(0.0f)), Rotation(vec3(0.0f)), Solid(false), Destroyed(false), Tex(Renderer::ReadTexture("assets/textures/checker2.png")) {}

GameObject::GameObject(vec3 pos, vec3 size, glm::vec3 color, vec3 velocity, vec3 rotation, const char* filename)
	: Position(pos), Size(size), Color(color), Velocity(velocity), Rotation(rotation), Solid(false), Destroyed(false), Tex(Renderer::ReadTexture(filename)) {}


void GameObject::Draw(GLuint &vao, ShaderProgram *shaderProgram, GLuint vertexCount) {
	shaderProgram->use();

	mat4 P, V, M;
	P = glm::perspective(45 * PI / 180, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0f, 50.0f); //Wylicz macierz rzutowania
	//Upper View
	V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 20.0f, 3.1f),
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(4.0f, 5.0f, 9.0f),
		glm::vec3(-1.0f, -3.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Wylicz macierz modelu rysowanego obiektu
	M = glm::mat4(1.0f);

	//compute P V M and vertex count
	M = glm::scale(M, Size);
	M = glm::translate(M, Position);
	M = glm::rotate(M,Rotation.x*PI/180.0f,glm::vec3(1.0f,0.0f,0.0f));
	M = glm::rotate(M,Rotation.y*PI/180.0f,glm::vec3(0.0f,1.0f,0.0f));
	M = glm::rotate(M,Rotation.z*PI/180.0f,glm::vec3(0.0f,0.0f,1.0f));

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(M));
    glUniform4f(shaderProgram->getUniformLocation("lp"), 0, 5, 1, 1); 

	glUniform1i(shaderProgram->getUniformLocation("textureMap0"),0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Tex);


	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}