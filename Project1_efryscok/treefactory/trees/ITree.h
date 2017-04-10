#pragma once

#include "..\..\IGameObject.h"

class ITree : public IGameObject {
public:
	// Virtual detructor needed to prevent memory leak
	virtual ~ITree() {};

	// Virtual functions that must be implemented by child classes
	virtual const IGameObject::SGameData& getFruitData(unsigned int fruitID) = 0;
	virtual unsigned int getNumberOfFruits() = 0;
	virtual void growFruit() = 0;
};