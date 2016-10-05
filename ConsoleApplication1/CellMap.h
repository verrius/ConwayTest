#pragma once

using namespace std;

#include <set>

// Class that acts as the glue between the game and the data structures.
// Implements simple interface so to aid in switching out the backing data structure

// Don't want extra baggage of pair for now
struct Cell {
	int64_t x;
	int64_t y;

	// Need to define a less<> operator so we can (ab)use set<>
	bool operator<(const Cell& other) const {
		if (x == other.x) {
			return y < other.y;
		} else {
			return x < other.x;
		}
	}
};

class ICellMap {
public:
	virtual ~ICellMap() {};

	virtual const set<Cell>& getCells() const = 0;
	virtual void addCell(const Cell& cell) = 0;
	virtual void getLiveNeighbors(const Cell & inCell, set<Cell>& out) const = 0;
	virtual void getDeadNeighbors(const Cell & inCell, set<Cell>& out) const = 0;
	virtual bool isCellAlive(const Cell& cell) const = 0;
	virtual void draw(float w, float h) const = 0;
};

extern bool willCellLive(const ICellMap& map, const Cell& cell);

// TODO: Move these out into separate files
class SetCellMap : public ICellMap
{
public:
	SetCellMap();
	virtual ~SetCellMap();

	virtual const set<Cell>& getCells() const;
	virtual void addCell(const Cell& cell);

	virtual void getLiveNeighbors(const Cell & inCell, set<Cell>& out) const;
	virtual void getDeadNeighbors(const Cell & inCell, set<Cell>& out) const;
	virtual bool isCellAlive(const Cell& cell) const;
	virtual void draw(float w, float h) const;

protected:
	virtual void addAdjacentCellsToSet(const Cell& inCell, set<Cell> &deadOut, set<Cell> &liveOut) const;

private:
	set<Cell> *mCells;
};
