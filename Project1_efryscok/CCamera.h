#pragma once

#include <glm/glm.hpp>

// Class used to store the camera information
class CCamera {
	// Data
public:
	// Projection matrix info
	float fovy;
	float aspect;
	float zNear;
	float zFar;

	// View matrix info
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	// Functions
public:
	// All in one constructor
	CCamera(
		float fovy,
		float aspect,
		float zNear,
		float zFar,

		glm::vec3 eye,
		glm::vec3 center,
		glm::vec3 up
	) : 
		fovy(fovy),
		aspect(aspect),
		zNear(zNear),
		zFar(zFar),

		eye(eye),
		center(center),
		up(up)
	{};
};

