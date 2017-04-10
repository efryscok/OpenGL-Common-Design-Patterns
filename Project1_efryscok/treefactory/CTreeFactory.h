#pragma once

#include "trees\ITree.h"

// Forward declaration for the implementation of the factory
class CTreeFactoryImp;

class CTreeFactory {
private:
	// Data
	CTreeFactoryImp* mImp;

public:
	// Constructors/Destructors
	CTreeFactory();
	~CTreeFactory();

	// Functions
	ITree* createTree(const IGameObject::SGameData& gameData);
};