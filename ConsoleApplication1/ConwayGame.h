#pragma once

#include "CellMap.h"

class ConwayGame
{
public:
	ConwayGame();
	ConwayGame(const char* inputFilename);
	~ConwayGame();

	void draw(float w, float h) const ;
	void runIteration();
	void addCell(int64_t x, int64_t y);
	void printState() const;

private:
	ICellMap *mCellMap;
};

