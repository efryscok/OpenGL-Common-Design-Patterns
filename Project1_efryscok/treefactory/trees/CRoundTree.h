#pragma once

#include "ITree.h"
#include "ITreeAttachFruit.h"

class CRoundTree : public ITree, public ITreeAttachFruit {
private:
	// Data
	float mFruitSize;
	static const unsigned int mskNumberOfFruits = 20;
	IFruit* mFruits[mskNumberOfFruits];
	SGameData* mGameData;

public:
	// Constructors/Destructors
	CRoundTree(const IGameObject::SGameData& data);
	virtual ~CRoundTree();

	// Functions
	virtual auto attach(unsigned int location, IFruit* pFruit) -> void;
	virtual auto getData() -> const IGameObject::SGameData&;
	virtual auto getFruitData(unsigned int fruitID) -> const IGameObject::SGameData&;
	virtual auto getNumberOfFruits() -> unsigned int;
	virtual auto growFruit() -> void;
};