#pragma once

#include "..\..\IGameObject.h"

class IFruit : public IGameObject {
public:
	// Virtual detructor needed to prevent memory leak
	virtual ~IFruit() {};

	// Virtual functions that must be implemented by child classes
	virtual void setPosition(glm::vec3 position) = 0;
	virtual void setScale(float scale) = 0;
};