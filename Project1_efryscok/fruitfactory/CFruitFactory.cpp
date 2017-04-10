#include "CFruitFactory.h"
#include "CFruitFactoryImp.h"

// Create the factory implementation object
CFruitFactory::CFruitFactory() {
	this->mImp = new CFruitFactoryImp();
}

// Destroy the factory implementation object
CFruitFactory::~CFruitFactory() {
	delete this->mImp;
}

// Use the implementation object to create a fruit
IFruit* CFruitFactory::createFruit(const IGameObject::SGameData& gameData) {
	return this->mImp->createFruit(gameData);
}