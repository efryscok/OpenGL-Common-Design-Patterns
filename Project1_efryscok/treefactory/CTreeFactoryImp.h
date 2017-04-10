#pragma once

#include "CTreeFactory.h"

class CTreeFactoryImp {
public:
	// Creates a new tree from the game object data
	ITree* createTree(const IGameObject::SGameData& gameData);
};