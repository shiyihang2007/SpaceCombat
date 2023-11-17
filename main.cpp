
// clang-format off
#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "game/game.h"
#include "resource_manager.h"

// GLFW function declerations
void key_callback(GLFWwindow *window, int key, int scancode, int action,
				  int mode);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// The Width of the screen
const GLuint SCREEN_WIDTH = 200;
// The height of the screen
const GLuint SCREEN_HEIGHT = 320;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

auto main(int argc, const char *argv[]) -> int {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
										  "Test-4", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
		0) {
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	game.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0F;
	GLfloat lastFrame = 0.0F;

	while (glfwWindowShouldClose(window) == 0) {
		// Calculate delta time
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// deltaTime = 0.001f;
		// Manage user input
		game.ProcessInput(deltaTime);

		// Update Game state
		game.Update(deltaTime);

		// Render
		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);
		game.Render();

		glfwSwapBuffers(window);
	}
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
				  int mode) {
	// When a user presses the escape key, we set the WindowShouldClose
	// property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			game.Keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE) {
			game.Keys[key] = GL_FALSE;
		}
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that
	// width and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}
