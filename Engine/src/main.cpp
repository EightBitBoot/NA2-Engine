#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

int main() {
	if (!glfwInit()) {
		printf("Failed to initalize GLFW!\n");
		getchar();
		return 1;
	}

	printf("Using GLFW version %s\n", glfwGetVersionString());

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(896, 504, "Switch", NULL, NULL);

	if (window == nullptr) {
		printf("Failed to create window!");
		glfwTerminate();
		getchar();
		return 1;
	}

	glfwMakeContextCurrent(window);

	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		printf("Failed to initalize GLEW!\n");
		printf("%s\n", glewGetErrorString(glewInitStatus));
		getchar();
		return 1;
	}

	printf("Using glew version %s\n", glewGetString(GLEW_VERSION));
	printf("Using OpenGL version %s\n\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.7, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}