#include "CellMap.h"
#include <GL/glut.h>

bool willCellLive(const ICellMap& map, const Cell& cell) {
	set<Cell> liveNeighbors;

	map.getLiveNeighbors(cell, liveNeighbors);
	if (map.isCellAlive(cell)) {
		return !((liveNeighbors.size() < 2) || (liveNeighbors.size() > 3));
	} else {
		return liveNeighbors.size() == 3;
	}
}

SetCellMap::SetCellMap() {
	mCells = new set<Cell>();
}

SetCellMap::~SetCellMap() {
	delete mCells;
}

const set<Cell>& SetCellMap::getCells() const {
	return *mCells;
}

void SetCellMap::addCell(const Cell& cell) {
	Cell c(cell);
	mCells->insert(c);
}

void SetCellMap::getLiveNeighbors(const Cell &inCell, set<Cell> &out) const {
	set<Cell> nullSet;
	addAdjacentCellsToSet(inCell, out, nullSet);
}

void SetCellMap::getDeadNeighbors(const Cell &inCell, set<Cell> &out) const {
	set<Cell> nullSet;
	addAdjacentCellsToSet(inCell, nullSet, out);
}

static bool isOverflow(int64_t a, int64_t b, int64_t sum) {
	return (((a < 0) == (b < 0)) && ((a < 0) == (sum > b)));
}

// TODO: Find a smarter way to implement previous 2 functions without this looking awful
void SetCellMap::addAdjacentCellsToSet(const Cell &inCell, set<Cell> &deadOut, set<Cell> &liveOut) const {
	Cell newCell;
	for (int64_t i = -1; i < 2; ++i) {
		for (int64_t j = -1; j < 2; ++j) {
			newCell.x = inCell.x + i;
			newCell.y = inCell.y + j;
			// TODO: Check to make sure overflow test works
			// Check for under/overflow
			/*
			if ((newCell.x - inCell.x) != i) {
				continue;
			}
			if ((newCell.y - inCell.y) != j) {
				continue;
			}
			*/
			if ((isOverflow(inCell.x, i, newCell.x) || isOverflow(inCell.y, j, newCell.y))) {
				continue;
			}
			// Don't add ourselves to the list
			if (newCell.x == inCell.x && newCell.y == inCell.y) {
				continue;
			}
			if (mCells->find(newCell) != mCells->end()) {
				deadOut.insert(newCell);
			} else {
				liveOut.insert(newCell);
			}
		}
	}
}

void SetCellMap::draw(float w, float h) const {
	for (auto i = mCells->begin(); i != mCells->end(); i++) {
		glVertex3f((i->x + 0.0f)/w, (i->y + 0.0f)/h, 0.0f);
		glVertex3f((i->x + 0.0f)/w, (i->y + 1.0f)/h, 0.0f);
		glVertex3f((i->x + 1.0f)/w, (i->y + 1.0f)/h, 0.0f);
		glVertex3f((i->x + 1.0f)/w, (i->y + 0.0f)/h, 0.0f);
	}
}

bool SetCellMap::isCellAlive(const Cell &cell) const {
	return mCells->find(cell) != mCells->end();
}
