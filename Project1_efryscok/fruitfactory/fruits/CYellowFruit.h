#pragma once

#include "IFruit.h"

class CYellowFruit : public IFruit {
private:
	// Data
	SGameData* mGameData;

public:
	// Constructors/Destructors
	CYellowFruit();
	virtual ~CYellowFruit();

	// Functions
	virtual const IGameObject::SGameData& getData();
	virtual void setPosition(glm::vec3 position);
	virtual void setScale(float scale);
};