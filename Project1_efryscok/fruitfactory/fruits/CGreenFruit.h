#pragma once

#include "IFruit.h"

class CGreenFruit : public IFruit {
private:
	// Data
	SGameData* mGameData;

public:
	// Constructors/Destructors
	CGreenFruit();
	virtual ~CGreenFruit();

	// Functions
	virtual const IGameObject::SGameData& getData();
	virtual void setPosition(glm::vec3 position);
	virtual void setScale(float scale);
};