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
	printf("GLFW version: %s\n",   glfwGetVersionString());
	printf("GLEW version: %s\n",   glewGetString(GLEW_VERSION));

	//Set the window background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetWindowSizeCallback(window, &glfw_window_resize_callback);

	//Mark the engine as running after environment initialization
	bool stopped = false;

	//nat::vertex vertices[] = {
	//	{ -0.5f,  0.5f },
	//	{ -0.5f, -0.5f },
	//	{  0.5f,  0.5f },
	//	{  0.5f,  0.5f },
	//	{  0.5f, -0.5f },
	//	{ -0.5f, -0.5f }
	//};

	nat::vertex vertices[] = {
		//Back Face
		{-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{ 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{ 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f},

		//Front Face				
		{-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f},
		{ 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f},
		{ 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f},
		{ 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f},
		{-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f},
		{-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f},

		//Left Face					
		{-0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.5f},
		{-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f},
		{-0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.5f},
		{-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f},
		{-0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.5f},
		{-0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.5f},

		//Right Face
		{ 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f},
		
		//Bottom Face			
		{-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f},
		{ 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f},
		{ 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f},
		{-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f},
		{-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f},
		
		//Top Face
		{-0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.5f},
		{ 0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.5f},
		{ 0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.5f},
		{ 0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.5f},
		{-0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.5f},
		{-0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.5f}
	};

	//Initialize an OpenGL manager
	nat::GLManager manager;

	GLCALL(glEnable(GL_CULL_FACE));

	//Create a VertexArray for the rectangle
	nat::VertexArray vertexArray(&manager);
	vertexArray.addVertices(vertices, 36);

	vertexArray.bufferVertices();
	
	//Define the position attribute
	vertexArray.pushFormat(GL_FLOAT, 3);
	vertexArray.pushFormat(GL_FLOAT, 3);

	nat::Shader shader(&manager, "shader/test.shad");
	shader.compile();
	shader.link();
	
	//Rotation matrix
	nat::Mat4 proMat = nat::Mat4::Orthographic(-3.0f, 3.0f, -2.0f, 2.0f, -1.0f, 1.0f);
	nat::Mat4 rotMaty(1.0f);
	nat::Mat4 rotMatx(1.0f);

	//Angle to rotate the rectangle
	float angleY = 0.0f;
	float angleX = 0.0f;

	nat::Mat4 trsMat;

	//MAIN LOOP
	while (!stopped) {
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glfwPollEvents();

		//Adjust the angle if the left or right key is being pressed
		int leftState = glfwGetKey(window, GLFW_KEY_LEFT);
		if (leftState == GLFW_PRESS) {
			angleY += ANGLE_VELOCITY;
		}

		int rightState = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (rightState == GLFW_PRESS) {
			angleY -= ANGLE_VELOCITY;
		}

		int upState = glfwGetKey(window, GLFW_KEY_UP);
		if (upState == GLFW_PRESS) {
			angleX -= ANGLE_VELOCITY;
		}

		int downState = glfwGetKey(window, GLFW_KEY_DOWN);
		if (downState == GLFW_PRESS) {
			angleX += ANGLE_VELOCITY;
		}

		//Compute the rotation and store in the rotation matrix
		float negAngleCosy = cos(-1.0f * angleY);
		float negAngleSiny = sin(-1.0f * angleY);

		float negAngleCosx = cos(-1.0f * angleX);
		float negAngleSinx = sin(-1.0f * angleX);

		rotMaty[0][0] =	negAngleCosy;
		rotMaty[0][2] =	negAngleSiny;
		rotMaty[2][0] = -negAngleSiny;
		rotMaty[2][2] =	negAngleCosy;
		
		rotMatx[1][1] =	negAngleCosx;
		rotMatx[1][2] = -negAngleSinx;
		rotMatx[2][1] =	negAngleSinx;
		rotMatx[2][2] =	negAngleCosx;

		trsMat = proMat * rotMaty * rotMatx;

		//Draw the rectangle
		vertexArray.bind();
		
		shader.use();
		shader.setUniformMat4f("trsMat", trsMat);

		GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));

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