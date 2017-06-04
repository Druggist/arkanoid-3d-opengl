#include "game_object.h"

GameObject::GameObject()
	: Position(vec3(0.0f)), Size(vec3(1.0f)), Color(vec3(1.0f)), Velocity(vec3(0.0f)), Rotation(vec3(0.0f)), Solid(false), Destroyed(false), Tex(ReadTexture("assets/textures/checker2.png")) {}

GameObject::GameObject(vec3 pos, vec3 size, glm::vec3 color, vec3 velocity, vec3 rotation, const char* filename)
	: Position(pos), Size(size), Color(color), Velocity(velocity), Rotation(rotation), Solid(false), Destroyed(false), Tex(ReadTexture(filename)) {}

GLuint GameObject::ReadTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	if (error!=0) {
        printf("Error while reading texture %s. Error code: %d. \n",filename,error);
	}

	//Import do pamięci karty graficznej
	glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return tex;
}


void GameObject::Draw(GLuint &vao, ShaderProgram *shaderProgram, GLuint vertexCount) {
	shaderProgram->use();

	mat4 P, V, M;
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	V = glm::lookAt( //Wylicz macierz widoku
		glm::vec3(0.0f, 0.0f, -3.5f),
		glm::vec3(0.0f, 0.0f, 0.0f),
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
    glUniform4f(shaderProgram->getUniformLocation("lp"), 0, 0, -6, 1); 

	glUniform1i(shaderProgram->getUniformLocation("textureMap0"),0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Tex);


	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}