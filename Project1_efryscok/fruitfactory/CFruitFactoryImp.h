#pragma once

#include "CFruitFactory.h"

class CFruitFactoryImp {
public:
	// Functions
	IFruit* createFruit(const IGameObject::SGameData& gameData);
};