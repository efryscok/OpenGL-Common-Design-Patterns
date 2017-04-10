#pragma once

#include "ITree.h"
#include "ITreeAttachFruit.h"

class COvalTree : public ITree, public ITreeAttachFruit {
private:
	// Data
	float mFruitSize;
	static const unsigned int mskNumberOfFruits = 20;
	IFruit* mFruits[mskNumberOfFruits];
	SGameData* mGameData;

public:
	// Constructors/Destructors
	COvalTree(const IGameObject::SGameData& data);
	virtual ~COvalTree();

	// Functions
	virtual auto attach(unsigned int location, IFruit* pFruit) -> void;
	virtual auto getData() -> const IGameObject::SGameData&;
	virtual auto getFruitData(unsigned int fruitID) -> const IGameObject::SGameData&;
	virtual auto getNumberOfFruits() -> unsigned int;
	virtual auto growFruit() -> void;
};