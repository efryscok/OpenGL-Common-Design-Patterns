#include "CRedFruit.h"

// Create the game data object and set attributes
CRedFruit::CRedFruit() {
	this->mGameData = new IGameObject::SGameData();
	this->mGameData->colour = glm::vec3(1.f, 0.f, 0.f);
	this->mGameData->meshName = "Sphere.ply";
}

// Clear out the game data from the heap
CRedFruit::~CRedFruit() {
	delete this->mGameData;
}

// Getters
const IGameObject::SGameData& CRedFruit::getData() {
	return *this->mGameData;
}

// Setters
void CRedFruit::setPosition(glm::vec3 position) {
	this->mGameData->position = position;
}

void CRedFruit::setScale(float scale) {
	this->mGameData->scale = scale;
}
