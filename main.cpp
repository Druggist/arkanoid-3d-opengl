#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "constants.h"
#include "game.h"

Game Arkanoid(LEVEL_WIDTH);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) Arkanoid.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE) Arkanoid.Keys[key] = GL_FALSE;
	}
}

int main(int argc, char const *argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Arkanoid.Init();

	GLfloat dt = 0.0f;
	GLfloat lf = 0.0f;

	Arkanoid.State = GAME_ACTIVE;

	while(!glfwWindowShouldClose(window)) {
		GLfloat cf = glfwGetTime();
		dt = cf - lf;
		lf = cf;
		glfwPollEvents();

		Arkanoid.ProcessInput(dt);
		Arkanoid.Update(dt);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Arkanoid.Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}