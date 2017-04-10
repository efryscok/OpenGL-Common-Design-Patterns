#include "CTreeFactory.h"
#include "CTreeFactoryImp.h"

// Create the factory implementation object
CTreeFactory::CTreeFactory() {
	this->mImp = new CTreeFactoryImp();
}

// Destroy the factory implementation object
CTreeFactory::~CTreeFactory() {
	delete this->mImp;
}

// Use the implementation object to create a tree
ITree * CTreeFactory::createTree(const IGameObject::SGameData& gameData) {
	return this->mImp->createTree(gameData);
}
