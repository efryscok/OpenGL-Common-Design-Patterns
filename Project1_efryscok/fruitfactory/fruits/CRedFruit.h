#pragma once

#include "IFruit.h"

class CRedFruit : public IFruit {
private:
	// Data
	SGameData* mGameData;

public:
	// Constructors/Destructors
	CRedFruit();
	virtual ~CRedFruit();

	// Functions
	virtual const IGameObject::SGameData& getData();
	virtual void setPosition(glm::vec3 position);
	virtual void setScale(float scale);
};