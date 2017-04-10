#include "CPyramidTree.h"

// Initialize the initial fruit size and game object data
CPyramidTree::CPyramidTree(const IGameObject::SGameData& data) {
	this->mFruitSize = 50.f;
	this->mGameData = new IGameObject::SGameData(data);
	this->mGameData->colour = glm::vec3(0.58f, 0.29f, 0.00f);
}

// Clean up the game data object and the fruit objects
CPyramidTree::~CPyramidTree() {
	delete this->mGameData;

	for (unsigned int i = 0; i < this->mskNumberOfFruits; ++i) {
		delete this->mFruits[i];
	}
}

// Add a fruit to the tree and pick a random location on the tree to put it
void CPyramidTree::attach(unsigned int location, IFruit * pFruit) {
	pFruit->setScale(this->mGameData->scale / this->mFruitSize);

	glm::vec3 low(
		-(this->mGameData->scale / 6.f),
		(this->mGameData->scale / 3.f),
		-(this->mGameData->scale / 6.f)
	);

	glm::vec3 high(
		(this->mGameData->scale / 6.f),
		(this->mGameData->scale / 1.1),
		(this->mGameData->scale / 6.f)
	);

	glm::vec3 position(
		low.x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high.x - low.x))),
		low.y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high.y - low.y))),
		low.z + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high.z - low.z)))
	);

	pFruit->setPosition(position + this->mGameData->position);
	this->mFruits[location] = pFruit;
}

// Getters
const IGameObject::SGameData& CPyramidTree::getData() {
	return *this->mGameData;
}

const IGameObject::SGameData& CPyramidTree::getFruitData(unsigned int fruitID) {
	return this->mFruits[fruitID]->getData();
}

unsigned int CPyramidTree::getNumberOfFruits() {
	return this->mskNumberOfFruits;
}

// Grow the fruits attached to the tree until they reach maturity
void CPyramidTree::growFruit() {
	this->mFruitSize -= 0.05f;

	if (this->mFruitSize > 20.f) {
		for (unsigned int i = 0; i < this->mskNumberOfFruits; ++i) {
			this->mFruits[i]->setScale(this->mGameData->scale / this->mFruitSize);
		}
	}
}
