#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include<filesystem>




#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "shapeData.h"
#include "Camera.h"
#include "Renderable.h"

#include <math.h>

const static int width = 1000;
const static int height = 1000;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL window ;3", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

    //error checks the shader files (checks if the roots are coming from the right place /// the file must be run from main.cpp to function other wise crash time)
    std::cout << "CWD at runtime: " << std::filesystem::current_path() << '\n';
    std::filesystem::path shaderPath = std::filesystem::current_path() / "entity/shaders/default.frag";
    if (!std::filesystem::exists(shaderPath)) {
        std::cerr << "Shader not found: " << shaderPath << "\n";
    }	
    // Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("entity/shaders/default.vert", "entity/shaders/default.frag");

	glEnable(GL_DEPTH_TEST);

	Renderable pyramidMesh(pyramidVertices, pyramidVerticesSize, pyramidIndices, pyramidIndicesSize);
	Renderable cubeMesh(cubeVertices, cubeVerticesSize, cubeIndices, cubeIndicesSize);
	Renderable sphereMesh(sphereVertices, sphereVerticesSize, sphereIndices, sphereIndicesSize);
	// Instantiate PhysicsObjects		

	float time, currentTime = glfwGetTime();


	Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));
	camera.pyramidRenderable = &pyramidMesh;
	camera.cubeRenderable = &cubeMesh;
	camera.sphereRenderable = &sphereMesh;


	float lastTime = glfwGetTime();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{ 
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (!camera.paused)		//pauses the simmulation
		{
			
		}
		if (camera.mouseLocked )		//locks the mouse to the center of screen
		{
			double mouseX;
            double mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
			if((mouseX < (width/2)-50) || (mouseX > (width/2)+50) || (mouseY < (height/2)-50) || (mouseY > (height/2)+50))
            {
				glfwSetCursorPos(window, (width / 2), (height / 2));
			}

		}
		
		glClearColor(0.0f, 0.0f, 0.01f, 1.0f);		// Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clean the back buffer and assign the new color to it
		shaderProgram.Activate();		// Tell OpenGL which Shader Program we want to use

		
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");

		glm::mat4 model = glm::mat4(1.0f);
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//sets the draw to be solid object (as its set else for the spacetime grid)

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cubeMesh.Draw();

		glfwSwapBuffers(window);		// Swap the back buffer with the front buffer
		glfwPollEvents();		// Take care of all GLFW events
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}