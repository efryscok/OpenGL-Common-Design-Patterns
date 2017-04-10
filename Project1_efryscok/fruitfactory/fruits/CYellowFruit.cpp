#include "CYellowFruit.h"

// Create the game data object and set attributes
CYellowFruit::CYellowFruit() {
	this->mGameData = new IGameObject::SGameData();
	this->mGameData->colour = glm::vec3(1.f, 1.f, 0.f);
	this->mGameData->meshName = "Sphere.ply";
}

// Clear out the game data from the heap
CYellowFruit::~CYellowFruit() {
	delete this->mGameData;
}

// Getters
const IGameObject::SGameData& CYellowFruit::getData() {
	return *this->mGameData;
}

// Setters
void CYellowFruit::setPosition(glm::vec3 position) {
	this->mGameData->position = position;
}

void CYellowFruit::setScale(float scale) {
	this->mGameData->scale = scale;
}
