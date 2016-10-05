using namespace std;

#include <iostream>
#include "ConwayGame.h"
#include "CellMap.h"

ConwayGame::ConwayGame()
{
	// TODO: Make this use a factory, so we can easily switch it out with a quadtree-based cellmap later?
	mCellMap = new SetCellMap();
}

ConwayGame::ConwayGame(const char * inputFilename) {
	mCellMap = new SetCellMap();
	FILE* input = fopen("input.txt", "r");
	int64_t x, y;
	// TODO: Add some sort of error checking in case someone misformats the file, or it doesn't exist
	while (fscanf(input, "(%lld, %lld)\n", &x, &y) != EOF) {
		addCell(x, y);
	}
	fclose(input);
}

ConwayGame::~ConwayGame() {
	delete mCellMap;
}

void ConwayGame::draw(float w, float h) const {
	mCellMap->draw(w, h);
}

void ConwayGame::runIteration() {
	SetCellMap *nextCellMap = new SetCellMap();
	set<Cell> candidates;
	for (auto i = mCellMap->getCells().begin(); i != mCellMap->getCells().end(); ++i) {
		if (willCellLive(*mCellMap, *i)) {
			nextCellMap->addCell(*i);
		}
		mCellMap->getDeadNeighbors(*i, candidates);
	}

	for (auto i = candidates.begin(); i != candidates.end(); ++i) {
		if (willCellLive(*mCellMap, *i)) {
			nextCellMap->addCell(*i);
		}
	}

	delete mCellMap;
	mCellMap = nextCellMap;
}

void ConwayGame::addCell(int64_t x, int64_t y) {
	Cell c = { x, y };
	mCellMap->addCell(c);
}

void ConwayGame::printState() const {
	for (auto i = mCellMap->getCells().begin(); i != mCellMap->getCells().end(); ++i) {
		cout << "(" << i->x << ", " << i->y << ")" << endl;
	}
}