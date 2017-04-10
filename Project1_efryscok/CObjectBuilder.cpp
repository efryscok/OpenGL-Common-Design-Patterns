#include "CObjectBuilder.h"
#include "treefactory\CTreeFactory.h"
#include "treefactory\trees\ITreeAttachFruit.h"
#include "fruitfactory\CFruitFactory.h"

// Create a tree and attach some fruit
ITree* CObjectBuilder::buildTree(const IGameObject::SGameData& gameData) {
	// Factory objects
	CTreeFactory* pTreeFactory = new CTreeFactory();
	CFruitFactory* pFruitFactory = new CFruitFactory();

	// Make a tree
	ITree* pTree = pTreeFactory->createTree(gameData);

	// Make the fruits and attach to the tree
	for (unsigned int i = 0; i < pTree->getNumberOfFruits(); ++i) {
		// New fruit
		IFruit* pFruit = pFruitFactory->createFruit(gameData);

		// Cast the tree to a fruit attach object to access the attach() function
		ITreeAttachFruit* pTreeAttachFruit = dynamic_cast<ITreeAttachFruit*>(pTree);

		// If cast was successful attach the fruit
		if (pTreeAttachFruit != nullptr) {
			pTreeAttachFruit->attach(i, pFruit);
		}
	}

	// Cleanup pointers and return tree pointer
	delete pTreeFactory;
	delete pFruitFactory;
	return pTree;
}
