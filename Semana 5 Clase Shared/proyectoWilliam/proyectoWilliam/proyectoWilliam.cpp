// PracticaShaders.cpp: define el punto de entrada de la aplicación de consola.

//



#include "stdafx.h"

#include <iostream>





#include <GL/glew.h>

#include <GLFW/glfw3.h>



#include "Shader.h"



const GLint WIDTH = 800, HEIGHT = 600;



void configWindow()

{

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

}



int main()

{

	//===================================== TEMPLATE ===========================================================

	//Init GLFW

	glfwInit();



	configWindow();



	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn to do triangle", nullptr, nullptr);



	int screenWidth, screenHeight;



	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);



	if (nullptr == window)

	{

		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();



		return EXIT_FAILURE;

	}



	glfwMakeContextCurrent(window);



	glewExperimental = GL_TRUE;



	//Initialize the GLEW to setup the OpenGL function pointers

	if (GLEW_OK != glewInit())

	{

		std::cout << "Failed to initilize the GLEW" << std::endl;



		glfwTerminate();



		return EXIT_FAILURE;

	}

	// Define the viewport and its dimensiones

	glViewport(0, 0, screenWidth, screenHeight);



	Shader ourShader("core.vs", "core.frag");



	//===================================== TEMPLATE ===========================================================

	GLfloat vertices[] =

	{

		//Position				//Color

		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,//bottom left

		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,//bottom right

		0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f//up center

	};



	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);



	glBindVertexArray(VAO);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);

	glEnableVertexAttribArray(0);



	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);



	//glBindBuffer(GL_ARRAY_BUFFER, 0);



	glBindVertexArray(0);



	// Game loop

	while (!glfwWindowShouldClose(window))

	{

		// Check if any events have been activated (Keypressed, mouse moved etc.) and call corresponding response 

		// function

		glfwPollEvents();



		// Render

		// Color de fondo

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);



		//Invoca el Shader

		ourShader.use();

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Dibuja el triangulo



		glBindVertexArray(0);



		// Swap the screen buffer

		glfwSwapBuffers(window);

	}



	// Eliminacion de buffers y arreglo de vertices

	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &VBO);

	// Fin de la ventana

	glfwTerminate();

	//Salida segura

	return EXIT_SUCCESS;

}