#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "constants.h"
#include "game.h"

Game Arkanoid;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) Arkanoid.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE) Arkanoid.Keys[key] = GL_FALSE;
	}
}

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

int main(int argc, char const *argv[]) {
	
	GLFWwindow* window; 
	
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Cannot initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}

	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Cannot create a window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Cannot initialize GLEW.\n");
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	
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

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		Arkanoid.Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}