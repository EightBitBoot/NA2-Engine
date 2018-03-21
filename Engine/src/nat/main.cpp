#include <iostream>

#include <math.h>

#include "graphics\glcommon.h"

#include "graphics\vertexarray.h"
#include "graphics\glmanager.h"
#include "graphics\shader.h"

#include "math\mat4.h"

#define ANGLE_VELOCITY 0.1f

void terminal_error(const char* message);
void glfw_window_resize_callback(GLFWwindow* window, int width, int height);

int main()
{	
	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE) {
		terminal_error("Failed to initialize GLFW!");
	}

	//Create the window
	GLFWwindow* window = glfwCreateWindow(600, 400, "Switch", NULL, NULL);
	if (!window) {
		terminal_error("Failed to create window!");
	}

	//Create OpenGL context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Initialize GLEW
	if (glewInit() != GLEW_OK) {
		terminal_error("Failed to initialize GLEW!");
	}

	//Print environment information
	printf("OPENGL version: %s\n", glGetString(GL_VERSION));
	printf("GLFW version: %s\n", glfwGetVersionString());
	printf("GLEW version: %s\n", glewGetString(GLEW_VERSION));


	//Set the window background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetWindowSizeCallback(window, &glfw_window_resize_callback);

	//Mark the engine as running after environment initialization
	bool stopped = false;

	vertex vertices[] = {
		{ -0.5f,  0.5f },
		{ -0.5f, -0.5f },
		{  0.5f,  0.5f },
		{  0.5f,  0.5f },
		{  0.5f, -0.5f },
		{ -0.5f, -0.5f }
	};
	
	//Initialize an OpenGL manager
	nat::GLManager manager;

	//Create a VertexArray for the rectangle
	nat::VertexArray vertexArray(&manager);
	vertexArray.addVertices(vertices, 6);

	vertexArray.bufferVertices();
	
	//Define the position attribute
	vertexArray.pushFormat(GL_FLOAT, 2);

	nat::Shader shader(&manager, "shader/test.shad");
	shader.compile();
	shader.link();
	
	//Rotation matrix
	nat::Mat4 matrix;

	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;

	//Angle to rotate the rectangle
	float angle = 0.0f;
	float colorAngle = 0.0f;

	//MAIN LOOP
	while (!stopped) {
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glfwPollEvents();

		//Adjust the angle if the left or right key is being pressed
		int leftState = glfwGetKey(window, GLFW_KEY_LEFT);
		if (leftState == GLFW_PRESS) {
			angle -= ANGLE_VELOCITY;
		}

		int rightState = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (rightState == GLFW_PRESS) {
			angle += ANGLE_VELOCITY;
		}

		colorAngle += ANGLE_VELOCITY;
		float colorVariation = abs(sin(colorAngle));

		if (colorVariation == 0.1f) {
			colorVariation = 0.1f;
		}

		//Compute the rotation and store in the rotation matrix
		float negAngleCos = cos(-1.0f * angle);
		float negAngleSin = sin(-1.0f * angle);

		matrix[0][0] = negAngleCos;
		matrix[0][2] = negAngleSin;
		matrix[2][0] = negAngleSin;
		matrix[2][2] = negAngleCos;
		
		//Draw the rectangle
		vertexArray.bind();

		shader.use();
		shader.setUniformMat4f("rotMat", matrix);
		shader.setUniform1f("colorVariation", colorVariation);

		GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));

		vertexArray.unbind();

		//Present the final product
		glfwSwapBuffers(window);

		//Exit if the window is closed
		if (glfwWindowShouldClose(window)) {
			stopped = true;
		}
	}

	//Cleanup shader program
	//GLCALL(glDeleteProgram(shaderProgramID));

	//Close the window
	glfwDestroyWindow(window);
	//Shutdown GLFW
	glfwTerminate();
	
	//Pause so log is readable
	getchar();

	return 0;
}

//Exit the program if a fatal error is encountered
void terminal_error(const char* message)
{
	printf(message);
	glfwTerminate();
	getchar();
	exit(-1);
}

//GLFW window callback that resizes the OpenGL Viewport to the new window dimensions
void glfw_window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}