#include "CTreeFactoryImp.h"
#include "trees\COpenTree.h"
#include "trees\COvalTree.h"
#include "trees\CPyramidTree.h"
#include "trees\CRoundTree.h"

// Takes a game data object to construct the tree with
ITree* CTreeFactoryImp::createTree(const IGameObject::SGameData& gameData) {
	if (gameData.meshName == "OpenTree.ply") {
		return new COpenTree(gameData);
	}
	else if (gameData.meshName == "OvalTree.ply") {
		return new COvalTree(gameData);
	}
	else if (gameData.meshName == "PyramidTree.ply") {
		return new CPyramidTree(gameData);
	}
	else if (gameData.meshName == "RoundTree.ply") {
		return new CRoundTree(gameData);
	}

	return nullptr;
}
