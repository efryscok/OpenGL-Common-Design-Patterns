#include "COrangeFruit.h"

// Create the game data object and set attributes
COrangeFruit::COrangeFruit() {
	this->mGameData = new IGameObject::SGameData();
	this->mGameData->colour = glm::vec3(1.f, 0.4f, 0.f);
	this->mGameData->meshName = "Sphere.ply";
}

// Clear out the game data from the heap
COrangeFruit::~COrangeFruit() {
	delete this->mGameData;
}

// Getters
const IGameObject::SGameData& COrangeFruit::getData() {
	return *this->mGameData;
}

// Setters
void COrangeFruit::setPosition(glm::vec3 position) {
	this->mGameData->position = position;
}

void COrangeFruit::setScale(float scale) {
	this->mGameData->scale = scale;
}
