#include "CFruitFactoryImp.h"
#include "fruits\CRedFruit.h"
#include "fruits\CGreenFruit.h"
#include "fruits\COrangeFruit.h"
#include "fruits\CYellowFruit.h"

// Takes a game data object to determine which fruit to make
IFruit* CFruitFactoryImp::createFruit(const IGameObject::SGameData& gameData) {
	if (gameData.meshName == "OpenTree.ply") {
		return new CGreenFruit();
	}
	else if (gameData.meshName == "OvalTree.ply") {
		return new COrangeFruit();
	}
	else if (gameData.meshName == "PyramidTree.ply") {
		return new CRedFruit();
	}
	else if (gameData.meshName == "RoundTree.ply") {
		return new CYellowFruit();
	}

	return nullptr;
}