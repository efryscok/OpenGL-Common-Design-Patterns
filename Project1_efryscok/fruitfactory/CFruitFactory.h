#pragma once

#include "fruits\IFruit.h"

// Forward declaration for the implementation of the factory
class CFruitFactoryImp;

class CFruitFactory {
private:
	// Data
	CFruitFactoryImp* mImp;

public:
	// Constructors/Destructors
	CFruitFactory();
	~CFruitFactory();

	// Functions
	IFruit* createFruit(const IGameObject::SGameData& gameData);
};