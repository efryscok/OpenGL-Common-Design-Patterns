#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <Windows.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CCamera.h"
#include "CMeshManager.h"
#include "CShaderManager.h"
#include "CObjectBuilder.h"
#include "IGameObject.h"

#ifdef _DEBUG
	#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DBG_NEW
#endif

#pragma region Globals

// OpenGL related variables
GLFWwindow* gWindow;
GLint		gMVPLocation;
GLuint		gShaderProgramID = 0,
			gUniLocObjectColour = 0,
			gUniLocIsWireframe = 0;
glm::mat4	gProjection, gView;

// Custom objects
std::vector<IGameObject*>	gGameObjects;
CMeshManager*				gMeshManager = 0;
CShaderManager*				gShaderManager = 0;

float gCameraMovementSpeed = 0.1f;
CCamera gCamera(
	0.6f,
	1200.f / 800.f,
	0.01f,
	100.0f,
	
	glm::vec3(0.0f, 12.5f, 25.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
);

#pragma endregion Globals

// Method declarations
void DrawScene();
void ImportScene();
void InitWindow();

// Callback functions
static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error(%d): %s\n", error, description);

	return;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(gWindow, GLFW_TRUE);
	}

	switch (key) {
	case GLFW_KEY_A:
		gCamera.eye.x -= gCameraMovementSpeed;
		break;
	case GLFW_KEY_D:
		gCamera.eye.x += gCameraMovementSpeed;
		break;
	case GLFW_KEY_W:
		gCamera.eye.z -= gCameraMovementSpeed;
		break;
	case GLFW_KEY_S:
		gCamera.eye.z += gCameraMovementSpeed;
		break;
	case GLFW_KEY_Q:
		gCamera.eye.y -= gCameraMovementSpeed;
		break;
	case GLFW_KEY_E:
		gCamera.eye.y += gCameraMovementSpeed;
		break;
	}

	return;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// Initialize the GLFW window
	InitWindow();
	
	// Display information about system
	std::cout << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << ", " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shader language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Create shader objects
	gShaderManager = new CShaderManager();
	CShaderManager::CShader verShader;
	CShaderManager::CShader fragShader;
	
	// Import the shaders from files
	verShader.fileName = "simpleVert.glsl";
	fragShader.fileName = "simpleFrag.glsl";

	if (!gShaderManager->createProgramFromFile("simple", verShader, fragShader)) {
		std::cout << gShaderManager->getLastError();
		return -1;
	}

	// Setup the mesh object to mediate importing mesh from files
	gMeshManager = new CMeshManager();
	gShaderProgramID = gShaderManager->getIDFromFriendlyName("simple");
	
	// Get uniform locations from the shader
	gMVPLocation = glGetUniformLocation(gShaderProgramID, "MVP");
	gUniLocObjectColour = glGetUniformLocation(gShaderProgramID, "objectColour");
	gUniLocIsWireframe = glGetUniformLocation(gShaderProgramID, "isWireframe");

	// Read the scene description from a file
	ImportScene();
	
	// Main application loop
	while (!glfwWindowShouldClose(gWindow)) {
		// Update the apect ratio of the camera based on window size
		int width, height;
		glfwGetFramebufferSize(gWindow, &width, &height);
		gCamera.aspect = (float)width / (float)height;
	
		// Calculate the projection matrix and the view matrix
		gProjection = glm::perspective(gCamera.fovy, gCamera.aspect, gCamera.zNear, gCamera.zFar);
		gView = glm::lookAt(gCamera.eye, gCamera.center, gCamera.up);

		// Reset the viewport and clear the screen
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
		// Render loop
		DrawScene();
	
		glfwSwapBuffers(gWindow);
		glfwPollEvents();
	}
	
	// Cleanup objects
	delete gMeshManager;
	delete gShaderManager;
	
	for (std::vector<IGameObject*>::iterator itGameObject = gGameObjects.begin(); itGameObject != gGameObjects.end(); ++itGameObject) {
		delete *itGameObject;
	}

	// Final exit commands
	glfwDestroyWindow(gWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

// General function for drawing a game object
void DrawObject(const IGameObject::SGameData& gameObjectData) {
	std::string meshModelName = gameObjectData.meshName;

	// Get the mesh info for the current object
	GLuint VAO_ID = 0;
	int numberOfIndices = 0;
	float unitScale = 1.0f;
	if (!gMeshManager->LookUpMeshInfo(meshModelName, VAO_ID, numberOfIndices, unitScale)) {
		return;
	}

	// Setup the model * view * projection matrix and model matrix
	glm::mat4 ModelViewProjection(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);

	// Pre-rotation
	Model = glm::rotate(Model, gameObjectData.preRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, gameObjectData.preRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, gameObjectData.preRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Translation
	Model = glm::translate(Model, gameObjectData.position);

	// Post-rotation
	Model = glm::rotate(Model, gameObjectData.postRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, gameObjectData.postRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, gameObjectData.postRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	float actualScale = gameObjectData.scale * unitScale;

	// Scale
	Model = glm::scale(Model, glm::vec3(actualScale, actualScale, actualScale));

	// Determine if object is to be drawn as a wireframe
	if (gameObjectData.isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Calculate model * view * projection matrix
	ModelViewProjection = gProjection * gView * Model;

	// Update shader information
	gShaderManager->useShaderProgram("simple");

	glUniformMatrix4fv(gMVPLocation, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(ModelViewProjection));
	glUniform3f(gUniLocObjectColour, gameObjectData.colour.r, gameObjectData.colour.g, gameObjectData.colour.b);

	if (gameObjectData.isWireframe) {
		glUniform1i(gUniLocIsWireframe, TRUE);
	}
	else {
		glUniform1i(gUniLocIsWireframe, FALSE);
	}

	glBindVertexArray(VAO_ID);
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}
	
// Update the scene for the next frame
void DrawScene() {
	// Loop through the object array
	for (std::vector<IGameObject*>::iterator itGameObject = gGameObjects.begin(); itGameObject != gGameObjects.end(); ++itGameObject) {
		// Current game object
		DrawObject((*itGameObject)->getData());
		
		// Cast the game object to a tree object
		ITree* treeGameObject = dynamic_cast<ITree*>(*itGameObject);

		// If the cast was successful grow and draw the fruit on the tree
		if (treeGameObject != nullptr) {
			treeGameObject->growFruit();

			for (unsigned int i = 0; i < treeGameObject->getNumberOfFruits(); ++i) {
				DrawObject(treeGameObject->getFruitData(i));
			}
		}
	}
	
	return;
}
	
// Read the scene description from a file
void ImportScene() {
	// Array of strings to read in the object attributes
	std::string line;
	std::getline(std::cin, line); // Header
	
	while (std::getline(std::cin, line)) {
		std::stringstream sstream(line);

		// Stream in from the input file to the game data object
		IGameObject::SGameData gameObjectData;
		sstream >>
			gameObjectData.meshName >>
			gameObjectData.scale >>
			gameObjectData.position.x >>
			gameObjectData.position.y >>
			gameObjectData.position.z >>
			gameObjectData.postRotation.x >>
			gameObjectData.postRotation.y >>
			gameObjectData.postRotation.z;
	
		// Use the builder to create a game object based on the game data object
		IGameObject* gameObject = CObjectBuilder::instance().buildTree(gameObjectData);

		// If a game object was successfully created
		if (gameObject != nullptr) {
			// If the game object is a tree
			if (dynamic_cast<ITree*>(gameObject) != nullptr) {
				// Cast the game object to a tree object
				ITree* treeGameObject = dynamic_cast<ITree*>(gameObject);

				// Get the mesh name and determine if it still needs to be imported
				GLuint VAO_ID = 0;
				int numberOfIndices = 0;
				float unitScale = 1.f;

				// Tree object mesh lookup/load
				if (!gMeshManager->LookUpMeshInfo(treeGameObject->getData().meshName, VAO_ID, numberOfIndices, unitScale)) {
					gMeshManager->LoadPlyFileIntoGLBuffer(gShaderProgramID, treeGameObject->getData().meshName);
				}

				// Fruit object mesh lookup/load
				for (unsigned int i = 0; i < treeGameObject->getNumberOfFruits(); ++i) {
					if (!gMeshManager->LookUpMeshInfo(treeGameObject->getFruitData(i).meshName, VAO_ID, numberOfIndices, unitScale)) {
						gMeshManager->LoadPlyFileIntoGLBuffer(gShaderProgramID, treeGameObject->getFruitData(i).meshName);
					}
				}
			}

			// Add the resulting object into the vector of all objects
			gGameObjects.push_back(gameObject);
		}
	}
	// Cleanup the attribute array
	
	return;
}
	
// GLFW window creation
void InitWindow() {
	glfwSetErrorCallback(error_callback);
	
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	gWindow = glfwCreateWindow(1200, 800, "Simple example", NULL, NULL);
	if (!gWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(gWindow, key_callback);
	glfwMakeContextCurrent(gWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	
	return;
}