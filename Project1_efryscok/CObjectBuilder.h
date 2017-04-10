#pragma once

#include "treefactory\trees\ITree.h"
#include "CSingleton.h"
#include <memory>

class CObjectBuilder : public CSingleton {
public:
	// Singleton function
	static CObjectBuilder& instance() {
		static std::unique_ptr<CObjectBuilder> _instance(new CObjectBuilder);
		return *_instance;
	}

	// Functions
	ITree* buildTree(const IGameObject::SGameData& gameData);
};