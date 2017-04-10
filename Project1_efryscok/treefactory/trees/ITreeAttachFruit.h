#pragma once

#include "..\..\fruitfactory\fruits\IFruit.h"

class ITreeAttachFruit {
public:
	// Virtual detructor needed to prevent memory leak
	virtual ~ITreeAttachFruit() {};
	
	// Virtual functions that must be implemented by child classes
	virtual void attach(unsigned int location, IFruit* pFruit) = 0;
};