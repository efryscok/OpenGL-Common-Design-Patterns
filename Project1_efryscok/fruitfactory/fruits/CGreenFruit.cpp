#include "CGreenFruit.h"

// Create the game data object and set attributes
CGreenFruit::CGreenFruit() {
	this->mGameData = new IGameObject::SGameData();
	this->mGameData->colour = glm::vec3(0.f, 1.f, 0.f);
	this->mGameData->meshName = "Sphere.ply";
}

// Clear out the game data from the heap
CGreenFruit::~CGreenFruit() {
	delete this->mGameData;
}

// Getters
const IGameObject::SGameData& CGreenFruit::getData() {
	return *this->mGameData;
}

// Setters
void CGreenFruit::setPosition(glm::vec3 position) {
	this->mGameData->position = position;
}

void CGreenFruit::setScale(float scale) {
	this->mGameData->scale = scale;
}
