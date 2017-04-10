#pragma once

#include <string>
#include <glm\glm.hpp>

// General class used to represent an object to render
struct IGameObject {
public:
	// All information needed for rendering a 3D object
	struct SGameData {
		// Constructors
		SGameData() : 
			hasPhysics(false),
			isWireframe(false),

			scale(0.f),
			radius(0.f),

			velocity(0.f),
			acceleration(0.f),
			preRotation(0.f),
			postRotation(0.f),

			position(0.f),
			lastPosition(0.f),
			colour(0.f),

			meshName("N/A")
		{};

		// Flag variables
		bool hasPhysics;
		bool isWireframe;

		float scale;
		float radius;

		// Physics variables
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 preRotation;
		glm::vec3 postRotation;

		// General object variables
		glm::vec3 position;
		glm::vec3 lastPosition;
		glm::vec3 colour;

		// Mesh info
		std::string meshName;
	};

public:
	// Destructors
	virtual ~IGameObject() {};

	// Functions
	virtual const SGameData& getData() = 0;
};
