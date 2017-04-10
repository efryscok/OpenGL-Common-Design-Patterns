#pragma once

#include "IFruit.h"

class COrangeFruit : public IFruit {
private:
	// Data
	SGameData* mGameData;

public:
	// Constructors/Destructors
	COrangeFruit();
	virtual ~COrangeFruit();

	// Functions
	virtual const IGameObject::SGameData& getData();
	virtual void setPosition(glm::vec3 position);
	virtual void setScale(float scale);
};